//
//  etMouse.h
//
//  Created by  on 2008-11-12.
//  Copyright (c) 2008 Electric Textiles and Thomson Comer. All rights reserved.
//

#include "etTransform.h"

enum etMouseButton
{
    LEFT,
    MIDDLE,
    RIGHT
};

/*! class etMouse stores the current mouse state and computes any OpenGL state updates
* that depend on the mouse state.
*/
class etMouse
{
private:
    
    /// button-down state.
    bool leftbutton, middlebutton, rightbutton;
    
    /// last recorded position of mouse on screen
    int oldscreenx, oldscreeny;
    
    /// the current position of mouse on screen
    int currentscreenx, currentscreeny;
    
    /***********************************
    * MODIFIERS
    ************************************/
    constexpr const static float ROTATION_INCREMENT      = 0.2f;
    constexpr const static float TRANSLATION_INCREMENT   = 0.05f;
    
    /***********************************
    * ACCESSORS
    ************************************/
    /// set the old x/y positions
    /// --- This could be a problem at mouse initialization ---
    /// --- or if the mouse position is not continous.      ---
    void setOldPosition();
    
public:
    /// get the old x coordinate position
    int GetOldX()   { return oldscreenx; }
    /// get the old x coordinate position    
    int GetOldY()   { return oldscreeny; }
    /// get the change in x since the last mouse update
    int GetDeltaX() { return currentscreenx - oldscreenx; }
    /// get the change in y since the last mouse update
    int GetDeltaY() { return currentscreeny - oldscreeny; }
    
    /// set the current mouse position
    void SetPosition(int x, int y);    
    
    /// check if the mouse has moved
    bool HasMoved();
    
    /***********************************
    * CONSTRUCTORS
    ************************************/
    etMouse();
    
    /***********************************
    * STATE MODIFIERS
    ************************************/
    void Down( etMouseButton );
    void Up  ( etMouseButton );
    bool IsActive();
    
    /***********************************
    * RENDERING
    ************************************/
    /// state of current transformation, as modifiable by mouse state
    etTransform MouseUpdate;
    void Update();
    void ClearUpdate();        
    void ApplyRotation();
    void ApplyTranslation();
};
