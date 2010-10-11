//
//  etTransform.h
//
//  Created by  on 2008-11-12.
//  Copyright (c) 2008 Electric Textiles and Thomson Comer. All rights reserved.
//

#include "defs.h"

/*! struct etTransform is intended to serve as a generic class for storing OpenGL transformation
* information. Each object that is capable of producing MODELVIEW transforms in the OpenGL 
* state machine must contain one Transform object. During the render phase of an application,
* each Transform object can be applied individually, or summed together and applied one time.
* etTransform is designed to be used with the OpenGL matrix modification commands glRotatefv,
* glScalefv, and glTranslatefv.
*/
struct etTransform
{
    // the amount to rotate in x,y, and z
    etVector Rotation;
    
    // scale should not be used - if it is used, it must be uniform.
    // non-uniform scaling prevents the shader from being reprogrammed.
    etVector Scaling;
    
    // translation in x,y, and z
    etVector Translation;

    /***********************************
    * CONSTRUCTORS
    ************************************/
    etTransform();
    etTransform( const etTransform &target );
    etTransform( const etVector &rot, const etVector &scal, const etVector &trans) : Rotation(rot), Scaling(scal), Translation(trans) {};
    
    /***********************************
    * SUMMATION
    ************************************/
    etTransform operator+( const etTransform &target );
    etTransform operator-( const etTransform &target );
    
    /***********************************
    * RENDERING
    ************************************/
    void Apply();
};
