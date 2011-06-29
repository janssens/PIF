/*
 * Polyhedron Intersection Framework
 * 
 * FileName: HalfEdge.hpp
 * Creation: 29.06.2011
 * Author: Gaëtan Janssens
 * Last Edit: 29.06.2011
 * 
 */
#ifndef HALFEDGE_H
#define HALFEDGE_H

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
//~ #include "Vertex.hpp"
//~ #include "HalfEdge.hpp"
//~ #include "Face.hpp"
 
namespace pif {
	
	template <class T> class Vertex;
	template <class T> class HalfEdge;
	template <class T> class Face;
	template <class T> class Intersection;

	template <class T> class HalfEdge {
		public:
			HalfEdge(void) {};
			HalfEdge(const Vertex<T> v): _data(new Obj(v)) {};
			HalfEdge(const Vertex<T> v,const Face<T> f,const HalfEdge<T> p,const HalfEdge<T> n) : _data(new Obj(v,f,p,n)) {};
			////
			//~ ~HalfEdge(){ if ((bool)_data) delete _data;};
			////
			Vertex<T> getVertex(void) const { 				
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h is not initialized, h.getVertex() not defined! " << std::endl;
					exit(1);
				}
				return _data->vertex; 
			};
			Face<T> getFace(void) const { 				
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h is not initialized, h.getFace() not defined! " << std::endl;
					exit(1);
				}
				if (_data->face.isNull()){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h as no associate face, h.getFace() not defined! (h:" << *this << ")" << std::endl;
					exit(1);
				}
				return _data->face; 
			};
			HalfEdge<T> getPair(void) const { 				
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h is not initialized, h.getPair() not defined! " << std::endl;
					exit(1);
				}
				if (_data->pair.isNull()){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h as no pair, h.getPair() not defined! (h:" << *this << ")" << std::endl;
					exit(1);	
				}
				return _data->pair; 
			};
			HalfEdge<T> getNext(void) const {				
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h is not initialized, h.getNext() not defined! " << std::endl;
					exit(1);
				}
				if (_data->next.isNull()){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h as no successor, h.getNext() not defined! (h:" << *this << ")" << std::endl;
					exit(1);	
				}
				return _data->next; 
			};
			bool isNull(void) const { return !(bool)_data;};
			////
			void addIntersection(const Intersection<T> i) {
					_data->listOfIntersection.push_back(i);
					if (_data->pair.isNull()){
						std::cerr << "/!\\ PIF Error: " << "HalfEdge h as no pair, h.getPair() not defined! (h:" << *this << ")" << std::endl;
						exit(1);	
					}
					_data->pair._data->listOfIntersection.push_back(i);
					//~ std::cout << "list back:" << _data->listOfIntersection.back() << std::endl;
			}
			
			std::list<Intersection<T> > getIntersections(void) const { return _data->listOfIntersection; }
			
			Intersection<T> getClosestIntersection(void) const { //get the closest Intersection of _data->Vertex
				typename std::list<Intersection<T> >::iterator it;
				it = _data->listOfIntersection.begin();
				Intersection<T> result = *it;
				T refDist;
				for (it++, refDist = dist(_data->vertex,result.getPoint());it != _data->listOfIntersection.end(); it++){
					T tmpDist = dist(_data->vertex,it->getPoint());
					if (tmpDist < refDist) {
						refDist = tmpDist;
						result = *it;
					}
				}
				return result;
			}
			
			Intersection<T> getFarestIntersection(void) const { //get the farest Intersection of _data->Vertex
				typename std::list<Intersection<T> >::iterator it;
				it = _data->listOfIntersection.begin();
				Intersection<T> result = *it;
				T refDist;
				for (;it != _data->listOfIntersection.end(); it++){
					T tmpDist = (T)0;
					if (tmpDist > refDist) {
						refDist = tmpDist;
						result = *it;
					}
				}
				return result;
			}
			////
			void setVertex(Vertex<T> v) {  
				if (!_data){
					boost::shared_ptr<struct Obj> sp(new Obj(v));
					_data = sp;
				}
				_data->vertex = v; 
			};
			void setFace(Face<T> f) {  
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "This HalfEdge h is not initialized, h.setFace() cannot be used!" << std::endl;
					exit(1);
				}
				_data->face = f;
			};
			void setPair(HalfEdge<T> he) {  
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "This HalfEdge h is not initialized, h.setPair() cannot be used!" << std::endl;
					exit(1);
				}
				_data->pair = he;
				he._data->pair = *this;
			};
			void setNext(HalfEdge<T> he) {  
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "This HalfEdge h is not initialized, h.setNext() cannot be used!" << std::endl;
					exit(1);
				}
				_data->next = he;
			};
			////
			bool operator!=(const HalfEdge<T> he)const 
			{
				return _data!=he._data;
			}
			bool operator==(const HalfEdge<T> he)const 
			{
				return _data==he._data;
			}
			bool operator >(const HalfEdge<T> he) const{
				if (this->getVertex()>he.getVertex())
					return true;
				else
					return false;
			}
			bool operator >=(const HalfEdge<T> he) const{
				if (this->getVertex()>=he.getVertex())
					return true;
				else
					return false;
			}
			bool operator <(const HalfEdge<T> he) const{
				if (this->getVertex()<he.getVertex())
					return true;
				else
					return false;
			}
			bool operator <=(const HalfEdge<T> he) const{
				if (this->getVertex()<=he.getVertex())
					return true;
				else
					return false;
			}
		private:
			struct Obj{
				Vertex<T> vertex;
				Face<T> face;
				HalfEdge<T> pair;
				HalfEdge<T> next;
				std::list<Intersection<T> > listOfIntersection;
				Obj(const Vertex<T> v) { vertex = v; };
				Obj(const Vertex<T> v,const Face<T> f,const HalfEdge<T> p,const HalfEdge<T> n) { vertex = v; face = f; pair= p; next = n; };
			};
			boost::shared_ptr<struct Obj> _data;
	};
	
	template<class T> std::ostream& operator<< (std::ostream& o,const HalfEdge<T> h){
		if (h.isNull()) {
			return o << "(NULL)";
		}else{
			return o << "-> " << h.getVertex() ;
		}
	};

		
}
#endif
