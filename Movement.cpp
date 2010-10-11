/*
 *  Movement.cpp
 *  Chess
 *
 *  Created by Hugh Comer on 11/2/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "./Movement.h"

Movement::Movement()
{
	i=j=s=t=moveX=moveY=0;
	state = false;
}

void Movement::setObj(shape_ptr p)
{
	piece = p;
}

void Movement::on(bool value)
{
	state = value;
}

bool Movement::on()
{
	return state;
}

int* Movement::getDifference()
{
	int *Diff = new int[2];
	Diff[0] = s - i;
	Diff[1] = t - j;
	return Diff;
}

void Movement::setStart()
{
	s = getJ(piece->location);
	t = piece->location - s*8;
	cout << "s: " << s << " t: " << t << endl;
}

void Movement::setFinish(int pickedObject)
{
	i = getJ(pickedObject);
	j = pickedObject - i*8;
	cout << "i: " << i << " j: " << j << endl;
}

int Movement::getJ(int position)
{
		for(j=1;8*j<=position;j++);
		return j-1;	
}
