#ifndef _defs
#define _defs

#include <GL/freeglut.h>
//#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include "etVector.h"

using etMath::etVector;

using namespace std;

#define NONE			0

#define BOARDPIECE		1
#define BOARDBASE		2
#define PIECEBASE		3
#define REDPIECE		4
#define GREENPIECE		5

#define PAWN			21
#define ROOK			22
#define KNIGHT			23
#define BISHOP			24
#define QUEEN			25
#define KING			26

#define SPECULAR		30
#define DIFFUSE			31
#define AMBIENT			32

#define ZERO			"0"
#define ONE				"1"
#define TWO				"2"
#define THREE			"3"
#define FOUR			"4"
#define FIVE			"5"
#define SIX				"6"
#define SEVEN			"7"

#define ROTATE_MODE		11
#define TRANSLATE_MODE	12

#define MAX_NAME_BUFFER 1024

typedef struct object
{
    int type;
	float specmat[3];
    float diffmat[3];
	float ambimat[3];
	float shininess;
    float position[3];
	float rotation[3];
    float scale[3];
	int location;
    int ID;
	int texID;
    struct object *next;
} shape;

typedef shape* shape_ptr;

#endif

