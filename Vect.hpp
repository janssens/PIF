/*
 * Polyhedron Intersection Framework
 * 
 * FileName: Vect.hpp
 * Creation: 29.06.2011
 * Author: Gaëtan Janssens
 * Last Edit: 29.06.2011
 * 
 */
#ifndef VECT_H
#define VECT_H

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
		
}
#endif
