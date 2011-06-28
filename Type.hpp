/*
 * Polyhedron Intersection Framework
 * 
 * FileName: Type.hpp
 * Creation: 28.01.2011
 * Author: Gaëtan Janssens
 * Last Edit: 27.06.2011
 * 
 */
#ifndef TYPE_H
#define TYPE_H

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
 
#define MAXIMUM_NUMBER_OF_HALFEDGES 150
 
 
 // T must include (+ - * /)
 
namespace pif {
		
	template <class T> class Vertex;
	template <class T> class HalfEdge;
	template <class T> class Edge;
	template <class T> class Vect;
	template <class T> class Face;
	template <class T> class Intersection;

	template <class T> T abs(T value){
			if (value>(T)0)
				return value;
			else
				return -value;
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	template<class T> class Vertex {
		struct Obj;
		
		public:
			Vertex() {}; 
			Vertex(T x,T y,T z) : _data(new Obj(x,y,z)){};
			////
			T getX(void) const { 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex v is not initialized, v.getX() undefined!" << std::endl;
					exit(1);
				}
				return _data->x;
			};
			T getY(void) const { 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex v is not initialized, v.getY() undefined!" << std::endl;
					exit(1);
				}
				return _data->y; 
			};
			T getZ(void) const { 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex v is not initialized, v.getZ() undefined!" << std::endl;
					exit(1);
				}
				return _data->z; 
			};
			bool isNull(void) const { return !(bool)_data;};
			////
			void setX(T x) { 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex v is not initialized, v.setX() cannot be used!" << std::endl;
					exit(1);
				}
				_data->x = x; 
			};
			void setY(T y) {  
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex v is not initialized, v.setY() cannot be used!" << std::endl;
					exit(1);
				}
				_data->y = y;
			};
			void setZ(T z) {  
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex v is not initialized, v.setZ() cannot be used!" << std::endl;
					exit(1);
				}
				_data->z = z; 
			};
			void setXYZ(T x,T y,T z) {  
				boost::shared_ptr<Obj> sp(new Obj(x,y,z));
				_data = sp;
			};
			////
			Vertex<T> duplicate(void) {
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex v is not initialized, it cannot be duplicate!" << std::endl;
					exit(1);
				}
				Vertex p(_data->x,_data->y,_data->z);
				return p;
			};
			////
			bool isClosestIntersectionInSpaceDefined(void) const {				
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h is not initialized, h.isClosestIntersectionInSpaceDefined() not defined! " << std::endl;
					exit(1);
				}
				if (_data->closestIntersectionInSpace.isNull()){
					return false;	
				}else{
					return true;
				}
			};
			Intersection<T> getClosestIntersectionInSpace(void) const {				
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h is not initialized, h.getClosestIntersectionInSpace() not defined! " << std::endl;
					exit(1);
				}
				if (_data->closestIntersectionInSpace.isNull()){
					std::cerr << "/!\\ PIF Error: " << "HalfEdge h as no known close intersection, h.getClosestIntersectionInSpace() not defined! (h:" << *this << ")" << std::endl;
					exit(1);	
				}
				return _data->closestIntersectionInSpace; 
			};
			void setClosestIntersectionInSpace(Intersection<T> i) {				
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "This HalfEdge h is not initialized, h.setClosestIntersectionInSpace() cannot be used!" << std::endl;
					exit(1);
				}
				_data->closestIntersectionInSpace = i;
			};
			bool isInside(void) const {
				if (_data->closestIntersectionInSpace.isNull()){
					return false;
				}else{
					Vect<T> v1(*this,_data->closestIntersectionInSpace.getPoint());
					Vect<T> v2 = _data->closestIntersectionInSpace.getFace().getNormal();
					return (bool)(v1.dot(v2)>0);
				}
			};
			////
			Vertex<T> operator+(const Vertex<T> v)const {
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex is not initialized, it should not be used! (operator +)" << std::endl;
					exit(1);
				}
				Vertex<T> w(_data->x+v.getX(),_data->y+v.getY(),_data->z+v.getZ());
				return w;
			}
			Vertex<T> operator-(const Vertex<T> v)const {
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex is not initialized, it should not be used! (operator -)" << std::endl;
					exit(1);
				}
				Vertex<T> w(_data->x-v.getX(),_data->y-v.getY(),_data->z-v.getZ());
				return w;
			}
			Vertex<T> operator*(const T k)const //Multiplication by Scalar
			{
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex is not initialized, it should not be used! (operator *)" << std::endl;
					exit(1);
				}
				Vertex<T> w(k*_data->x,k*_data->y,k*_data->z);
				return w;
			}
			Vertex<T> operator-()const //Negative Of A Scaler
			{
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vertex is not initialized, it should not be used! (operator -)" << std::endl;
					exit(1);
				}
				Vertex<T> w(-_data->x,-_data->y,-_data->z);
				return w;
			}
			bool operator ==(const Vertex<T> v)const {
				return _data==v._data;
			}
			bool operator !=(const Vertex<T> v)const {
				return _data!=v._data;
			}
			bool operator >(const Vertex<T> v) const{
				return (_data->x>v.getX())||((_data->x==v.getX())&&(_data->y>v.getY()))||((_data->x==v.getX())&&(_data->y==v.getY())&&(_data->z>v.getZ()));
			}
			bool operator >=(const Vertex<T> v) const{
				return (_data->x>v.getX())||((_data->x==v.getX())&&(_data->y>v.getY()))||((_data->x==v.getX())&&(_data->y==v.getY())&&(_data->z>=v.getZ()));
			}
			bool operator <(const Vertex<T> v) const{
				return (_data->x<v.getX())||((_data->x==v.getX())&&(_data->y<v.getY()))||((_data->x==v.getX())&&(_data->y==v.getY())&&(_data->z<v.getZ()));
			}
			bool operator <=(const Vertex<T> v) const{
				return (_data->x<v.getX())||((_data->x==v.getX())&&(_data->y<v.getY()))||((_data->x==v.getX())&&(_data->y==v.getY())&&(_data->z<=v.getZ()));
			}
			
		private:
			struct Obj{
				T x;
				T y;
				T z;
				Intersection<T> closestIntersectionInSpace;
				Obj(T a,T b,T c) { x = a; y = b; z = c;};
			};
			boost::shared_ptr<Obj> _data;
	};
	
	template<class T> Vertex<T> operator*(const T k,const Vertex<T> v){
		return v * k;
	}
	
	template<class T> std::ostream& operator<< (std::ostream& o,const Vertex<T> v){
		if (v.isNull()) {
			return o << "(NULL)";
		}else{
			return o << v.getX() << " " << v.getY() << " " << v.getZ();
		}
	};
	
	template<class T> T norm(const Vertex<T> v){
		return v.getX()*v.getX()+v.getY()*v.getY()+v.getZ()*v.getZ();
	};
	
	template<class T> T dist(const Vertex<T> v1,const Vertex<T> v2){
		return norm(v2-v1);
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
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
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	template<class T> class Vect {
		public:
			Vect() {}; 
			Vect(T x,T y,T z) : _data(new Obj(x,y,z)){};
			Vect(Vertex<T> from,Vertex<T> to) : _data(new Obj(to.getX() - from.getX(),to.getY() - from.getY(),to.getZ() - from.getZ())){};
			bool isNull(void) const { return !(bool)_data;};
			////
			T getDx(void) const { 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect v is not initialized, v.getDx() not defined! " << std::endl;
					exit(1);
				}
				return _data->dx; 
			};
			T getDy(void) const { 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect v is not initialized, v.getDy() not defined! " << std::endl;
					exit(1);
				}
				return _data->dy; 
			};
			T getDz(void) const { 
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect v is not initialized, v.getDz() not defined! " << std::endl;
					exit(1);
				}
				return _data->dz; 
			};
			////
			void setDx(T x) {  
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect v is not initialized, v.setDx() cannot be used!" << std::endl;
					exit(1);
				}
				_data->dx = x; 
			};
			void setDy(T y) {   
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect v is not initialized, v.setDy() cannot be used!" << std::endl;
					exit(1);
				}
				_data->dy = y; 
			};
			void setDz(T z) {   
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect v is not initialized, v.setDz() cannot be used!" << std::endl;
					exit(1);
				}
				_data->dz = z; 
			};
			////
			Vect<T> duplicate(void) {
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect v is not initialized, it cannot be duplicate!" << std::endl;
					exit(1);
				}
				Vect<T> v(_data->dx,_data->dy,_data->dz);
				return v;
			};
			
			void normalise(void) {
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect v is not initialized, it cannot be normalise!" << std::endl;
					exit(1);
				}
				double length = sqrt((double)_data->dx*(double)_data->dx + (double)_data->dy*(double)_data->dy + (double)_data->dz*(double)_data->dz);
				_data->dx /= (T)length;
				_data->dy /= (T)length;
				_data->dz /= (T)length;
			};
			////
			Vect<T> operator+(const Vect<T> v)const {
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect is not initialized, it should not be used! (operator +)" << std::endl;
					exit(1);
				}
				Vect<T> w(_data->dx+v.getDx(),_data->dy+v.getDy(),_data->dz+v.getDz());
				return w;
			}
			Vect<T> operator-(const Vect<T> v)const {
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect is not initialized, it should not be used! (operator -)" << std::endl;
					exit(1);
				}
				Vect<T> w(_data->dx-v.getDx(),_data->dy-v.getDy(),_data->dz-v.getDz());
				return w;
			}
			Vect<T> operator*(const T k)const //Multiplication by Scalar
			{
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect is not initialized, it should not be used! (operator *)" << std::endl;
					exit(1);
				}
				Vect<T> w(k*_data->dx,k*_data->dy,k*_data->dz);
				return w;
			}
			
			Vect<T> operator*(const Vect<T> v)const //Cross Product
			{
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect is not initialized, it should not be used! (Cross Product)" << std::endl;
					exit(1);
				}
				Vect<T> w((_data->dy * v.getDz()) - (_data->dz * v.getDy()),
						(_data->dz * v.getDx()) - (_data->dx * v.getDz()),
						(_data->dx * v.getDy()) - (_data->dy * v.getDx()));
				return w;
			}
			Vect<T> operator-()const //Negative Of A Scaler
			{
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect is not initialized, it should not be used! (operator -)" << std::endl;
					exit(1);
				}
				Vect<T> w(-_data->dx,-_data->dy,-_data->dz);
				return w;
			}
			T dot(Vect<T> v)const //Dot Product
			{
				if (!_data){
					std::cerr << "/!\\ PIF Error: " << "Vect is not initialized, it should not be used! (dot)" << std::endl;
					exit(1);
				}
				return _data->dx* v.getDx()+_data->dy* v.getDy()+_data->dz* v.getDz();
			}

		private:
			struct Obj{
				T dx;
				T dy;
				T dz;
				Obj(T a,T b,T c) { dx = a; dy = b; dz = c; };
			};
			boost::shared_ptr<Obj> _data;
	};
	
	template<class T> Vect<T> operator*(const T k,const Vect<T> v){
		return v * k;
	}
	
	template<class T> std::ostream& operator<< (std::ostream& o,const Vect<T> v){
		if (v.isNull()) {
			return o << "(NULL)";
		}else{
			return o << v.getDx() << " " << v.getDy() << " " << v.getDz();
		}
	};
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
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
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	template <class T> class Mesh {
		public:
			Mesh(): _vertex_count(0),_face_count(0),_edge_count(0) {};
			////
			std::list<Face<T> > getFaces(void) const {
				return _faces;
			}
			void setVertexCount(int nb){
				_vertex_count = nb;
			}
			void setFaceCount(int nb){
				_face_count = nb;
			}
			void setEdgeCount(int nb){
				_edge_count = nb;
			}		
			int getVertexCount(void) const{
				return _vertex_count;
			}
			int getFaceCount(void) const{
				return _face_count;
			}
			int getEdgeCount(void) const{
				return _edge_count;
			}
			void showStat(void){
				std::cout << "_vertex_count:" << _vertex_count << std::endl;
				std::cout << "_face_count:" << _face_count << std::endl;
				std::cout << "_edge_count:" << _edge_count << std::endl;
			}			
			void stat(void){
				typename std::list<Face<T> >::iterator it;
				_face_count = 0;
				int halfedge_count = 0;
				std::vector<Vertex<T> > vertex_array;
				for (it=_faces.begin(); it!=_faces.end(); ++it){
					//~ std::cout << "face:" << *it << std::endl << std::endl;
					HalfEdge<T> firstHalfEdge = it->getHalfEdge();
					HalfEdge<T> halfEdge = firstHalfEdge;
					do {
						Vertex<T> v = halfEdge.getVertex();
						typename std::vector<Vertex<T> >::iterator itv;
						if (!vertex_array.empty()){
							for ( itv=vertex_array.begin() ; itv != vertex_array.end()  && v < *itv;)
								itv++;
							if (*itv!=v){ // v > *itv
								vertex_array.insert ( itv , v );
							}
						}else{
							vertex_array.push_back(v);
						}
						//~ std::cout << std::endl;
						//~ for ( itv=vertex_array.begin() ; itv != vertex_array.end();itv++)
							//~ std::cout << *itv << ",";
						halfEdge = halfEdge.getNext();
						halfedge_count++;
					} while (halfEdge != firstHalfEdge);
					//~ _face_count++;
					//~ std::cout << _face_count;
				}
				_vertex_count = vertex_array.size();
				_edge_count = halfedge_count/2;
				//~ std::cout << "_vertex_count:" << _vertex_count << std::endl;
				//~ std::cout << "_face_count:" << _face_count << std::endl;
				//~ std::cout << "_edge_count:" << _edge_count << std::endl;
			}
			////
			
			void forEachFace( void (*fct) (void *,void *), void * data = NULL){
				typename std::list<Face<T> >::iterator it;
				for (it=_faces.begin(); it!=_faces.end(); ++it){
					fct((void *) &(*it), data);
				}
			}
			
			void forEachEdge( void (*fct) (void *,void *), void * data = NULL){
				typename std::list<Face<T> >::iterator itFace;
				std::vector<Edge<T> > alreadySeen;
				for (itFace=_faces.begin(); itFace!=_faces.end(); ++itFace){ // for all face
					//~ std::cout << "dealing with face:" << *itFace << std::endl;
					HalfEdge<T> firstHalfEdge = itFace->getHalfEdge();
					HalfEdge<T> currentHalfEdge = firstHalfEdge;
					do { // for all halfedges on the face
						Edge<T> e(currentHalfEdge);
						int max = alreadySeen.size();
						int tmp = 0;
						for (; (tmp<max) && (alreadySeen.at(tmp)<e); tmp ++){ } //check if the Edge is already seen
						if (tmp==max||alreadySeen.at(tmp)!=e) //Edge is not already seen
						{
							//~ std::cout << "just seen:" << e << std::endl;
							fct((void *) &e, data);
							alreadySeen.insert(alreadySeen.begin()+tmp,e); //this Edge is now seen
						}
						currentHalfEdge = currentHalfEdge.getNext();
					} while (currentHalfEdge != firstHalfEdge);
				}
			}
			
			
			void forEachHalfEdge( void (*fct) (void *,void *), void * data = NULL){
				typename std::list<Face<T> >::iterator it;
				for (it=_faces.begin(); it!=_faces.end(); ++it){
					//~ std::cout << *it << std::endl;
					it->forEachHalfEdge(fct,data);
				}
			}
			
			void forEachVertex( void (*fct) (void *,void *), void * data = NULL){
				typename std::list<Face<T> >::iterator itFace;
				std::vector<Vertex<T> > alreadySeen;
				for (itFace=_faces.begin(); itFace!=_faces.end(); ++itFace){ // for all face
					//~ std::cout << "dealing with face:" << *itFace << std::endl;
					HalfEdge<T> firstHalfEdge = itFace->getHalfEdge();
					HalfEdge<T> currentHalfEdge = firstHalfEdge;
					do { // for all halfedges on the face
						Vertex<T> v = currentHalfEdge.getVertex();
						int max = alreadySeen.size();
						int tmp = 0;
						for (; (tmp<max) && (alreadySeen.at(tmp)<v); tmp ++){ } //check if the Edge is already seen
						if (tmp==max||alreadySeen.at(tmp)!=v) //Edge is not already seen
						{
							//~ std::cout << "just seen:" << e << std::endl;
							fct((void *) &v, data);
							alreadySeen.insert(alreadySeen.begin()+tmp,v); //this Edge is now seen
						}
						currentHalfEdge = currentHalfEdge.getNext();
					} while (currentHalfEdge != firstHalfEdge);
				}
			}
			
			void push(Face<T> f) {
				_faces.push_back(f);
			}
			void addFace(Face<T> f) { // same as push
				_faces.push_back(f);
			}
		private:
			std::list<Face<T> > _faces;
			int _vertex_count;
			int _face_count;
			int _edge_count;
	};
	
	template<class T> std::ostream& operator<< (std::ostream& o,const Mesh<T> mesh){
		o << "OFF" << std::endl;
		o << mesh.getVertexCount() << " " <<  mesh.getFaceCount() << " " << mesh.getEdgeCount() << std::endl;
		if (mesh.getVertexCount()>0) {
			typename std::list<Face<T> >::iterator it;
			std::vector<Vertex<T> > vertex_array;
			std::list<Face<T> > faces = mesh.getFaces();
			for (it=faces.begin(); it!=faces.end(); it++){ // for each face
				HalfEdge<T> firstHalfEdge = it->getHalfEdge();
				HalfEdge<T> halfEdge = firstHalfEdge;
				do { // for each halfedge in the face
				
					Vertex<T> v = halfEdge.getVertex();
					//~ std::cout << "reading: " << v << std::endl;
					typename std::vector<Vertex<T> >::iterator itv;
					if (!vertex_array.empty()){
						for ( itv=vertex_array.begin() ; itv != vertex_array.end()  &&  v < *itv;)
							itv++;
						if(itv == vertex_array.end()){
							vertex_array.push_back(v);
						}else if (v > *itv){
							vertex_array.insert ( itv , v );
						}
					}else{
						vertex_array.push_back(v);
					}
					halfEdge = halfEdge.getNext();
				} while (halfEdge != firstHalfEdge);
			}
			
			int tmpint=0;
			int max = vertex_array.size();
			for ( int i=0; i < max; i++)
				o << vertex_array[i] << std::endl;
			for (it=faces.begin(); it!=faces.end(); ++it){
				int nbOfVertex = 0;
				HalfEdge<T> firstHalfEdge = it->getHalfEdge();
				HalfEdge<T> halfEdge = firstHalfEdge;
				std::stringstream ss (std::stringstream::in | std::stringstream::out);
				int indextmp ;
				do {
					indextmp = 0;
					Vertex<T> v = halfEdge.getVertex();
					typename std::vector<Vertex<T> >::iterator itv;
					for ( itv=vertex_array.begin() ; itv != vertex_array.end()  && v < *itv;itv++)
						indextmp++;
					if (*itv!=v){ // v > *itv
						std::cout << "what the hell!" << std::endl; //vertex not found, but should be!
					}else{
						ss << indextmp << " ";
					}
					halfEdge = halfEdge.getNext();
					nbOfVertex++;
				} while (halfEdge != firstHalfEdge);
				o << nbOfVertex << " " << ss.str() << std::endl;
			}
		}
		return o;
	};
	
	
	template<class T> void operator>> (std::ifstream& fichier,Mesh<T> &myMesh){
		std::string contenu;  // to contain the read line
        std::getline(fichier, contenu);  // read the line
        if (contenu.compare(0,3,"OFF") != 0){
			std::cerr << "/!\\ PIF Error: The file you are trying to read is not an regular OFF file." << std::endl;
			exit(1);
		}
       
        int VertexCount;
        int FaceCount;
        int EdgeCount;
        fichier >> VertexCount;
        fichier >> FaceCount;
        fichier >> EdgeCount;
        #ifdef DEBUG
        std::cout << "VertexCount:" << VertexCount << std::endl;
        std::cout << "FaceCount:" << FaceCount << std::endl;
        std::cout << "EdgeCount:" << EdgeCount << std::endl;
        #endif

        std::getline(fichier, contenu);  //get the end of the line
		
		typename std::vector<Vertex<T> > vertex;
		for(int i = 0; i < VertexCount; i++){ // for all vertex
			T x,y,z;
			fichier >> x;
			fichier >> y;
			fichier >> z;
			std::getline(fichier, contenu); //get the end of the line
			Vertex<T> v(x,y,z);
			vertex.push_back(v);
			#ifdef DEBUG
			std::cout << "#" << i << ":" << v << std::endl;
			#endif
		}
		
		
		typename std::vector<Face<T> > faces;
		
		typename std::vector<std::vector<HalfEdge<T> > > link;
		for(int i = 0; i < VertexCount; i++){
			std::vector<HalfEdge<T> > vect;
			link.push_back(vect);
		}
		for(int i = 0; i < FaceCount; i++){ // for all Face
			int nbOfVertexInThisFace = 0;
			fichier >> nbOfVertexInThisFace;
			int VertexIndex = 0;
			fichier >> VertexIndex;
			int firstVertexIndex=VertexIndex;
			int previousVertexIndex = 0;
			int nbOfHalfEdges = 0;;
			int indexOfFirstVertex = VertexIndex;
			Vertex<T> firstVertex = vertex.at(indexOfFirstVertex);
			HalfEdge<T> firstsHalfEdge(firstVertex);
			HalfEdge<T> previousHalfEdge = firstsHalfEdge;
			HalfEdge<T> tmp_he;
			bool pairFound;
			int j = 1; //index of read Vertex
			do{ //for all Vertex in the face
				previousVertexIndex = VertexIndex;
				fichier >> VertexIndex;
				#ifdef DEBUG
				std::cout << previousVertexIndex << "->" << VertexIndex << " (boucle)" << std::endl;
				#endif
				HalfEdge<T> currentHalfEdge(vertex.at(VertexIndex));
				nbOfHalfEdges = link[VertexIndex].size();
				pairFound = false;
				if (nbOfHalfEdges){ // there is at least one halfedge going somewhere from here
					#ifdef DEBUG
					std::cout << nbOfHalfEdges << " halfedge starting from " << VertexIndex << std::endl;
					#endif
					for (int k=0; (k < nbOfHalfEdges)&&(!pairFound); k++){ //lets find the pair
						tmp_he = link[VertexIndex][k];
						if (tmp_he.getVertex()==vertex.at(previousVertexIndex)) { // the pair exist!
							currentHalfEdge.setPair(tmp_he);
							#ifdef DEBUG
							std::cout << "->" << VertexIndex << "(" << currentHalfEdge << ") paired with " << "->" << previousVertexIndex << "(" << tmp_he << ")" << std::endl;
							#endif
							link[VertexIndex].erase(link[VertexIndex].begin()+k);//the two vertex are paired, we dont need to keep trace of them anymore.
							pairFound = true; //leave the for loop with result found
						}
					}
				}
				if (!pairFound) { // the pair do not exist yet!
					link[previousVertexIndex].push_back(currentHalfEdge); // this new halfedge is going from previousVertex to Vertex, we keep track of that
					#ifdef DEBUG
					std::cout << "we keep track of " << previousVertexIndex << "->" << VertexIndex << std::endl;
					#endif
				}
				previousHalfEdge.setNext(currentHalfEdge);
				previousHalfEdge = currentHalfEdge;
				j++;//we just read one more Vertex
			} while (j < nbOfVertexInThisFace);
			#ifdef DEBUG
			std::cout << "->" << VertexIndex << "->" << indexOfFirstVertex << " (hors boucle)" << std::endl;
			#endif
			previousHalfEdge.setNext(firstsHalfEdge);// and the cycle is complete
			nbOfHalfEdges = link[indexOfFirstVertex].size();// all the half edge who start here
			pairFound = false;
			if (nbOfHalfEdges){ // there is at least one halfedge who start here
				#ifdef DEBUG
				std::cout << nbOfHalfEdges << " halfedge starting from " << indexOfFirstVertex << std::endl;
				#endif
				for (int k=0; (k < nbOfHalfEdges)&&(!pairFound); k++){ //lets find the pair
					tmp_he = link[indexOfFirstVertex][k];
					if (tmp_he.getVertex()==vertex.at(VertexIndex)) { // the pair exist!
							#ifdef DEBUG
							std::cout << indexOfFirstVertex << "(" << firstsHalfEdge << ") paired with " << "->" << VertexIndex << "(" << tmp_he << ")" << std::endl;
							#endif
							firstsHalfEdge.setPair(tmp_he);
							#ifdef DEBUG
							tmp_he.setPair(firstsHalfEdge);
							#endif
							link[indexOfFirstVertex].erase(link[indexOfFirstVertex].begin()+k);//the two vertex are paired, we dont need to keep trace of them anymore.
							pairFound = true; //leave the for loop with result found
					}
				}
			}
			if (!pairFound) { // the pair do not exist yet!
				link[VertexIndex].push_back(firstsHalfEdge);// we know from were the first half edge was going, and we keep track of that
				#ifdef DEBUG
				std::cout << "we keep track of " << VertexIndex << "->" << indexOfFirstVertex << std::endl;
				#endif
			}
			Face<T> face(firstsHalfEdge);
			
			HalfEdge<T> tmpHalfEdge = firstsHalfEdge;
			do {
				tmpHalfEdge.setFace(face); //associer 
				tmpHalfEdge = tmpHalfEdge.getNext();
			} while (tmpHalfEdge != firstsHalfEdge); // pour chaque halfhedge de la face
			
			myMesh.push(face);
			#ifdef DEBUG
			std::cout << "face:" << face << std::endl;
			#endif
			std::getline(fichier, contenu); //get the end of the line
		}
		int leftOver=0;
		for(int i = 0; i < VertexCount; i++){
			leftOver += link[i].size(); 
			link[i].clear();
		}
		link.clear();
		if (leftOver>0)
			std::cout << "/!\\" << leftOver << " HalfEdge where not paired!"  << std::endl;
		
		myMesh.setVertexCount(VertexCount);
		myMesh.setEdgeCount(EdgeCount);
		myMesh.setFaceCount(FaceCount);
		//~ std::cout << myMesh << std::endl;
		//~ return myMesh; 
	};
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	
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
				Obj(Edge<T> e,Face<T> f) { 
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
