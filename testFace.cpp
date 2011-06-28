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
	
	//// Vertex ////
	Vertex<montype>  a((montype)1,(montype)0,(montype)0);
	Vertex<montype>  b((montype)0,(montype)1,(montype)0);
	Vertex<montype>  c((montype)0,(montype)0,(montype)1);
	
	//// Face ////
	std::cout << "\n\n/////////\nFace" << std::endl;
	Face<montype> nullFace;
	std::cout << "null: " << nullFace << std::endl;
	//std::cout << "nullFace.getNormal(): " << nullFace.getNormal() << std::endl;
	//std::cout << "nullFace.getD(): " << nullFace.getD() << std::endl;
	//nullFace.computeNormal();std::cout << "nullFace.computeNormal(): " << nullFace << std::endl;
	
	std::list<Edge<montype> > listOfEdges;
	std::cout << "a: " << a << ",\nb: " << b << ",\nc: " << c << std::endl;
	Edge<montype> e1(a,b);
	std::cout << "e1(a,b): " << e1 << std::endl;
	Edge<montype> e2(b,c);
	std::cout << "e2(b,c): " << e2 << std::endl;
	Edge<montype> e3(c,a);
	std::cout << "e3(c,a): " << e3 << std::endl;
	std::cout << "-e3: " << -e3 << std::endl;
	e1.getHalfEdge().setNext(e2.getHalfEdge());
	e2.getHalfEdge().setNext(e3.getHalfEdge());
	e3.getHalfEdge().setNext(e1.getHalfEdge());
	Face<montype> face(e1.getHalfEdge());
	std::cout << "face(e1,e2,e3): " << face << std::endl;
	a.setX(5);
	std::cout << "a.x = 5; face: " << face << std::endl;
	a.setX(1);
	std::cout << "a.x = 1; face: " << face << std::endl;
	std::cout << "face.getNormal(): " << face.getNormal() << std::endl;
	std::cout << "face.getD(): " << face.getD() << std::endl;
	std::cout << "face.getNormal().isNull(): " << ((face.getNormal().isNull())? "true" : "false") << std::endl;
	face.computeNormal();std::cout << "face.computeNormal(): " << std::endl;
	std::cout << "face.getNormal(): " << face.getNormal() << std::endl;
	std::cout << "face.getD(): " << face.getD() << std::endl;
	std::cout << "face.getNormal().isNull(): " << ((face.getNormal().isNull())? "true" : "false") << std::endl;
	
	return 0;
}

