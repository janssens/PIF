/*
 * Polyhedron Intersection Framework
 * 
 * FileName: Intersection.hpp
 * Creation: 29.06.2011
 * Author: Gaëtan Janssens
 * Last Edit: 29.06.2011
 * 
 */
#ifndef INTER_H
#define INTER_H

#define DEBUG

#include <iostream>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <math.h>
#include <boost/smart_ptr/shared_ptr.hpp>
 
#include "Type.hpp"
#include "Edge.hpp"
#include "Face.hpp"
 
namespace pif {
	
	template<class T> class Intersection {
		public:
			Intersection() {};
			Intersection(Edge<T> e,Face<T> f) : _data(new Obj(e,f)){
				this->giveFeedback();
			};
			bool isNull(void) const { return !(bool)_data;};
			bool exist(void) const { return _data->exist;};
			Vertex<T> getPoint(void) const {
					return _data->point;
			};
			Face<T> getFace(void) const {
					return _data->face;
			};
			Edge<T> getEdge(void) const {
					return _data->edge;
			};
			void giveFeedback(void){ // lets give a feedback to the vertex of the two halfedge behind the edge in order to compute the inside & outside information		
				if ((bool)_data&&!(bool)_data->point.isNull()) { // intersection exist!
					if (_data->edge.getHalfEdge().getVertex().isClosestIntersectionInSpaceDefined()){//yes
						if (dist(_data->edge.getHalfEdge().getVertex().getClosestIntersectionInSpace().getPoint(),_data->edge.getHalfEdge().getVertex())>dist(this->getPoint(),_data->edge.getHalfEdge().getVertex())){ // this intersection is the closest so far
							_data->edge.getHalfEdge().getVertex().setClosestIntersectionInSpace(*this);
							#ifdef DEBUG
								std::cout << "=> feedback for " << _data->edge.getHalfEdge().getVertex() << ": " << "the closest intersection is now " << _data->edge.getHalfEdge().getVertex().getClosestIntersectionInSpace().getPoint() << std::endl;
							#endif
						}
					}else{//no
						_data->edge.getHalfEdge().getVertex().setClosestIntersectionInSpace(*this); // lets defined it
						#ifdef DEBUG
							std::cout << "=> feedback for " << _data->edge.getHalfEdge().getVertex() << ":" << "the closest intersection is " << _data->edge.getHalfEdge().getVertex().getClosestIntersectionInSpace().getPoint() << std::endl;
						#endif
					}
					if (_data->edge.getPair().getVertex().isClosestIntersectionInSpaceDefined()){//yes
						if (dist(_data->edge.getPair().getVertex().getClosestIntersectionInSpace().getPoint(),_data->edge.getPair().getVertex())>dist(this->getPoint(),_data->edge.getPair().getVertex())){ // this intersection is the closest so far
							_data->edge.getPair().getVertex().setClosestIntersectionInSpace(*this);
							#ifdef DEBUG
								std::cout << "=> feedback for " << _data->edge.getPair().getVertex() << ": " << "the closest intersection is now " << _data->edge.getPair().getVertex().getClosestIntersectionInSpace().getPoint() << std::endl;
							#endif
						}
					}else{//no
						_data->edge.getPair().getVertex().setClosestIntersectionInSpace(*this); // lets defined it
						#ifdef DEBUG
							std::cout << "=> feedback for " << _data->edge.getPair().getVertex() << ":" << "the closest intersection is " << _data->edge.getPair().getVertex().getClosestIntersectionInSpace().getPoint() << std::endl;
						#endif
					}
				}
			};
		private:
			struct Obj{
				Vertex<T> point;
				Edge<T> edge;
				Face<T> face;
				bool exist;
				Obj(Edge<T> e,Face<T> f) { //http://paulbourke.net/geometry/linefacet/
					edge = e; 
					face = f;
					#ifdef DEBUG
						std::cout << "interesction of" << e <<  " vs " << f << std::endl;
					#endif
					if (face.getNormal().isNull())
						face.computeNormal();
					T denominator = face.getA()*(edge.getA().getX()-edge.getB().getX());
					denominator += face.getB()*(edge.getA().getY()-edge.getB().getY());
					denominator += face.getC()*(edge.getA().getZ()-edge.getB().getZ());
					if (denominator!=(T)0) { //intersection exist (If the denominator is 0 then the line is parallel to the plane and they don't intersect.)
						T mu = face.getD() ;
						mu +=  face.getA()*edge.getA().getX() ;
						mu +=  face.getB()*edge.getA().getY() ;
						mu +=  face.getC()*edge.getA().getZ() ;
						mu /=  denominator;
						mu /= sqrt((double)(face.getA()*face.getA() + face.getB()*face.getB() + face.getC()*face.getC()));
						
						Vertex<T> ptmp =  edge.getA() + mu *(edge.getB() - edge.getA()); //P = P1 + mu (P2 - P1)
						bool liesOn = false;
						HalfEdge<T> firstHalfEdge = face.getHalfEdge();
						HalfEdge<T> halfEdge = firstHalfEdge;
						std::vector<Vertex<T> > vertex;
						int nvert=0;
						do{
							vertex.push_back(halfEdge.getVertex());
							nvert++;
							halfEdge = halfEdge.getNext();
						} while (halfEdge != firstHalfEdge);
						
						int i, j;
						i=0;
						j=nvert - 1;
						
						T tmp_x = abs(face.getNormal().getDx());
						T tmp_y = abs(face.getNormal().getDy());
						T tmp_z = abs(face.getNormal().getDz());
										
						if (tmp_z>tmp_x&&tmp_z>tmp_y) { // projection on Z axis
							#ifdef DEBUG
							std::cout << "projection on Z axis" << " (normal:" <<  face.getNormal() << ")" << std::endl;
							#endif
							for (i = 0, j = nvert-1; i < nvert; j = i++) {
								if ( ((vertex[i].getY()>ptmp.getY()) != (vertex[j].getY()>ptmp.getY())) && (ptmp.getX() < (vertex[j].getX()-vertex[i].getX()) * (ptmp.getY()-vertex[i].getY()) / (vertex[j].getY()-vertex[i].getY()) + vertex[i].getX()) )
									liesOn = !liesOn;
							}
						} else if (tmp_x>tmp_y&&tmp_x>tmp_z) { // projection on X axis
							#ifdef DEBUG
							std::cout << "projection on X axis" << " (normal:" <<  face.getNormal() << ")" << std::endl;
							#endif
							for (i = 0, j = nvert-1; i < nvert; j = i++) {	 
								if ( ((vertex[i].getY()>ptmp.getY()) != (vertex[j].getY()>ptmp.getY())) && (ptmp.getZ() < (vertex[j].getZ()-vertex[i].getZ()) * (ptmp.getY()-vertex[i].getY()) / (vertex[j].getY()-vertex[i].getY()) + vertex[i].getZ()) )
									liesOn = !liesOn;
							}
						} else { // projection on Y axis
							#ifdef DEBUG
							std::cout << "projection on Y axis" << " (normal:" <<  face.getNormal() << ")" << std::endl;
							#endif
							for (i = 0, j = nvert-1; i < nvert; j = i++) {	 
								if ( ((vertex[i].getZ()>ptmp.getZ()) != (vertex[j].getZ()>ptmp.getZ())) && (ptmp.getX() < (vertex[j].getX()-vertex[i].getX()) * (ptmp.getZ()-vertex[i].getZ()) / (vertex[j].getZ()-vertex[i].getZ()) + vertex[i].getX()) )
									liesOn = !liesOn;
							}	 
						}
						if (liesOn){ //the intersection of the line vs the face is inside the face
							point = ptmp;
							#ifdef DEBUG
								std::cout << "mu =" << mu << std::endl;
							#endif
							if ((mu<1)&&(mu>0)) {//For the intersection point to lie on the line segment, mu must be between 0 and denominator.
								exist = true;
							}else{// intersection point doesn't lie on the segment
								exist = false;
								#ifdef DEBUG
								std::cout << "intersection with the plan doesn't lie on the segment" << std::endl;
								#endif
							}
						}else{
							#ifdef DEBUG
							std::cout << "intersection with the plan doesn't lie on the face" << std::endl;
							#endif
							exist = false;
						}
					}else{
						#ifdef DEBUG
						std::cout << "intersection doesn't exist" << std::endl;
						#endif
						exist = false;
					} 
				};
			};
			boost::shared_ptr<Obj> _data;
	};
	
	template<class T> std::ostream& operator<< (std::ostream& o,const Intersection<T> i){
		if (i.isNull()) {
			return o << "(NULL)";
		}else{
			return o << "int(" << i.getPoint() << ")";
		}
	};
}
#endif
