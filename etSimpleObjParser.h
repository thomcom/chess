#ifndef _simpleobjparser
#define _simpleobjparser

#include "./defs.h"

/*! etSimpleObjParser reads in a simplified .obj file
* after it has been produced by blender. This class
* does not read any .obj file except those hand
* produced for this project
*/
class etSimpleObjParser
{
public:
	etSimpleObjParser(string filename);
	
	void BuildMesh();
	
	int CloseFile();
	int VertCount;
	int QuadCount;
	int TriangleCount;
	
	float* GetVertices();
	float* GetNormals();
	int* GetQuads();
	int* GetTriangles();
private:
    
	void openFile();
	ifstream infile;
	float* vertices;
	float* normals;
	int* quads;
	int* triangles;
	string filename;
};

#endif

