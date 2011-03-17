/*
 * Polyhedron Intersection Framework
 * 
 * FileName: simpleMeshLoader.cpp
 * Creation: 11.03.2011
 * Author: Gaëtan Janssens
 * Last Edit: 11.03.2011
 * 
 */

#include "Type.hpp"

using namespace pif;

int main(int argc, char **argv) {
	assert(argc>1);
	
	typedef double montype;
	
	std::ifstream myOff(argv[1], std::ios::in);
	if(myOff)
    {   
		Mesh<montype> myMeshFromFile;
		myOff >> myMeshFromFile;
        myOff.close();
		std::cout << "myMeshFromFile:\n" << myMeshFromFile << std::endl;
    }
    else
         std::cerr << "Impossible d'ouvrir le fichier " << argv[1] << "!" << std::endl;
		
	return 0;
}

