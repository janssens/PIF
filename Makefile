CPP=g++
#CCFLAGS=-c -Wall
CCFLAGS = -g -O2
LIBS=
LIBSDIR = -L./
INCLDIR = -I./
SOURCES=Type.cpp Vertex.cpp Vect.cpp Edge.cpp main.cpp testVertex.cpp testEdge.cpp testVect.cpp testMesh.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= testVertex testEdge testVect testFace testMesh

all: $(EXECUTABLE)

############################################
# just a testing file for Vertex
############################################	
testVertex: testVertex.o Type.o Vertex.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
Vertex.o: Vertex.hpp Vertex.cpp Type.hpp 
	$(CPP) $(CFLAGS)  $(INCLDIR) -c  Vertex.cpp	
testVertex.o: testVertex.cpp Type.hpp Vertex.hpp
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  testVertex.cpp
	
############################################
# just a testing file for Edges
############################################	
testEdge: testEdge.o Edge.o Type.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
Edge.o: Edge.hpp Edge.cpp Type.hpp 
	$(CPP) $(CFLAGS)  $(INCLDIR) -c  Edge.cpp	
testEdge.o: testEdge.cpp Type.hpp 
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  testEdge.cpp
	
############################################
# just a testing file for Vect
############################################	
testVect: testVect.o Type.o Vect.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
Vect.o: Vect.hpp Type.hpp 
	$(CPP) $(CFLAGS)  $(INCLDIR) -c  Vect.cpp	
testVect.o: testVect.cpp Type.hpp Vect.hpp
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  testVect.cpp
	
############################################
# just a testing file for Faces
############################################	
testFace: testFace.o Face.o Type.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
Face.o: Face.hpp Type.hpp 
	$(CPP) $(CFLAGS)  $(INCLDIR) -c  Face.cpp	
testFace.o: testFace.cpp Type.hpp 
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  testFace.cpp
	
############################################
# just a testing file for Mesh
############################################	
testMesh: testMesh.o Type.o Mesh.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
Mesh.o: Mesh.hpp Type.hpp 
	$(CPP) $(CFLAGS)  $(INCLDIR) -c  Mesh.cpp	
testMesh.o: testMesh.cpp Type.hpp 
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  testMesh.cpp

############################################
# just a simple Mesh Loader
############################################	
simpleMeshLoader: simpleMeshLoader.o Type.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
simpleMeshLoader.o: simpleMeshLoader.cpp Type.hpp 
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  simpleMeshLoader.cpp


############################################
	
############################################
Type.o: Type.hpp Type.cpp
	$(CPP) $(CFLAGS)  $(INCLDIR) -c  Type.cpp
	
clean:
	rm -rf *o test
