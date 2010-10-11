/*
 *  Movement.h
 *  Chess
 *
 *  Created by Hugh Comer on 11/2/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _movement
#define _movement

#include "./defs.h"

class Movement
{
public:
	Movement();
	shape_ptr piece;
	int moveX;
	int moveY;
	void setObj(shape_ptr p);
	void setStart();
	void setFinish(int pickedObject);
	void on(bool value);
	bool on();
	int *getDifference();
private:
	int s,t,i,j;
	bool state;
	int getJ(int position);

};

#endif
