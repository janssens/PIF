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
	std::cout << "/////////\nVertex" << std::endl;
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	
	//// HalfEdge ////
	std::cout << "/////////\nHalfEdge" << std::endl;
	HalfEdge<montype> nullHalfEdge;
	std::cout << "null: " << nullHalfEdge << std::endl;
	//std::cout << "nullHalfEdge.getVertex():" << nullHalfEdge.getVertex() << std::endl;
	//std::cout << "nullHalfEdge.getFace():" << nullHalfEdge.getFace() << std::endl;
	//std::cout << "nullHalfEdge.getPair():" << nullHalfEdge.getPair() << std::endl;
	//std::cout << "nullHalfEdge.getNext():" << nullHalfEdge.getNext() << std::endl;
	nullHalfEdge.setVertex(a);
	std::cout << "nullHalfEdge.setVertex(a):" << nullHalfEdge << std::endl;
	std::cout << "nullHalfEdge.getVertex():" << nullHalfEdge.getVertex() << std::endl;
	//std::cout << "nullHalfEdge.getFace():" << nullHalfEdge.getFace() << std::endl;
	//std::cout << "nullHalfEdge.getPair():" << nullHalfEdge.getPair() << std::endl;
	//std::cout << "nullHalfEdge.getNext():" << nullHalfEdge.getNext() << std::endl;
	HalfEdge<montype> hea(a);
	HalfEdge<montype> heb(b);
	std::cout << "hea(a): " << hea << std::endl;
	std::cout << "heb(b): " << heb << std::endl;
	hea.setPair(heb);
	heb.setPair(hea);
	std::cout << "hea.setPair(heb);heb.setPair(hea);" << std::endl;
	std::cout << "hea.getPair():" << hea.getPair() << std::endl;
	std::cout << "heb.getPair():" << heb.getPair() << std::endl;
	
	
	//// Edge ////
	std::cout << "/////////\nEdge" << std::endl;
	Edge<montype> nullEdge;
	std::cout << "null: " << nullEdge << std::endl;
	Edge<montype> e(a,b);
	std::cout << "e(a,b): " << e << std::endl;
	Edge<montype> f = e.duplicate();
	std::cout << "f = duplicate(e): " << f << std::endl;
	b.setY(0);
	std::cout << "b.y = 0" << std::endl;
	std::cout << "e: " << e << std::endl;
	std::cout << "f: " << f << std::endl;
	Edge<montype> g1(hea);
	std::cout << "g1(hea): " << g1 << std::endl;
	Edge<montype> g2(heb);
	std::cout << "g2(heb): " << g2 << std::endl;
	std::cout << "g1 == g2: " << ((g1==g2) ? "true" : "false")  << std::endl;
	std::cout << "g1 == e: " << ((g1==e) ? "true" : "false")  << std::endl;
	std::cout << "g1 != e: " << ((g1!=e) ? "true" : "false")  << std::endl;
	return 0;
}

