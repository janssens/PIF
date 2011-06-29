/*
 * Polyhedron Intersection Framework
 * 
 * FileName: Vertex.hpp
 * Creation: 29.06.2011
 * Author: Gaëtan Janssens
 * Last Edit: 29.06.2011
 * 
 */
#ifndef VERTEX_H
#define VERTEX_H

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
#include "Intersection.hpp"
 
namespace pif {
		
	template <class T> class Vect;
	
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

		
}
#endif
