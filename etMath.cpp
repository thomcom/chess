//
//  etMath.cpp
//
//  Created by  on 2008-11-07.
//  Copyright (c) 2008 Electric Textiles and Thomson Comer. All rights reserved.
//

#include "etMath.h"

namespace etMath
{
    // inverse square root
    float InvSqrt( float f )
    {
	    return FastInvSqrt( f );
    }
    // fast inverse square root
    float FastSqrt( float f )
    {
	    return f * FastInvSqrt( f );
    }
    // fast inverse square root (Gary Tarolli and opGames)
    // this method is based on the Quake 3 fast inverted square root
    // and recommended by Kevin Depue at opGames
    // I use 3 iterations of newton's method.
    float FastInvSqrt( float x )
    {
    	float xhalf = 0.5f * x;
    	int   i     = *(int*) &x;

    	i = 0x5f3759df - (i >> 1);
    	x = *(float*) &i;
    	x = x * (1.5f - xhalf * x * x);
    	x = x * (1.5f - xhalf * x * x);  
    	x = x * (1.5f - xhalf * x * x);  	  	
    	
    	return x;
    }
}
