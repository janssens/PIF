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
template<class T> void printHalfEdge(void *halfedge,void *nothing){
		HalfEdge<T> *he = (HalfEdge<T>*) halfedge;
		std::cout << *he << std::endl;
		
}
template<class T> void printVertex(void *vertex,void *nothing){
		Vertex<T> *v = (Vertex<T>*) vertex;
		if (v->isClosestIntersectionInSpaceDefined())
				std::cout << "Closest Intersection of " << *v << " is: " << v->getClosestIntersectionInSpace().getPoint();
		if (v->isInside()) {
			std::cout << ".It is inside" << std::endl;
		}else{
			std::cout << ".It is outside" << std::endl;
		}
}

template<class T> void inter(void *edge,void *mesh){
		Mesh<T> *m = (Mesh<T> *) mesh;
		Edge<T> *e = (Edge<T>*) edge;
		#ifdef DEBUG
			std::cout << "Dealing with edge: " << *e << std::endl;
		#endif
		std::list<Face<T> > faces = m->getFaces(); // list of the faces
		typename std::list<Face<T> >::iterator it;
		for (it=faces.begin(); it!=faces.end(); ++it){
			Intersection<T> i(*e,*it);
			if (i.exist()){
				#ifdef DEBUG
				std::cout << "add " << i.getPoint() << " as an intersection for e =" << *e << std::endl;
				#endif
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

template<class T> void printHalfEdge2(void *halfEdge,void *nothing){
		HalfEdge<T> *he = (HalfEdge<T>*) halfEdge;
		std::cout << *he << std::endl;
		std::cout << "next:" << he->getNext() << std::endl;
		std::cout << "pair:" << he->getPair() << std::endl;   
		Edge<T> e(*he);
		std::cout << e << std::endl;
		std::cout << std::endl;  
}
///////////////////////////////////////////////////////////////////////
//
// reconstruction
//
///////////////////////////////////////////////////////////////////////
//~ 
//~ template<class T> void inside(Mesh<T> * IntersectedMesh,Mesh<T> * Result){
	//~ std::list<Face<T> > faces = IntersectedMesh->getFaces();
	//~ typename std::list<Face<T> >::iterator f;
	//~ for (f = faces.begin(); f != faces.end(); ++f){
		//~ HalfEdge<T> currentHalfEdge = f->getHalfEdge();
		//~ bool skip = false;
		//~ if (!currentHalfEdge.getVertex().isInside()) { //first halfedge of this face is outside!
			//~ do{
				//~ currentHalfEdge = currentHalfEdge.getNext();
			//~ } while(!currentHalfEdge.getVertex().isInside()&&currentHalfEdge!=f->getHalfEdge()); // while we still outside and we have not seen every halfedge yet
			//~ if (currentHalfEdge==f->getHalfEdge()) //this face is completly outside.
				//~ skip = true;
		//~ }
		//~ if (!skip){ //here we have an halfedge who is inside!
			//~ std::cout << *f << std::endl;	
			//~ HalfEdge<T> newCurrentHalfEdge;
			//~ do { // 		
				//~ std::list<Intersection<T> > intersections = currentHalfEdge.getIntersections();
				//~ int tsize = intersections.size();
				//~ std::cout << "intersections.size: " << tsize << std::endl;
				//~ if (tsize=0) { // the edge is completly inside.
					//~ Vertex<T> newVertex = currentHalfEdge.getVertex().duplicate();
					//~ HalfEdge<T> newHalfEdge(newVertex);
					//~ if (!newCurrentHalfEdge.isNull()){
						//~ newCurrentHalfEdge.setNext(newHalfEdge);
					//~ }
					//~ newCurrentHalfEdge = newHalfEdge;
				//~ }else{
					//~ Vertex<T> firstVertex = currentHalfEdge.getFarestIntersection().getVertex().duplicate();
				//~ }
				//~ 
			//~ } while (currentHalfEdge!=f->getHalfEdge());
			//~ Face<T> brandNewFace(newCurrentHalfEdge);
			//~ Result->addFace(brandNewFace);
	//~ }
//~ }


template<class T> void build(Mesh<T> * IntersectedMesh,Mesh<T> * Result){
	std::list<Face<T> > faces = IntersectedMesh->getFaces();
	typename std::list<Face<T> >::iterator f;
	for (f = faces.begin(); f != faces.end(); ++f){ // for each faces
		HalfEdge<T> currentFaceHalfEdge = f->getHalfEdge();
		HalfEdge<T> halfEdge = currentFaceHalfEdge;
		do { // for each halfedge on the face
			std::list<Intersection<T> > intersections = halfEdge.getIntersections();
			typename std::list<Intersection<T> >::iterator it;
			for (it=intersections.begin(); it=!intersections.end(); ++it){ //for each intersection in the halfedge
				std::cout << *it << std::endl;// each intersection
				//face1 is f, the current face
				Face<T> face2 = it->getFace();// the face2
				//for each halfedge of face2
					//for each intersection in halfedge
						//if intersection.face == face2 eureka
				//if not eureka
					//for each halfedge in face1
						//for each intersection in halfedge
							//if intersection.face == face2 eureka
					//if not eureka
						//FAIL
			}
			halfEdge = halfEdge.getNext();
		} while (halfEdge != currentFaceHalfEdge);
	}
}
////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
	
	typedef double montype;
	
	//~ //// Vertex ////
	//~ Vertex<montype>  a((montype)1,(montype)0,(montype)0);
	//~ std::cout << "a: " << a << std::endl;
	//~ Vertex<montype>  b((montype)0,(montype)1,(montype)0);
	//~ std::cout << "b: " << b << std::endl;
	//~ Vertex<montype>  c((montype)0,(montype)0,(montype)1);
	//~ std::cout << "c: " << c << std::endl;
	//~ Vertex<montype>  d((montype)0,(montype)0,(montype)0);
	//~ std::cout << "d: " << d << std::endl;
	//~ 
	//~ //// HalfEdge ////
	//~ std::cout << "/////////\nHalfEdge" << std::endl;
	//~ HalfEdge<montype> he11(a);
	//~ std::cout << "he11(a): " << he11 << std::endl;
	//~ HalfEdge<montype> he12(b);
	//~ std::cout << "he12(b): " << he12 << std::endl;
	//~ HalfEdge<montype> he13(d);
	//~ std::cout << "he12(d): " << he13 << std::endl;
	//~ he11.setNext(he12);
	//~ he12.setNext(he13);
	//~ he13.setNext(he11);
	//~ HalfEdge<montype> he21(a);
	//~ std::cout << "he21(a): " << he21 << std::endl;
	//~ HalfEdge<montype> he22(c);
	//~ std::cout << "he22(c): " << he22 << std::endl;
	//~ HalfEdge<montype> he23(b);
	//~ std::cout << "he22(b): " << he23 << std::endl;
	//~ he21.setNext(he22);
	//~ he22.setNext(he23);
	//~ he23.setNext(he21);
	//~ he21.setPair(he12);
	//~ HalfEdge<montype> he31(b);
	//~ std::cout << "he31(b): " << he31 << std::endl;
	//~ HalfEdge<montype> he32(c);
	//~ std::cout << "he32(c): " << he32 << std::endl;
	//~ HalfEdge<montype> he33(d);
	//~ std::cout << "he33(d): " << he33 << std::endl;
	//~ he31.setNext(he32);
	//~ he32.setNext(he33);
	//~ he33.setNext(he31);
	//~ he31.setPair(he13);
	//~ he32.setPair(he23);
	//~ HalfEdge<montype> he41(a);
	//~ std::cout << "he41(a): " << he41 << std::endl;
	//~ HalfEdge<montype> he42(d);
	//~ std::cout << "he42(d): " << he42 << std::endl;
	//~ HalfEdge<montype> he43(c);
	//~ std::cout << "he43(c): " << he43 << std::endl;
	//~ he41.setNext(he42);
	//~ he42.setNext(he43);
	//~ he43.setNext(he41);
	//~ he41.setPair(he22);
	//~ he42.setPair(he11);
	//~ he43.setPair(he33);
	//~ 
	//~ //// Mesh ////
	//~ std::cout << "\n\n/////////\nMesh" << std::endl;
	//~ 
	//~ Face<montype> face1(he11);
	//~ std::cout << "face1: " << face1 << std::endl;
	//~ Face<montype> face2(he21);
	//~ std::cout << "face2: " << face2 << std::endl;
	//~ Face<montype> face3(he31);
	//~ std::cout << "face3: " << face3 << std::endl;
	//~ Face<montype> face4(he41);
	//~ std::cout << "face4: " << face4 << std::endl;
	
	//~ Mesh<montype> myMesh;
	//~ myMesh.push(face1);
	//~ myMesh.push(face2);
	//~ myMesh.push(face3);
	//~ myMesh.push(face4);
	//~ std::cout << "myMesh:\n" << myMesh << std::endl;
	//~ myMesh.stat();
	//~ std::cout << "myMesh.stat()" << std::endl;
	//~ std::cout << "myMesh:\n" << myMesh << std::endl;
	//~ myMesh.forEachEdge(printEdge<montype>, (void *)NULL);
    //~ 

    char mesh1[] = "meshA.off";
    char mesh2[] = "meshB.off";
    
    //~ char mesh1[] = "tt.off";
    //~ char mesh2[] = "tt2.off";
    
	std::ifstream myOff1(mesh1, std::ios::in);
	std::ifstream myOff2(mesh2, std::ios::in);
	if(myOff1&&myOff2)
    {
		
		//~ Vertex<montype>  a1((montype)0,(montype)0,(montype)0);
		//~ Vertex<montype>  a2((montype)1,(montype)1,(montype)1);
		//~ Vertex<montype>  b1((montype)2,(montype)0,(montype)0);
		//~ Vertex<montype>  b2((montype)3,(montype)1,(montype)1);
		//~ Vertex<montype>  c1((montype)2,(montype)2,(montype)0);
		//~ Vertex<montype>  c2((montype)3,(montype)3,(montype)1);
		//~ Vertex<montype>  d1((montype)0,(montype)2,(montype)0);
		//~ Vertex<montype>  d2((montype)1,(montype)3,(montype)1);
		//~ Vertex<montype>  e1((montype)0,(montype)0,(montype)2);
		//~ Vertex<montype>  e2((montype)1,(montype)1,(montype)3);
		//~ Vertex<montype>  f1((montype)2,(montype)0,(montype)2);
		//~ Vertex<montype>  f2((montype)3,(montype)1,(montype)3);
		//~ Vertex<montype>  g1((montype)2,(montype)2,(montype)2);
		//~ Vertex<montype>  g2((montype)3,(montype)3,(montype)3);
		//~ Vertex<montype>  h1((montype)0,(montype)2,(montype)2);
		//~ Vertex<montype>  h2((montype)1,(montype)3,(montype)3);
		//~ 
		//~ HalfEdge<montype> he_ab1(b1);
		//~ HalfEdge<montype> he_ab2(b2);
		//~ HalfEdge<montype> he_bc1(c1);
		//~ HalfEdge<montype> he_bc2(c2);
		//~ HalfEdge<montype> he_cd1(d1);
		//~ HalfEdge<montype> he_cd2(d2);
		//~ HalfEdge<montype> he_da1(a1);
		//~ HalfEdge<montype> he_da2(a2);
		//~ he_ab1.setNext(he_bc1);
		//~ he_ab2.setNext(he_bc2);
		//~ he_bc1.setNext(he_cd1);
		//~ he_bc2.setNext(he_cd2);
		//~ he_cd1.setNext(he_da1);
		//~ he_cd2.setNext(he_da2);
		//~ he_da1.setNext(he_ab1);
		//~ he_da2.setNext(he_ab2);
		//~ Face<montype> f_abcd1(he_ab1);
		//~ Face<montype> f_abcd2(he_ab2);
		//~ 
		//~ HalfEdge<montype> he_cb1(b1);
		//~ HalfEdge<montype> he_cb2(b2);
		//~ HalfEdge<montype> he_bf1(f1);
		//~ HalfEdge<montype> he_bf2(f2);
		//~ HalfEdge<montype> he_fg1(g1);
		//~ HalfEdge<montype> he_fg2(g2);
		//~ HalfEdge<montype> he_gc1(c1);
		//~ HalfEdge<montype> he_gc2(c2);
		//~ he_cb1.setNext(he_bf1);
		//~ he_cb2.setNext(he_bf2);
		//~ he_bf1.setNext(he_fg1);
		//~ he_bf2.setNext(he_fg2);
		//~ he_fg1.setNext(he_gc1);
		//~ he_fg2.setNext(he_gc2);
		//~ he_gc1.setNext(he_cb1);
		//~ he_gc2.setNext(he_cb2);
		//~ Face<montype> f_cbfg1(he_cb1);
		//~ Face<montype> f_cbfg2(he_cb2);		
		//~ 
		//~ HalfEdge<montype> he_fe1(e1);
		//~ HalfEdge<montype> he_fe2(e2);
		//~ HalfEdge<montype> he_eh1(h1);
		//~ HalfEdge<montype> he_eh2(h2);
		//~ HalfEdge<montype> he_hg1(g1);
		//~ HalfEdge<montype> he_hg2(g2);
		//~ HalfEdge<montype> he_gf1(f1);
		//~ HalfEdge<montype> he_gf2(f2);
		//~ he_fe1.setNext(he_eh1);
		//~ he_fe2.setNext(he_eh2);
		//~ he_eh1.setNext(he_hg1);
		//~ he_eh2.setNext(he_hg2);
		//~ he_hg1.setNext(he_gf1);
		//~ he_hg2.setNext(he_gf2);
		//~ he_gf1.setNext(he_fe1);
		//~ he_gf2.setNext(he_fe2);
		//~ Face<montype> f_fehg1(he_fe1);
		//~ Face<montype> f_fehg2(he_fe2);	
		//~ 
		//~ HalfEdge<montype> he_ea1(a1);
		//~ HalfEdge<montype> he_ea2(a2);
		//~ HalfEdge<montype> he_ad1(d1);
		//~ HalfEdge<montype> he_ad2(d2);
		//~ HalfEdge<montype> he_dh1(h1);
		//~ HalfEdge<montype> he_dh2(h2);
		//~ HalfEdge<montype> he_he1(e1);
		//~ HalfEdge<montype> he_he2(e2);
		//~ he_ea1.setNext(he_ad1);
		//~ he_ea2.setNext(he_ad2);
		//~ he_ad1.setNext(he_dh1);
		//~ he_ad2.setNext(he_dh2);
		//~ he_dh1.setNext(he_he1);
		//~ he_dh2.setNext(he_he2);
		//~ he_he1.setNext(he_ea1);
		//~ he_he2.setNext(he_ea2);
		//~ Face<montype> f_eadh1(he_ea1);
		//~ Face<montype> f_eadh2(he_ea2);	
		//~ 
		//~ HalfEdge<montype> he_ba1(a1);
		//~ HalfEdge<montype> he_ba2(a2);
		//~ HalfEdge<montype> he_ae1(e1);
		//~ HalfEdge<montype> he_ae2(e2);
		//~ HalfEdge<montype> he_ef1(f1);
		//~ HalfEdge<montype> he_ef2(f2);
		//~ HalfEdge<montype> he_fb1(b1);
		//~ HalfEdge<montype> he_fb2(b2);
		//~ he_ba1.setNext(he_ae1);
		//~ he_ba2.setNext(he_ae2);
		//~ he_ae1.setNext(he_ef1);
		//~ he_ae2.setNext(he_ef2);
		//~ he_ef1.setNext(he_fb1);
		//~ he_ef2.setNext(he_fb2);
		//~ he_fb1.setNext(he_ba1);
		//~ he_fb2.setNext(he_ba2);
		//~ Face<montype> f_baef1(he_ba1);
		//~ Face<montype> f_baef2(he_ba2);	
		//~ 
		//~ HalfEdge<montype> he_dc1(c1);
		//~ HalfEdge<montype> he_dc2(c2);
		//~ HalfEdge<montype> he_cg1(g1);
		//~ HalfEdge<montype> he_cg2(g2);
		//~ HalfEdge<montype> he_gh1(h1);
		//~ HalfEdge<montype> he_gh2(h2);
		//~ HalfEdge<montype> he_hd1(d1);
		//~ HalfEdge<montype> he_hd2(d2);
		//~ he_dc1.setNext(he_cg1);
		//~ he_dc2.setNext(he_cg2);
		//~ he_cg1.setNext(he_gh1);
		//~ he_cg2.setNext(he_gh2);
		//~ he_gh1.setNext(he_hd1);
		//~ he_gh2.setNext(he_hd2);
		//~ he_hd1.setNext(he_dc1);
		//~ he_hd2.setNext(he_dc2);
		//~ Face<montype> f_dcgh1(he_dc1);
		//~ Face<montype> f_dcgh2(he_dc2);
		//~ 
		//~ he_ab1.setPair(he_ba1);
		//~ he_ab2.setPair(he_ba2);
		//~ he_ad1.setPair(he_da1);
		//~ he_ad2.setPair(he_da2);
		//~ he_dh1.setPair(he_hd1);
		//~ he_dh2.setPair(he_hd2);
		//~ he_dc1.setPair(he_cd1);
		//~ he_dc2.setPair(he_cd2);
		//~ he_hg1.setPair(he_gh1);
		//~ he_hg2.setPair(he_gh2);
		//~ he_cg1.setPair(he_gc1);
		//~ he_cg2.setPair(he_gc2);
		//~ he_gf1.setPair(he_fg1);
		//~ he_gf2.setPair(he_fg2);
		//~ he_bf1.setPair(he_fb1);
		//~ he_bf2.setPair(he_fb2);
		//~ he_cb1.setPair(he_bc1);
		//~ he_cb2.setPair(he_bc2);
		//~ he_ae1.setPair(he_ea1);
		//~ he_ae2.setPair(he_ea2);
		//~ he_eh1.setPair(he_he1);
		//~ he_eh2.setPair(he_he2);
		//~ he_ef1.setPair(he_fe1);
		//~ he_ef2.setPair(he_fe2);
		//~ 
		Mesh<montype> myMeshFromFileA;
		Mesh<montype> myMeshFromFileB;
		//~ 
		//~ myMeshFromFileA.push(f_abcd1);
		//~ myMeshFromFileA.push(f_cbfg1);
		//~ myMeshFromFileA.push(f_fehg1);
		//~ myMeshFromFileA.push(f_baef1);
		//~ myMeshFromFileA.push(f_dcgh1);
		//~ 
		//~ myMeshFromFileB.push(f_abcd2);
		//~ myMeshFromFileB.push(f_cbfg2);
		//~ myMeshFromFileB.push(f_fehg2);
		//~ myMeshFromFileB.push(f_baef2);
		//~ myMeshFromFileB.push(f_dcgh2);
		
		
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
		//~ 
		//~ std::cout << "==== forEachHalfEdge ====" << std::endl;
		//~ myMeshFromFileA.forEachHalfEdge(printHalfEdge<montype>);
		std::cout << "==== forEachVertex ====" << std::endl;
		myMeshFromFileA.forEachVertex(printVertex<montype>);
		myMeshFromFileB.forEachVertex(printVertex<montype>);
		//~ Mesh<montype> myMeshFromInter;
		//~ std::cout << "==== A inside B ====" << std::endl;
		//~ Mesh<montype> result;
		//inside(&myMeshFromFileA,&result);
		//build(&myMeshFromFileA,&result);
		//std::cout <<  result << std::endl;
    }
    else
         std::cerr << "Impossible d'ouvrir les fichiers !" << std::endl;
	
	return 0;
}


