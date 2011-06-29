/*
 * Polyhedron Intersection Framework
 * 
 * FileName: Edge.hpp
 * Creation: 29.06.2011
 * Author: Gaëtan Janssens
 * Last Edit: 29.06.2011
 * 
 */
#ifndef EDGE_H
#define EDGE_H

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
#include "Vertex.hpp"
#include "HalfEdge.hpp"
 
namespace pif {
	
		template <class T> class Edge {
		public:
			Edge(void) {};
			Edge(HalfEdge<T> he) : _data(new Obj(he)) {};
			Edge(const Vertex<T> a,const Vertex<T> b) : _data(new Obj(a,b)) {};
			////
			void addIntersection(const Intersection<T> i) {
					_data->halfedge.addIntersection(i);
			}
			////
			Vertex<T> getA(void) const { return _data->halfedge.getPair().getVertex(); }
			Vertex<T> getB(void) const { return _data->halfedge.getVertex(); }
			HalfEdge<T> getHalfEdge(void) const { return _data->halfedge; }
			HalfEdge<T> getPair(void) const { return _data->halfedge.getPair(); }
			
			std::list<Intersection<T> > getIntersections(void) const { return _data->halfedge.getIntersections(); }
			
			bool isNull(void) const { return !(bool)_data;};
			////
			Edge<T> duplicate(void) {
				Vertex<T> p1 = _data->halfedge.getPair().getVertex().duplicate();
				Vertex<T> p2 = _data->halfedge.getVertex().duplicate();
				Edge<T> e(p1,p2);
				return e;
			}
			
			Edge<T> operator-()const //Negative ab is ba
			{
				Edge<T> opos(_data->halfedge.getPair());
				return opos;
			}
			bool operator ==(const Edge<T> v)const {
				return (v.getA()==this->getA()&&v.getB()==this->getB());
			}
			bool operator !=(const Edge<T> v)const {
				return (v.getA()!=this->getA()||v.getB()!=this->getB());
			}
			bool operator >(const Edge<T> v) const{
				if (this->getA()>v.getA())
					return true;
				else if(this->getA()==v.getA())
					return (this->getB()>v.getB());
				else
					return false;
			}
			bool operator >=(const Edge<T> v) const{
				if (this->getA()>v.getA())
					return true;
				else if(this->getA()==v.getA())
					return (this->getB()>=v.getB());
				else
					return false;
			}
			bool operator <(const Edge<T> v) const{
				if (this->getA()<v.getA())
					return true;
				else if(this->getA()==v.getA())
					return (this->getB()<v.getB());
				else
					return false;
			}
			bool operator <=(const Edge<T> v) const{
				if (this->getA()<v.getA())
					return true;
				else if(this->getA()==v.getA())
					return (this->getB()<=v.getB());
				else
					return false;
			}
		private:
			struct Obj{
				HalfEdge<T> halfedge;
				Obj(const HalfEdge<T> he) { 
					if (he.getVertex()>he.getPair().getVertex())
						halfedge = he;
					else
						halfedge = he.getPair();
				};
				Obj(const Vertex<T> a, const Vertex<T> b) {
					HalfEdge<T> hea(a);
					HalfEdge<T> heb(b);
					if (a>b)
						halfedge = hea;
					else
						halfedge = heb;
					heb.setPair(hea);
					//~ hea.setPair(heb);
				};
			};
			boost::shared_ptr<struct Obj> _data;
	};
	

	template<class T> std::ostream& operator<< (std::ostream& o,const Edge<T> v){
		if (v.isNull()) {
			return o << "(NULL)";
		}else{
			return o << "[" << v.getA() << "," << v.getB() << "]" ;
		}
	};
		
}
#endif
