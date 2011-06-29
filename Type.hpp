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

#include "Vertex.hpp"
#include "Vect.hpp"
#include "HalfEdge.hpp"
#include "Edge.hpp"
#include "Face.hpp"
#include "Mesh.hpp"
#include "Intersection.hpp"
 
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

}
#endif
