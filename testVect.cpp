/*
 * Polyhedron Intersection Framework
 * 
 * FileName: main.cpp
 * Creation: 04.02.2011
 * Author: Gaëtan Janssens
 * Last Edit: 04.02.2011
 * 
 */

#include "Type.hpp"
#include <iostream>
#include <list>

using namespace pif;


int main(int argc, char **argv) {
	
	typedef double montype;

	//// Vect ////
	std::cout << "\n\n/////////\nVect" << std::endl;
	Vect<montype> nullVect;
	std::cout << "null: " << nullVect << std::endl;
	//std::cout << "nullVect.getDx(): " << nullVect.getDx() << std::endl;
	//nullVect.setDx(0);
	//std::cout << "nullVect.setDx(0): " << nullVect << std::endl;
	//std::cout << "-nullVect: " << -nullVect << std::endl;
	//std::cout << "nullVect*nullVect: " << nullVect*nullVect << std::endl;
	//std::cout << "nullVect*2: " << nullVect*2 << std::endl;
	//Vect<montype> nullVect2 = nullVect.duplicate();
	
	Vect<montype> u((montype)1,(montype)0,(montype)0);
	Vect<montype> v((montype)0,(montype)1,(montype)0);
	std::cout << "u: " << u << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "u+v: " << u + v << std::endl;
	std::cout << "u-v: " << u - v << std::endl;
	std::cout << "v-u: " << v - u << std::endl;
	std::cout << "8*(u+v): " << (montype)8*(u+v) << std::endl;
	std::cout << "6*u-3*v: " << (montype)6*u-(montype)3*v << std::endl;
	std::cout << "u*v: " << u*v << std::endl;
	std::cout << "u*(3*u): " << u*((montype)3*u) << std::endl;
	std::cout << "u.dot(v): " << u.dot(v) << std::endl;
	std::cout << "u.dot(9*u): " << u.dot((montype)9*u) << std::endl;

	return 0;
}

