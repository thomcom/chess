#include "./etSimpleObjParser.h"

etSimpleObjParser::etSimpleObjParser(string file)
{
	filename = file;
	ifstream infile;
	VertCount = 0;
	QuadCount = 0;
	TriangleCount = 0;
	vertices = NULL;
	quads = NULL;
	triangles = NULL;
}

void etSimpleObjParser::openFile()
{
	cout << filename;
	infile.open(filename.c_str());
	if(infile.fail())
	{
		cout << "Counting" << endl;
		cout << "File open failure![01]" << endl;
		exit(1);
	}
}

int etSimpleObjParser::CloseFile()
{
	infile.close();
	return 1;
}

void etSimpleObjParser::BuildMesh()
{
	QuadCount = 0;
	TriangleCount = 0;
	
	openFile();
	
	string name;
	string buffer = "";
	string garbage;
	
	infile >> name;
	infile >> VertCount;
	
	vertices = new float[VertCount*3];
	int* tempquads = new int[VertCount*5];
	int* temptriangles = new int[VertCount*5];
	
//	vertices = new float[VertCount*3];	
//	quads = new int[VertCount*3];
//	triangles = new int[VertCount*3];
	
	for(int i=0;i<VertCount;i++)
	{
		if(infile.eof())
		{
			cout << name << " has incorrect file format!" << endl;
			break;
		}
		infile >> vertices[i * 3 + 0] >> vertices[i * 3 + 1] >>
			vertices[i * 3 + 2];
//		cout << vertices[i * 3 + 0]  << " " << vertices[i * 3 + 1] << " "
//			<< vertices[i  * 3 + 2]	<< " " << endl;
	}
	while(true)
	{
		if(infile.eof())
		{
			cout << name << " processed." << endl;
			break;
		}
		infile >> garbage;
		if( garbage=="4" )
		{	
//			tempquads[QuadCount * 4] = 4;
			infile >> tempquads[QuadCount * 4 + 0] >>
				tempquads[QuadCount * 4 + 1] >>
				tempquads[QuadCount * 4 + 2] >>
				tempquads[QuadCount * 4 + 3];
//			cout << tempquads[QuadCount * 4 + 0]  << " " << tempquads[QuadCount * 4 + 1] << " "
//				<< tempquads[QuadCount  * 4 + 2]	<< " " << tempquads[QuadCount * 4 + 3] << endl;
			QuadCount++;
		}
		else if( garbage=="3" )
		{
//			temptriangles[TriangleCount * 3] = 3;
			infile >> temptriangles[TriangleCount * 3 + 0] >>
				temptriangles[TriangleCount * 3 + 1] >>
				temptriangles[TriangleCount * 3 + 2];
//			cout << temptriangles[TriangleCount * 3 + 0] << " " <<
//				temptriangles[TriangleCount * 3 + 1] << " " <<
//				temptriangles[TriangleCount * 3 + 2] << endl;
			TriangleCount++;
		}
		infile >> garbage;
	}
	quads = new int[QuadCount*4];
	for(int i=0;i<QuadCount*4;i++)
	{
		quads[i]=tempquads[i];
//		cout << quads[i] << " ";
//		if(i%4==3) cout << endl;
	}
	triangles = new int[TriangleCount*3];
	for(int i=0;i<TriangleCount*3;i++)
	{
		triangles[i]=temptriangles[i];
//		cout << triangles[i] << " ";
//		if(i%3==2) cout << endl;
	}
	CloseFile();
}

float* etSimpleObjParser::GetVertices()
{
	return vertices;
}

int* etSimpleObjParser::GetQuads()
{
//	for(int i =0;i<10;i++) cout << " " << quads[i];
	return quads;
}

int* etSimpleObjParser::GetTriangles()
{
	return triangles;
}
