//
//  etVector.h
//
//  Created by  on 2008-10-30.
//  Copyright (c) 2008 Electric Textiles and Thomson Comer. All rights reserved.
//

#include "etMath.h"

namespace etMath
{

    struct etVector
    {

        /***********************************
        * CONSTRUCTORS
        ************************************/
        etVector( ) : x(0.0f) , y(0.0f) , z(0.0f) , h(1.0f) { }
        etVector( float _x , float _y , float _z , float _h ) : x(_x), y(_y), z(_z), h(_h) { }
        etVector( float _x , float _y , float _z )  : x(_x) , y(_y) , z(_z) , h(1.0f) {}
        etVector( const etVector &target );
        etVector( const float coords[] );
    
        /***********************************
        * IN/EQUALITY
        ************************************/
        bool operator==( const etVector &target );
        bool operator!=( const etVector &target );

        /***********************************
        * LINEAR ALGEBRA
        ************************************/    
        /// multiplication by a scalar
        etVector operator*( const float k ) const;
        /// multiplication by the inverse of a scalar (in linear algebra terms).
        /// Don't be confused, this is division as you'd expect it.
        etVector operator/( const float k ) const;
        /// cross product of two vectors ( pipe syntax from opGames )
        etVector CrossProduct( const etVector &target ) const;
        etVector operator|( const etVector &target ) const;
        /// sum of two vectors
        etVector operator+( const etVector &target ) const;
        /// difference of two vectors
        etVector operator-( const etVector &target ) const;
        /// COMPONENT-WISE multiplication of two vectors c_i = a_i * b_i
        etVector ComponentWise( const etVector &target ) const;
        etVector operator*( const etVector &target ) const;
        /// dot product of two vectors ( carrot syntax from opGames )
        float DotProduct( const etVector &target ) const;
        float operator^( const etVector &target ) const;

        // a copy of this vector, normalized
        etVector Normal() const;
        // normalize this vector
        void Normalize();
        // magnitude of *this
        const float Length() const { return FastSqrt( LengthSquared() ); }
        // square of length (it is faster than a length comparison thanks Kevin)
        const float LengthSquared() const { return x*x + y*y + z*z; }
        // inverse magnitude of *this
        const float InvLength() const { return FastInvSqrt( LengthSquared() ); }
    
        /***********************************
        * DEBUGGING
        ************************************/
        void etVectorSummary( const char * message );
        void etVectorSummary( );  
    
        /* x,y, and z are equivalent to and can be accessed by Vec3
        *  and vice versa */
        union
        {
            struct
            {
                float x,y,z,h;
            };
            float Vec3[3];
        };
    };
};