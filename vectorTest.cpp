//
//  vectorTest
//
//  Created by  on 2008-11-07.
//  Copyright (c) 2008 Colorado State University and Thomson Comer. All rights reserved.
//

/*!
* A testing driver for the etVector struct
*/

#include <stdio.h>
#include "etVector.h"

using etMath::etVector;

/*****************************************
* TEST FUNCTIONS FOR VECTOR.H/CPP
*****************************************/

int main(int argc, char* argv)
{
    float xyzNorm[3] = {0.577350269f, 0.577350269f, 0.577350269f};
    
    printf("Testing etVector Constructors for a coordinate: %f %f %f\n" , xyzNorm[0] , xyzNorm[1] , xyzNorm[2] );
    
    // piecewise constructor
    etVector piecewise( xyzNorm[0] , xyzNorm[1] , xyzNorm[2] , 1.0f );
    piecewise.etVectorSummary("piecewise constructor: \n");
    
    // copy constructor
    etVector copyConstructor( piecewise );
    copyConstructor.etVectorSummary("copy constructor: \n");
    
    // reference to 3+ dimensional vector constructor
    etVector referentialConstructor( xyzNorm );
    referentialConstructor.etVectorSummary("3d vector constructor: \n");
    
    // basic elements
    piecewise = copyConstructor;
    piecewise.x += 1.0f;
    piecewise.y += 1.0f;
    piecewise.z += 1.0f;
    piecewise.h += 1.0f;
    piecewise.etVectorSummary("piecewise + 1: \n");

    // scalar mult
    (piecewise * 2.0f).etVectorSummary("scalar multiplication k = 2: \n");
    
    // scalar division
    (piecewise / 2.0f).etVectorSummary("scalar division k = 2: \n");
    
    // ==
    char * outcome = "Equality measure failed!";
    if( copyConstructor == referentialConstructor )
        outcome = "They're equal: ";
    copyConstructor.etVectorSummary(outcome);
    referentialConstructor.etVectorSummary(outcome);
    
    // !=
    outcome = "Inequality measure failed!";
    if( copyConstructor != piecewise )
        outcome = "They're not equal: ";
    copyConstructor.etVectorSummary(outcome);
    piecewise.etVectorSummary(outcome);

    // cross product test
    etVector xy = etVector(0.707f , 0.707f , 0.0f);
    etVector z = etVector(0.0f , 0.0f , 1.0f);
    xy.CrossProduct(z).etVectorSummary("xy.CrossProduct(z): \n");
    (xy | z).etVectorSummary("xy | z: \n");
    
    // vector subtraction test
    outcome = "etVector subtraction failed!";
    if( piecewise - piecewise == etVector(0.0f, 0.0f, 0.0f) )
    {
        outcome = "piecewise minus itself is 0: \n";
    }
    (piecewise - piecewise).etVectorSummary(outcome);
    
    // vector addition test
    outcome = "etVector addition failed!";
    if( ( piecewise + piecewise ) == ( piecewise * 2 ) )
    {
        outcome = "piecewise plus itself equals self times 2: \n";
    }
    (piecewise + piecewise).etVectorSummary(outcome);
    
    // componentwise multiplication test
    etVector ones = etVector(1.0f, 1.0f, 1.0f);
    etVector tenths = etVector(0.1f, 0.1f, 0.1f);
    outcome = "Componentwise multiplication failed!";
    if( ones * tenths == tenths )
    {
        outcome = "ones * tenths = tenths: \n";
    }
    (ones * tenths).etVectorSummary(outcome);
    
    // dot product test
    printf("xy.DotProduct(z) = 0: %f\n",xy.DotProduct(z));
    printf("z ^ copyConstructor = 0.577: %f\n",z ^ copyConstructor);
    
    // normal of a normal vector is same vector
    etVector xyz = etVector( xyzNorm );
    outcome = "Normal of a normal vector isn't itself!";
    if( xyz.Normal() == xyz )
    {
        outcome = "Normal of a normal is itself\n";
    }
    (xyz - xyz.Normal()).etVectorSummary(outcome);
    
    // length of a normalized vector is 1
    etVector abc = etVector( 11.2f, 23.9f, 8.1f );
    abc.etVectorSummary("Original: ");
    abc.Normalize();
    abc.etVectorSummary("Normalized: ");
    printf( "Length of abc: %f\n",abc.Length() );
    
    printf( "SQUARE OF 16: %f\n",etMath::FastSqrt( 16.0f ) );
    if( etMath::FastSqrt( 16.0f ) == 4.0f) printf("Works for 16\n");
}

