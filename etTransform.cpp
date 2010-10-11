//
//  etTransform.cpp
//
//  Created by  on 2008-11-12.
//  Copyright (c) 2008 Electric Textiles and Thomson Comer. All rights reserved.
//

#include "etTransform.h"

/***********************************
* CONSTRUCTORS
************************************/
etTransform::etTransform()
{
    Rotation    = etVector(0.0f, 0.0f, 0.0f);
    Scaling     = etVector(0.0f, 0.0f, 0.0f);
    Translation = etVector(0.0f, 0.0f, 0.0f);
}
etTransform::etTransform( const etTransform &target )
{
    Rotation    = target.Rotation;
    Scaling     = target.Scaling;
    Translation = target.Translation;
}

/***********************************
* SUMMATION
************************************/
etTransform etTransform::operator+( const etTransform &target )
{
    return etTransform( Rotation + target.Rotation,
                        Scaling  + target.Scaling,
                        Translation + target.Translation );
}

etTransform etTransform::operator-( const etTransform &target )
{
    return etTransform( Rotation - target.Rotation,
                        Scaling  - target.Scaling,
                        Translation - target.Translation );
}

/***********************************
* RENDERING
************************************/
void etTransform::Apply()
{
    
}