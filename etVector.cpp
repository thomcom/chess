//
//  etVector.cpp
//
//  Created by  on 2008-10-30.
//  Copyright (c) 2008 Electric Textiles and Thomson Comer. All rights reserved.
//

#include <stdio.h>
#include "etVector.h"

namespace etMath
{

    /***********************************
    * CONSTRUCTORS
    ************************************/
    /// constructor that takes a 3d array as argument
    etVector::etVector( const float coords[] )
    {
        x = coords[0];
        y = coords[1];
        z = coords[2];
        h = 1.0f;
    
    }

    /// copy constructor
    etVector::etVector( const etVector &target )
    {
        x = target.x;
        y = target.y;
        z = target.z;
        h = target.h;
    
    }

    /***********************************
    * IN/EQUALITY
    ************************************/
    /// modeled after opGames opVector equality code
    bool etVector::operator==( const etVector &target )
    {
        return  x == target.x &&
                y == target.y &&
                z == target.z &&
                h == target.h;
    }

    /// Optimized version of opGames opVector inequality code.
    bool etVector::operator!=( const etVector &target )
    {
        return !(   x == target.x &&
                    y == target.y &&
                    z == target.z &&
                    h == target.h );
    }

    /***********************************
    * LINEAR ALGEBRA
    ************************************/
    /// Scalar multiplication
    etVector etVector::operator*( const float k ) const
    {
        return etVector(  k*x,
                        k*y,
                        k*z );
    }

    /// Scalar division
    etVector etVector::operator/( const float k ) const
    {
        return etVector(  x/k,
                        y/k,
                        z/k );
    }

    /// Cross product
    etVector etVector::CrossProduct( const etVector &target ) const
    {
        return *this | target;
    }

    /// Cross product operator
    etVector etVector::operator | ( const etVector &target ) const
    {
        return etVector(  y * target.z - z * target.y ,
                        z * target.x - x * target.z ,
                        x * target.y - y * target.x );
    }

    /// Vector addition
    etVector etVector::operator + ( const etVector &target ) const
    {
        return etVector(  x + target.x,
                        y + target.y,
                        z + target.z );
    }

    /// Vector subtraction
    etVector etVector::operator - ( const etVector &target ) const
    {
        return etVector(  x - target.x,
                        y - target.y,
                        z - target.z );
    }

    /// Component-wise
    etVector etVector::ComponentWise( const etVector &target ) const
    {
        return *this * target;
    }

    /// Component-wise multiplication (three weights)
    etVector etVector::operator * ( const etVector &target ) const
    {
        return etVector(  x * target.x,
                        y * target.y,
                        z * target.z );
    }

    /// Dot product
    float etVector::DotProduct( const etVector &target ) const
    {
        return *this ^ target;
    }

    /// Dot product operator
    float etVector::operator ^ ( const etVector &target ) const
    {
        return  x * target.x +
                y * target.y +
                z * target.z;
    }

    // Return a normalized copy of this vector
    etVector etVector::Normal() const
    {
    	return *this * InvLength();
    }

    // Normalize this vector.
    void etVector::Normalize()
    {
    	*this = Normal();
    }
    
    /***********************************
    * DEBUGGING
    ************************************/
    void etVector::etVectorSummary( const char * message )
    {
        printf("%s",message);
        etVectorSummary();
    }

    void etVector::etVectorSummary()
    {
        printf("Position: %f %f %f H: %f\n", x , y , z , h );
    }

}