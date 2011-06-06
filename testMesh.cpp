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

template<class T> void inter(void *edge,void *mesh){
		Mesh<T> *m = (Mesh<T> *) mesh;
		Edge<T> *e = (Edge<T>*) edge;
		std::list<Face<T> > faces = m->getFaces(); // list of the faces
		typename std::list<Face<T> >::iterator it;
		for (it=faces.begin(); it!=faces.end(); ++it){
			Intersection<T> i(*e,*it);
			if (i.exist()){
				std::cout << "add " << i.getPoint() << " as an intersection for e =" << *e << std::endl;
				e->addIntersection(i);
			}
		}
}

template<class T> void printInter(void *edge, void *d = NULL){
		Edge<T> *e = (Edge<T>*) edge;
		std::cout << *e << std::endl;
		std::list<Intersection<T> > intersections = e->getHalfEdge().getIntersections();
		int tsize = intersections.size();
		std::cout << "intersections.size: " << tsize << std::endl;
		typename std::list<Intersection<T> >::iterator it;
		int tt = 0;
		for (it=intersections.begin(); tt<tsize; ++it, tt++){
			std::cout << *it << std::endl;
		}
		if (tsize>1)
			std::cout << " Closest Intersection: " << e->getHalfEdge().getClosestIntersection() << std::endl;
		if (tsize>1)
			std::cout << " Farest Intersection: " << e->getHalfEdge().getFarestIntersection() << std::endl;
}

// find by edge
// find by face

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
	
	//// HalfEdge ////
	std::cout << "/////////\nHalfEdge" << std::endl;
	HalfEdge<montype> he11(a);
	std::cout << "he11(a): " << he11 << std::endl;
	HalfEdge<montype> he12(b);
	std::cout << "he12(b): " << he12 << std::endl;
	HalfEdge<montype> he13(d);
	std::cout << "he12(d): " << he13 << std::endl;
	he11.setNext(he12);
	he12.setNext(he13);
	he13.setNext(he11);
	HalfEdge<montype> he21(a);
	std::cout << "he21(a): " << he21 << std::endl;
	HalfEdge<montype> he22(c);
	std::cout << "he22(c): " << he22 << std::endl;
	HalfEdge<montype> he23(b);
	std::cout << "he22(b): " << he23 << std::endl;
	he21.setNext(he22);
	he22.setNext(he23);
	he23.setNext(he21);
	he21.setPair(he12);
	HalfEdge<montype> he31(b);
	std::cout << "he31(b): " << he31 << std::endl;
	HalfEdge<montype> he32(c);
	std::cout << "he32(c): " << he32 << std::endl;
	HalfEdge<montype> he33(d);
	std::cout << "he33(d): " << he33 << std::endl;
	he31.setNext(he32);
	he32.setNext(he33);
	he33.setNext(he31);
	he31.setPair(he13);
	he32.setPair(he23);
	HalfEdge<montype> he41(a);
	std::cout << "he41(a): " << he41 << std::endl;
	HalfEdge<montype> he42(d);
	std::cout << "he42(d): " << he42 << std::endl;
	HalfEdge<montype> he43(c);
	std::cout << "he43(c): " << he43 << std::endl;
	he41.setNext(he42);
	he42.setNext(he43);
	he43.setNext(he41);
	he41.setPair(he22);
	he42.setPair(he11);
	he43.setPair(he33);
	
	//// Mesh ////
	std::cout << "\n\n/////////\nMesh" << std::endl;
	
	Face<montype> face1(he11);
	std::cout << "face1: " << face1 << std::endl;
	Face<montype> face2(he21);
	std::cout << "face2: " << face2 << std::endl;
	Face<montype> face3(he31);
	std::cout << "face3: " << face3 << std::endl;
	Face<montype> face4(he41);
	std::cout << "face4: " << face4 << std::endl;
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
	myMesh.forEachEdge(printEdge<montype>, (void *)NULL);
    //~ 
    //~ char mesh1[] = "cube.off";
    //~ char mesh2[] = "cube2.off";
    
    char mesh1[] = "tt.off";
    char mesh2[] = "tt2.off";
    
	std::ifstream myOff1(mesh1, std::ios::in);
	std::ifstream myOff2(mesh2, std::ios::in);
	if(myOff1&&myOff2)
    {   
		Mesh<montype> myMeshFromFileA;
		Mesh<montype> myMeshFromFileB;
		myOff1 >> myMeshFromFileA;
		myOff2 >> myMeshFromFileB;
        myOff1.close();
        myOff2.close();
		std::cout << "myMeshFromFileA (" << mesh1 << "):\n" << myMeshFromFileA << std::endl;
		std::cout << "myMeshFromFileB (" << mesh2 << "):\n" << myMeshFromFileB << std::endl;
		
		myMeshFromFileA.forEachEdge(inter<montype>, (void *)&myMeshFromFileB);
		std::cout << "==== done A inter B ====" << std::endl;
		myMeshFromFileB.forEachEdge(inter<montype>, (void *)&myMeshFromFileA);
		std::cout << "==== done B inter A ====" << std::endl;
		
		//myMeshFromFileA.getFaces.front().getHalfEdge().
		
		myMeshFromFileA.forEachEdge(printInter<montype>);
		myMeshFromFileB.forEachEdge(printInter<montype>);
    }
    else
         std::cerr << "Impossible d'ouvrir les fichiers !" << std::endl;
	
	return 0;
}

