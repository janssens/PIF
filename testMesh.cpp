/*
 * Polyhedron Intersection Framework
 * 
 * FileName: testMesh.cpp
 * Creation: 04.02.2011
 * Author: Gaëtan Janssens
 * Last Edit: 04.02.2011
 * 
 */

#include "Type.hpp"

using namespace pif;

template<class T> void printFace(void *face,void *data){
		Face<T> *f = (Face<T> *) face;
		int *tmp = (int*) data;
		std::cout << "my custom face print: " << *f << " (" << *tmp << ")" << std::endl; 
}
template<class T> void printFaceVsEdge(void *face,void *halfedge){
		Face<T> *f = (Face<T> *) face;
		HalfEdge<T> *he = (HalfEdge<T>*) halfedge;
		std::cout << "my custom face print: " << *f << " vs " << *he << std::endl; 
}
template<class T> void printEdge(void *edge,void *nothing){
		Edge<T> *e = (Edge<T>*) edge;
		std::cout << *e << std::endl; 
}
template<class T> void printHalfEdge(void *halfEdge,void *nothing){
		HalfEdge<T> *he = (HalfEdge<T>*) halfEdge;
		std::cout << *he << std::endl; 
}
template<class T> void printHalfEdge2(void *halfEdge,void *nothing){
		HalfEdge<T> *he = (HalfEdge<T>*) halfEdge;
		std::cout << *he << std::endl;
		std::cout << "next:" << he->getNext() << std::endl;
		std::cout << "pair:" << he->getPair() << std::endl;   
		Edge<T> e(*he);
		std::cout << e << std::endl;
		std::cout << std::endl;  
}


int main(int argc, char **argv) {
	
	typedef double montype;
	
	//// Vertex ////
	Vertex<montype>  a((montype)1,(montype)0,(montype)0);
	std::cout << "a: " << a << std::endl;
	Vertex<montype>  b((montype)0,(montype)1,(montype)0);
	std::cout << "b: " << b << std::endl;
	Vertex<montype>  c((montype)0,(montype)0,(montype)1);
	std::cout << "c: " << c << std::endl;
	Vertex<montype>  d((montype)0,(montype)0,(montype)0);
	std::cout << "d: " << d << std::endl;
	
	//// Edge ////
	std::cout << "/////////\nEdge" << std::endl;
	Edge<montype> e1(a,b);
	std::cout << "e1(a,b): " << e1 << std::endl;
	Edge<montype> e2(b,c);
	std::cout << "e2(b,c): " << e2 << std::endl;
	Edge<montype> e3(c,a);
	std::cout << "e3(c,a): " << e3 << std::endl;
	Edge<montype> e4(a,d);
	std::cout << "e4(a,d): " << e4 << std::endl;
	Edge<montype> e5(b,d);
	std::cout << "e5(b,d): " << e5 << std::endl;
	Edge<montype> e6(c,d);
	std::cout << "e6(c,d): " << e6 << std::endl;
	
	//// Mesh ////
	std::cout << "\n\n/////////\nMesh" << std::endl;
	
	std::list<Edge<montype> > listOfEdges;
	listOfEdges.push_back(e1);
	listOfEdges.push_back(e2);
	listOfEdges.push_back(e3);
	Face<montype> face1(&listOfEdges);
	std::cout << "face1(e1,e2,e3): " << face1 << std::endl;
	
	listOfEdges.clear();
	listOfEdges.push_back(-e1);
	listOfEdges.push_back(e4);
	listOfEdges.push_back(-e5);
	Face<montype> face2(&listOfEdges);
	std::cout << "face2(-e1,e4,-e5): " << face2 << std::endl;
	//~
	listOfEdges.clear();
	listOfEdges.push_back(-e2);
	listOfEdges.push_back(e5);
	listOfEdges.push_back(-e6);
	Face<montype> face3(&listOfEdges);
	std::cout << "face3(-e2,e5,-e6): " << face3 << std::endl;
	//~ 
	listOfEdges.clear();
	listOfEdges.push_back(-e3);
	listOfEdges.push_back(e6);
	listOfEdges.push_back(-e4);
	Face<montype> face4(&listOfEdges);
	std::cout << "face4(-e1,e4,-e5): " << face4 << std::endl;
	//~ 
	Mesh<montype> myMesh;
	myMesh.push(face1);
	myMesh.push(face2);
	myMesh.push(face3);
	myMesh.push(face4);
	std::cout << "myMesh:\n" << myMesh << std::endl;
	myMesh.stat();
	std::cout << "myMesh.stat()" << std::endl;
	std::cout << "myMesh:\n" << myMesh << std::endl;
	
	int whatever = 56;
	myMesh.forEachFace( printFace<montype>, (void *) &whatever );
         
	std::ifstream myOff("cube.off", std::ios::in);
	if(myOff)
    {   
		Mesh<montype> myMeshFromFile;
		myOff >> myMeshFromFile;
        myOff.close();
		std::cout << "myMeshFromFile:\n" << myMeshFromFile << std::endl;
    }
    else
         std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
	
	std::ifstream myOffA("cube.off", std::ios::in);
	//~ std::ifstream myOffB("cube2.off", std::ios::in);
	if(myOffA)//&&myOffB)
    {   
		Mesh<montype> myMeshA;
		//~ Mesh<montype> myMeshB;
		myOffA >> myMeshA;
		//~ myOffB >> myMeshB;
        myOffA.close();
        //~ myOffB.close();
        
        std::cout << "myMeshA:" << myMeshA << std::endl;
        myMeshA.showStat();
		
		//~ typename std::list<Face<montype> >::iterator it;
		//~ for (it=myMeshA.getFaces().begin(); it!=myMeshA.getFaces().end(); ++it){
			//~ std::cout << *it << std::endl;
			//~ HalfEdge<montype> first = it->getHalfEdge();
			//~ HalfEdge<montype> current = first;
			//~ int i = 0;
			//~ do{
				//~ std::cout << current << ", ";
				//~ current = first.getNext();
				//~ i++;
			//~ }while( current != first && i < 50); 
			//~ std::cout <<  std::endl;
		//~ }
		
		//~ std::cout << "myMeshB:" << std::endl;
        //~ myMeshB.showStat();
        //~ 
        //~ Vertex<montype> v(0,0,0);
        //~ HalfEdge<montype> he(v);
        //~ myMeshA.forEachFace(printFaceVsEdge<montype>,(void *) &he);
        //~ myMeshA.forEachHalfEdge(printHalfEdge<montype>, (void *)NULL);
       // myMeshA.forEachHalfEdge(printHalfEdge2<montype>, (void *)NULL);
        
        //~ myMeshA.forEachEdge(printEdge<montype>, (void *)NULL);
    }
    else
         std::cerr << "Impossible d'ouvrir les fichiers !" << std::endl;
         
         
         
	
	
	return 0;
}

