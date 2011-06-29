/*
 * Polyhedron Intersection Framework
 * 
 * FileName: Face.hpp
 * Creation: 29.06.2011
 * Author: Gaëtan Janssens
 * Last Edit: 29.06.2011
 * 
 */
#ifndef FACE_H
#define FACE_H

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
 
namespace pif {
	
	template <class T> class Vertex;
	template <class T> class Vect;
	template <class T> class Edge;
	template <class T> class HalfEdge;
	
	template <class T> class Face {
		public:
			Face(void) {};
			Face(HalfEdge<T> he) : _data(new Obj(he)) {
				HalfEdge<T> hE = _data->halfEdge;
				HalfEdge<T> firstHalfEdge = hE;
				do {
					hE.setFace(*this);
					hE = hE.getNext();
				} while (hE != firstHalfEdge);
			};
			
			bool isNull(void) const { return !(bool)_data;};
			////
			Vect<T> getNormal(void) const{ 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Face f is not initialized, f.getNormal() not defined! " << std::endl;
					exit(1);
				}
				return _data->normal; };
			HalfEdge<T> getHalfEdge(void) const{ 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Face f is not initialized, f.getHalfEdge() not defined! " << std::endl;
					exit(1);
				}
				return _data->halfEdge; 
			};
			T getD(void) const{ 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Face f is not initialized, f.getD() not defined! " << std::endl;
					exit(1);
				}
				return _data->d; 
			};
			T getA(void) const{ 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Face f is not initialized, f.getA() not defined! " << std::endl;
					exit(1);
				}
				return _data->normal.getDx();
			};
			T getB(void) const{ 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Face f is not initialized, f.getB() not defined! " << std::endl;
					exit(1);
				}
				return _data->normal.getDy();
			};
			T getC(void) const{ 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Face f is not initialized, f.getC() not defined! " << std::endl;
					exit(1);
				}
				return _data->normal.getDz();
			};
			////
			bool operator ==(const Face<T> f)const {
				return (f.getHalfEdge()==this->getHalfEdge());
			}
			////
			void computeNormal(void){
				if (!_data) {
					std::cerr << "/!\\ PIF Error: " << "Face f is not initialized, f.computeNormal() not defined! " << std::endl;
					exit(1);
				}else{
					Vertex<T> a = _data->halfEdge.getVertex();
					Vertex<T> b = _data->halfEdge.getNext().getVertex();
					HalfEdge<T> tmp = _data->halfEdge.getNext().getNext();
					while (_data->normal.isNull()){
						Vertex<T> c = tmp.getVertex();
						Vect<T> ab(a,b);
						Vect<T> ac(a,c);
						_data->normal = ab*ac;
					}
					_data->normal.normalise();
					_data->d = -(_data->normal.getDx()*a.getX()+_data->normal.getDy()*a.getY()+_data->normal.getDz()*a.getZ());
				}
			}
			
			
			void forEachHalfEdge( void (*fct) (void *,void *), void * data){
				if ((bool)_data) {
					HalfEdge<T> halfEdge = _data->halfEdge;
					do {
						fct((void *) &halfEdge, data);
						halfEdge = halfEdge.getNext();
					} while (halfEdge != _data->halfEdge);
				}
			}
			void forEachVertex( void (*fct) (void *,void *), void * data){
				if ((bool)_data) {
					HalfEdge<T> halfEdge = _data->halfEdge;
					Vertex<T> vertex = halfEdge.getVertex();
					do {
						fct((void *) &vertex, data);
						halfEdge = halfEdge.getNext();
						vertex = halfEdge.getVertex();
					} while (halfEdge != _data->halfEdge);
				}
			}

			
		private:
			struct Obj{
				HalfEdge<T> halfEdge;
				Vect<T> normal;
				T d;
				Obj(HalfEdge<T> he){ halfEdge = he; };
			};
			boost::shared_ptr<Obj> _data;
	};
	
	template<class T> std::ostream& operator<< (std::ostream& o,const Face<T> face){
		if (face.isNull()) {
			return o << "(NULL)";
		}else{
			HalfEdge<T> firstHalfEdge = face.getHalfEdge();
			HalfEdge<T> halfEdge = firstHalfEdge;
			int i=0;
			do {
				o << halfEdge.getVertex() << " ";
				halfEdge = halfEdge.getNext();
				i++;
			} while ((halfEdge != firstHalfEdge) && (i < MAXIMUM_NUMBER_OF_HALFEDGES ));
			if (i==MAXIMUM_NUMBER_OF_HALFEDGES){
				o << "/!\\ PIF Error: More than " << MAXIMUM_NUMBER_OF_HALFEDGES << " edges!";
				exit(1);
			}
			return o;
		}
	};

}
#endif
