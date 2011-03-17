/*
 * Polyhedron Intersection Framework
 * 
 * FileName: testVertex.cpp
 * Creation: 24.02.2011
 * Author: Gaëtan Janssens
 * Last Edit: 24.02.2011
 * 
 */

#include "Type.hpp"
#include <iostream>
#include <list>

using namespace pif;


int main(int argc, char **argv) {
	
	typedef double montype;
	
	//// Vertex ////
	std::cout << "/////////\nVertex" << std::endl;
	Vertex<montype>	nI;
	std::cout << "not initialized nI: " << nI << std::endl;
	//std::cout << "nI.getX(): " << nI.getX() << std::endl;
	//nI.setZ(0);
	//std::cout << "nI2 = nI.setZ(0): " << nI.getZ() << std::endl;
	//Vertex<montype>	nI2 = nI.duplicate();
	//std::cout << "nI.duplicate(): " << nI2 << std::endl;
	nI.setXYZ(1,2,3);
	std::cout << "nI.setXYZ(1,2,3): " << nI << std::endl;
	Vertex<montype>	nI2 = nI.duplicate();
	std::cout << "nI2 = nI.duplicate(): " << nI2 << std::endl;
	std::cout << "nI.getX(): " << nI.getX() << std::endl;
	nI.setZ(0);
	std::cout << "nI.setZ(0): " << nI.getZ() << std::endl;
	std::cout << "nI: " << nI << std::endl;
	std::cout << "nI2: " << nI2 << std::endl;
	std::cout << "(nI == nI2)?: " << ((nI == nI2)? "true" : "false") << std::endl;
	std::cout << "(nI != nI2)?: " << ((nI != nI2)? "true" : "false") << std::endl;
	std::cout << "(nI >= nI2)?: " << ((nI >= nI2)? "true" : "false") << std::endl;
	std::cout << "(nI > nI2)?: " << ((nI > nI2)? "true" : "false") << std::endl;
	std::cout << "(nI <= nI2)?: " << ((nI <= nI2)? "true" : "false") << std::endl;
	std::cout << "(nI < nI2)?: " << ((nI < nI2)? "true" : "false") << std::endl;
	
	Vertex<montype>  a((montype)1,(montype)0,(montype)0);
	Vertex<montype>  abis = a;
	Vertex<montype>  b((montype)0,(montype)1,(montype)0);
	Vertex<montype>  c = b.duplicate();
	std::cout << "a: " << a << std::endl;
	std::cout << "abis = a: " << abis << std::endl;
	std::cout << "(abis == a)?: " << ((abis == a)? "true" : "false") << std::endl;
	std::cout << "(abis != a)?: " << ((abis != a)? "true" : "false") << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "(a == b)?: " << ((a == b)? "true" : "false") << std::endl;
	std::cout << "(a != b)?: " << ((a != b)? "true" : "false") << std::endl;
	std::cout << "c = duplicate(b): " << c << std::endl;
	c.setZ(1);
	c.setY(0);
	std::cout << "c.z = 1, c.y = 0 :" << c << std::endl;
	std::cout << "b: " << b << std::endl;
	
	return 0;
}

