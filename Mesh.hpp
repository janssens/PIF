/*
 * Polyhedron Intersection Framework
 * 
 * FileName: Mesh.hpp
 * Creation: 29.06.2011
 * Author: Gaëtan Janssens
 * Last Edit: 29.06.2011
 * 
 */
#ifndef MESH_H
#define MESH_H

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
	template <class T> class Mesh {
		public:
			Mesh(): _vertex_count(0),_face_count(0),_edge_count(0) {};
			////
			std::list<Face<T> > getFaces(void) const {
				return _faces;
			}
			void setVertexCount(int nb){
				_vertex_count = nb;
			}
			void setFaceCount(int nb){
				_face_count = nb;
			}
			void setEdgeCount(int nb){
				_edge_count = nb;
			}		
			int getVertexCount(void) const{
				return _vertex_count;
			}
			int getFaceCount(void) const{
				return _face_count;
			}
			int getEdgeCount(void) const{
				return _edge_count;
			}
			void showStat(void){
				std::cout << "_vertex_count:" << _vertex_count << std::endl;
				std::cout << "_face_count:" << _face_count << std::endl;
				std::cout << "_edge_count:" << _edge_count << std::endl;
			}			
			void stat(void){
				typename std::list<Face<T> >::iterator it;
				_face_count = 0;
				int halfedge_count = 0;
				std::vector<Vertex<T> > vertex_array;
				for (it=_faces.begin(); it!=_faces.end(); ++it){
					//~ std::cout << "face:" << *it << std::endl << std::endl;
					HalfEdge<T> firstHalfEdge = it->getHalfEdge();
					HalfEdge<T> halfEdge = firstHalfEdge;
					do {
						Vertex<T> v = halfEdge.getVertex();
						typename std::vector<Vertex<T> >::iterator itv;
						if (!vertex_array.empty()){
							for ( itv=vertex_array.begin() ; itv != vertex_array.end()  && v < *itv;)
								itv++;
							if (*itv!=v){ // v > *itv
								vertex_array.insert ( itv , v );
							}
						}else{
							vertex_array.push_back(v);
						}
						//~ std::cout << std::endl;
						//~ for ( itv=vertex_array.begin() ; itv != vertex_array.end();itv++)
							//~ std::cout << *itv << ",";
						halfEdge = halfEdge.getNext();
						halfedge_count++;
					} while (halfEdge != firstHalfEdge);
					//~ _face_count++;
					//~ std::cout << _face_count;
				}
				_vertex_count = vertex_array.size();
				_edge_count = halfedge_count/2;
				//~ std::cout << "_vertex_count:" << _vertex_count << std::endl;
				//~ std::cout << "_face_count:" << _face_count << std::endl;
				//~ std::cout << "_edge_count:" << _edge_count << std::endl;
			}
			////
			
			void forEachFace( void (*fct) (void *,void *), void * data = NULL){
				typename std::list<Face<T> >::iterator it;
				for (it=_faces.begin(); it!=_faces.end(); ++it){
					fct((void *) &(*it), data);
				}
			}
			
			void forEachEdge( void (*fct) (void *,void *), void * data = NULL){
				typename std::list<Face<T> >::iterator itFace;
				std::vector<Edge<T> > alreadySeen;
				for (itFace=_faces.begin(); itFace!=_faces.end(); ++itFace){ // for all face
					//~ std::cout << "dealing with face:" << *itFace << std::endl;
					HalfEdge<T> firstHalfEdge = itFace->getHalfEdge();
					HalfEdge<T> currentHalfEdge = firstHalfEdge;
					do { // for all halfedges on the face
						Edge<T> e(currentHalfEdge);
						int max = alreadySeen.size();
						int tmp = 0;
						for (; (tmp<max) && (alreadySeen.at(tmp)<e); tmp ++){ } //check if the Edge is already seen
						if (tmp==max||alreadySeen.at(tmp)!=e) //Edge is not already seen
						{
							//~ std::cout << "just seen:" << e << std::endl;
							fct((void *) &e, data);
							alreadySeen.insert(alreadySeen.begin()+tmp,e); //this Edge is now seen
						}
						currentHalfEdge = currentHalfEdge.getNext();
					} while (currentHalfEdge != firstHalfEdge);
				}
			}
			
			
			void forEachHalfEdge( void (*fct) (void *,void *), void * data = NULL){
				typename std::list<Face<T> >::iterator it;
				for (it=_faces.begin(); it!=_faces.end(); ++it){
					//~ std::cout << *it << std::endl;
					it->forEachHalfEdge(fct,data);
				}
			}
			
			void forEachVertex( void (*fct) (void *,void *), void * data = NULL){
				typename std::list<Face<T> >::iterator itFace;
				std::vector<Vertex<T> > alreadySeen;
				for (itFace=_faces.begin(); itFace!=_faces.end(); ++itFace){ // for all face
					//~ std::cout << "dealing with face:" << *itFace << std::endl;
					HalfEdge<T> firstHalfEdge = itFace->getHalfEdge();
					HalfEdge<T> currentHalfEdge = firstHalfEdge;
					do { // for all halfedges on the face
						Vertex<T> v = currentHalfEdge.getVertex();
						int max = alreadySeen.size();
						int tmp = 0;
						for (; (tmp<max) && (alreadySeen.at(tmp)<v); tmp ++){ } //check if the Edge is already seen
						if (tmp==max||alreadySeen.at(tmp)!=v) //Edge is not already seen
						{
							//~ std::cout << "just seen:" << e << std::endl;
							fct((void *) &v, data);
							alreadySeen.insert(alreadySeen.begin()+tmp,v); //this Edge is now seen
						}
						currentHalfEdge = currentHalfEdge.getNext();
					} while (currentHalfEdge != firstHalfEdge);
				}
			}
			
			void push(Face<T> f) {
				_faces.push_back(f);
			}
			void addFace(Face<T> f) { // same as push
				_faces.push_back(f);
			}
		private:
			std::list<Face<T> > _faces;
			int _vertex_count;
			int _face_count;
			int _edge_count;
	};
	
	template<class T> std::ostream& operator<< (std::ostream& o,const Mesh<T> mesh){
		o << "OFF" << std::endl;
		o << mesh.getVertexCount() << " " <<  mesh.getFaceCount() << " " << mesh.getEdgeCount() << std::endl;
		if (mesh.getVertexCount()>0) {
			typename std::list<Face<T> >::iterator it;
			std::vector<Vertex<T> > vertex_array;
			std::list<Face<T> > faces = mesh.getFaces();
			for (it=faces.begin(); it!=faces.end(); it++){ // for each face
				HalfEdge<T> firstHalfEdge = it->getHalfEdge();
				HalfEdge<T> halfEdge = firstHalfEdge;
				do { // for each halfedge in the face
				
					Vertex<T> v = halfEdge.getVertex();
					//~ std::cout << "reading: " << v << std::endl;
					typename std::vector<Vertex<T> >::iterator itv;
					if (!vertex_array.empty()){
						for ( itv=vertex_array.begin() ; itv != vertex_array.end()  &&  v < *itv;)
							itv++;
						if(itv == vertex_array.end()){
							vertex_array.push_back(v);
						}else if (v > *itv){
							vertex_array.insert ( itv , v );
						}
					}else{
						vertex_array.push_back(v);
					}
					halfEdge = halfEdge.getNext();
				} while (halfEdge != firstHalfEdge);
			}
			
			int tmpint=0;
			int max = vertex_array.size();
			for ( int i=0; i < max; i++)
				o << vertex_array[i] << std::endl;
			for (it=faces.begin(); it!=faces.end(); ++it){
				int nbOfVertex = 0;
				HalfEdge<T> firstHalfEdge = it->getHalfEdge();
				HalfEdge<T> halfEdge = firstHalfEdge;
				std::stringstream ss (std::stringstream::in | std::stringstream::out);
				int indextmp ;
				do {
					indextmp = 0;
					Vertex<T> v = halfEdge.getVertex();
					typename std::vector<Vertex<T> >::iterator itv;
					for ( itv=vertex_array.begin() ; itv != vertex_array.end()  && v < *itv;itv++)
						indextmp++;
					if (*itv!=v){ // v > *itv
						std::cout << "what the hell!" << std::endl; //vertex not found, but should be!
					}else{
						ss << indextmp << " ";
					}
					halfEdge = halfEdge.getNext();
					nbOfVertex++;
				} while (halfEdge != firstHalfEdge);
				o << nbOfVertex << " " << ss.str() << std::endl;
			}
		}
		return o;
	};
	
	
	template<class T> void operator>> (std::ifstream& fichier,Mesh<T> &myMesh){
		std::string contenu;  // to contain the read line
        std::getline(fichier, contenu);  // read the line
        if (contenu.compare(0,3,"OFF") != 0){
			std::cerr << "/!\\ PIF Error: The file you are trying to read is not an regular OFF file." << std::endl;
			exit(1);
		}
       
        int VertexCount;
        int FaceCount;
        int EdgeCount;
        fichier >> VertexCount;
        fichier >> FaceCount;
        fichier >> EdgeCount;
        #ifdef DEBUG
        std::cout << "VertexCount:" << VertexCount << std::endl;
        std::cout << "FaceCount:" << FaceCount << std::endl;
        std::cout << "EdgeCount:" << EdgeCount << std::endl;
        #endif

        std::getline(fichier, contenu);  //get the end of the line
		
		typename std::vector<Vertex<T> > vertex;
		for(int i = 0; i < VertexCount; i++){ // for all vertex
			T x,y,z;
			fichier >> x;
			fichier >> y;
			fichier >> z;
			std::getline(fichier, contenu); //get the end of the line
			Vertex<T> v(x,y,z);
			vertex.push_back(v);
			#ifdef DEBUG
			std::cout << "#" << i << ":" << v << std::endl;
			#endif
		}
		
		
		typename std::vector<Face<T> > faces;
		
		typename std::vector<std::vector<HalfEdge<T> > > link;
		for(int i = 0; i < VertexCount; i++){
			std::vector<HalfEdge<T> > vect;
			link.push_back(vect);
		}
		for(int i = 0; i < FaceCount; i++){ // for all Face
			int nbOfVertexInThisFace = 0;
			fichier >> nbOfVertexInThisFace;
			int VertexIndex = 0;
			fichier >> VertexIndex;
			int firstVertexIndex=VertexIndex;
			int previousVertexIndex = 0;
			int nbOfHalfEdges = 0;;
			int indexOfFirstVertex = VertexIndex;
			Vertex<T> firstVertex = vertex.at(indexOfFirstVertex);
			HalfEdge<T> firstsHalfEdge(firstVertex);
			HalfEdge<T> previousHalfEdge = firstsHalfEdge;
			HalfEdge<T> tmp_he;
			bool pairFound;
			int j = 1; //index of read Vertex
			do{ //for all Vertex in the face
				previousVertexIndex = VertexIndex;
				fichier >> VertexIndex;
				#ifdef DEBUG
				std::cout << previousVertexIndex << "->" << VertexIndex << " (boucle)" << std::endl;
				#endif
				HalfEdge<T> currentHalfEdge(vertex.at(VertexIndex));
				nbOfHalfEdges = link[VertexIndex].size();
				pairFound = false;
				if (nbOfHalfEdges){ // there is at least one halfedge going somewhere from here
					#ifdef DEBUG
					std::cout << nbOfHalfEdges << " halfedge starting from " << VertexIndex << std::endl;
					#endif
					for (int k=0; (k < nbOfHalfEdges)&&(!pairFound); k++){ //lets find the pair
						tmp_he = link[VertexIndex][k];
						if (tmp_he.getVertex()==vertex.at(previousVertexIndex)) { // the pair exist!
							currentHalfEdge.setPair(tmp_he);
							#ifdef DEBUG
							std::cout << "->" << VertexIndex << "(" << currentHalfEdge << ") paired with " << "->" << previousVertexIndex << "(" << tmp_he << ")" << std::endl;
							#endif
							link[VertexIndex].erase(link[VertexIndex].begin()+k);//the two vertex are paired, we dont need to keep trace of them anymore.
							pairFound = true; //leave the for loop with result found
						}
					}
				}
				if (!pairFound) { // the pair do not exist yet!
					link[previousVertexIndex].push_back(currentHalfEdge); // this new halfedge is going from previousVertex to Vertex, we keep track of that
					#ifdef DEBUG
					std::cout << "we keep track of " << previousVertexIndex << "->" << VertexIndex << std::endl;
					#endif
				}
				previousHalfEdge.setNext(currentHalfEdge);
				previousHalfEdge = currentHalfEdge;
				j++;//we just read one more Vertex
			} while (j < nbOfVertexInThisFace);
			#ifdef DEBUG
			std::cout << "->" << VertexIndex << "->" << indexOfFirstVertex << " (hors boucle)" << std::endl;
			#endif
			previousHalfEdge.setNext(firstsHalfEdge);// and the cycle is complete
			nbOfHalfEdges = link[indexOfFirstVertex].size();// all the half edge who start here
			pairFound = false;
			if (nbOfHalfEdges){ // there is at least one halfedge who start here
				#ifdef DEBUG
				std::cout << nbOfHalfEdges << " halfedge starting from " << indexOfFirstVertex << std::endl;
				#endif
				for (int k=0; (k < nbOfHalfEdges)&&(!pairFound); k++){ //lets find the pair
					tmp_he = link[indexOfFirstVertex][k];
					if (tmp_he.getVertex()==vertex.at(VertexIndex)) { // the pair exist!
							#ifdef DEBUG
							std::cout << indexOfFirstVertex << "(" << firstsHalfEdge << ") paired with " << "->" << VertexIndex << "(" << tmp_he << ")" << std::endl;
							#endif
							firstsHalfEdge.setPair(tmp_he);
							#ifdef DEBUG
							tmp_he.setPair(firstsHalfEdge);
							#endif
							link[indexOfFirstVertex].erase(link[indexOfFirstVertex].begin()+k);//the two vertex are paired, we dont need to keep trace of them anymore.
							pairFound = true; //leave the for loop with result found
					}
				}
			}
			if (!pairFound) { // the pair do not exist yet!
				link[VertexIndex].push_back(firstsHalfEdge);// we know from were the first half edge was going, and we keep track of that
				#ifdef DEBUG
				std::cout << "we keep track of " << VertexIndex << "->" << indexOfFirstVertex << std::endl;
				#endif
			}
			Face<T> face(firstsHalfEdge);
			
			HalfEdge<T> tmpHalfEdge = firstsHalfEdge;
			do {
				tmpHalfEdge.setFace(face); //associer 
				tmpHalfEdge = tmpHalfEdge.getNext();
			} while (tmpHalfEdge != firstsHalfEdge); // pour chaque halfhedge de la face
			
			myMesh.push(face);
			#ifdef DEBUG
			std::cout << "face:" << face << std::endl;
			#endif
			std::getline(fichier, contenu); //get the end of the line
		}
		int leftOver=0;
		for(int i = 0; i < VertexCount; i++){
			leftOver += link[i].size(); 
			link[i].clear();
		}
		link.clear();
		if (leftOver>0)
			std::cout << "/!\\" << leftOver << " HalfEdge where not paired!"  << std::endl;
		
		myMesh.setVertexCount(VertexCount);
		myMesh.setEdgeCount(EdgeCount);
		myMesh.setFaceCount(FaceCount);
		//~ std::cout << myMesh << std::endl;
		//~ return myMesh; 
	};
}
#endif
