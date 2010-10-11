
#include "./defs.h"
#include "./Mystack.h"
#include "./Shapemove.h"

void addGreen(Mystack& objects, int square, int& objID, int type)
{
//	cout << "Toggled Green" << endl;
//	cout << objects.find(square) << endl;
	if( objects.find(square)->type>20 && objects.find(square)->type<27 )
	{
//		cout << "Tried to erase someone." << endl;
		objects.erase(square);
//		cout << "I erased " << square << " at " << square << endl;
	}
	else
	{
//		cout << "Tried to add someone." << endl;
		shape_ptr p = new shape;
		p->type = type;
		p->location = square;
		p->ambimat[0] = .1;
		p->ambimat[1] = .4;
		p->ambimat[2] = .15;
		p->specmat[0] = .3;
		p->specmat[1] = .3;
		p->specmat[2] = .3;
		p->diffmat[0] = .2;
		p->diffmat[1] = .8;
		p->diffmat[2] = .3;
//		p->ambimat[0] = .1;
//		p->ambimat[1] = .1;
//		p->ambimat[2] = .1;
//		p->specmat[0] = .5;
//		p->specmat[1] = .5;
//		p->specmat[2] = .5;
//		p->diffmat[0] = .1;
//		p->diffmat[1] = .1;
//		p->diffmat[2] = .1;
		p->shininess = 8;
		p->position[0] = -3.5 + (square/8);
		p->position[1] = 0.2;
		p->position[2] = -3.5 + (square%8);
		p->rotation[0] = 0;
		p->rotation[1] = 0;
		p->rotation[2] = 0;
		p->scale[0] = .3;
		p->scale[1] = .3;
		p->scale[2] = .3;
	
		p->ID = objID;
		objID++;
		objects.push(p);
	}
}

void addRed(Mystack& objects, int square, int& objID, int type)
{
//	cout << "Toggled Red" << endl;
	if( objects.find(square)->type>20 && objects.find(square)->type<27 ) objects.erase(square);
	else
	{
		shape_ptr p = new shape;
		p->type = type;
		p->location = square;
		p->ambimat[0] = .4;
		p->ambimat[1] = .15;
		p->ambimat[2] = .15;
		p->specmat[0] = .3;
		p->specmat[1] = .3;
		p->specmat[2] = .3;
		p->diffmat[0] = .8;
		p->diffmat[1] = .3;
		p->diffmat[2] = .3;
//		p->ambimat[0] = .7;
//		p->ambimat[1] = .7;
//		p->ambimat[2] = .7;
//		p->specmat[0] = 1;
//		p->specmat[1] = 1;
//		p->specmat[2] = 1;
//		p->diffmat[0] = .8;
//		p->diffmat[1] = .8;
//		p->diffmat[2] = .8;
		p->shininess = 8;
		p->position[0] = -3.5 + (square/8);
		p->position[1] = 0.2;
		p->position[2] = -3.5 + (square%8);
		p->rotation[0] = 0;
		p->rotation[1] = 0;
		p->rotation[2] = 0;
		p->scale[0] = .3;
		p->scale[1] = .3;
		p->scale[2] = .3;
	
		p->ID = objID;
		objID++;
		objects.push(p);
	}
}
