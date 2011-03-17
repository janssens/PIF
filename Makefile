CPP=g++
#CCFLAGS=-c -Wall
CCFLAGS = -g -O2
LIBS=
LIBSDIR = -L./
INCLDIR = -I./
SOURCES=Type.cpp main.cpp testVertex.cpp testEdge.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= testVertex testEdge testVect testFace testMesh

all: $(EXECUTABLE)

############################################
# just a testing file for Vertex
############################################	
testVertex: testVertex.o Type.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
testVertex.o: testVertex.cpp Type.hpp 
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  testVertex.cpp
	
############################################
# just a testing file for Edges
############################################	
testEdge: testEdge.o Type.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
testEdge.o: testEdge.cpp Type.hpp 
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  testEdge.cpp
	
############################################
# just a testing file for Vect
############################################	
testVect: testVect.o Type.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
testVect.o: testVect.cpp Type.hpp 
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  testVect.cpp
	
############################################
# just a testing file for Faces
############################################	
testFace: testFace.o Type.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
testFace.o: testFace.cpp Type.hpp 
	$(CPP) $(CCFLAGS)  $(INCLDIR) -c  testFace.cpp
	
############################################
# just a testing file for Mesh
############################################	
testMesh: testMesh.o Type.o
	$(CPP) $(LIBS) $(CCFLAGS) $(LIBSDIR)   $^ -o $@
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
