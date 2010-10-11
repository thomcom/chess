//
//  etMouse.cpp
//
//  Created by  on 2008-11-12.
//  Copyright (c) 2008 Electric Textiles and Thomson Comer. All rights reserved.
//

#include "etMouse.h"
#include <stdio.h>

/***********************************
* CONSTRUCTORS
************************************/
etMouse::etMouse()
{
    leftbutton      = false;
    middlebutton    = false;
    rightbutton     = false;    
    oldscreenx      = 0;
    oldscreeny      = 0;
    currentscreenx  = 0;
    currentscreeny  = 0;
}

/***********************************
* ACCESSORS
************************************/
// set the old position to be the current position. This is a separate
// function in case there are ever problems with mouse teleportation.
void etMouse::setOldPosition()
{
    oldscreenx = currentscreenx;
    oldscreeny = currentscreeny;
}
// set the current mouse position, after calling to update the old position.
void etMouse::SetPosition( int x, int y )
{
    setOldPosition();
    currentscreenx  = x;
    currentscreeny  = y;
}
// return true if the mouse has moved
bool etMouse::HasMoved()
{
    return ((currentscreenx - oldscreenx) != 0) || ((currentscreeny - oldscreeny) != 0);
}

/***********************************
* STATE MODIFIERS
************************************/
// update button states : up or down
void etMouse::Down( etMouseButton whichButton )
{
    switch( whichButton )
    {
        case LEFT:
            leftbutton  = true;
            break;
        case MIDDLE:
            middlebutton = true;
            break;
        case RIGHT:
            rightbutton = true;
    }
}
void etMouse::Up( etMouseButton whichButton )
{
    switch( whichButton )
    {
        case LEFT:
            leftbutton  = false;
            break;
        case MIDDLE:
            middlebutton = false;
            break;
        case RIGHT:
            rightbutton = false;            
    }    
}
bool etMouse::IsActive()
{
    return leftbutton || rightbutton || middlebutton;    
}

/***********************************
* RENDERING
************************************/
void etMouse::ApplyRotation()
{

    MouseUpdate.Rotation = etVector( GetDeltaX() * ROTATION_INCREMENT , GetDeltaY() * ROTATION_INCREMENT , 0.0f );
    printf("Rotation xy: %d %d\n", GetDeltaX(), GetDeltaY() );
    MouseUpdate.Rotation.etVectorSummary("MouseUpdate:");
	//if( (abs((int)spinx)+90)/180%2==1 ) mouseUpdate.Rotation = spiny - .2*(y-mouse::oldY);
	//else spiny = spiny + .2*(y-mouse::oldY);
	
}

void etMouse::ApplyTranslation()
{
    MouseUpdate.Translation = MouseUpdate.Translation + etVector( GetDeltaX() * TRANSLATION_INCREMENT , -GetDeltaY() * TRANSLATION_INCREMENT , 0.0f );
}

void etMouse::Update()
{
    if(leftbutton) ApplyTranslation();
    if(rightbutton) ApplyRotation();
}

void etMouse::ClearUpdate()
{
    MouseUpdate.Rotation = etVector( 0.0f, 0.0f, 0.0f );
}