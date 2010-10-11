//
//  sqrtTest
//
//  Created by  on 2008-11-07.
//  Copyright (c) 2008 Colorado State University and Thomson Comer. All rights reserved.
//

/*!
* a set of functions for testing the fast sqrt functions
*/

#include <stdio.h>
#include <math.h>

/*****************************************
* TEST FUNCTIONS FOR SQRT FUNCTIONS
*****************************************/

int main(int argc, char* argv)
{
    int mod        = 10000000;
    int iterations = 300000000;
    float error = 0.0f;
    for(int i = 0 ; i < iterations ; ++i)
    {
        float real      = (float)(i % mod) + 1;
        float realinv   = 1.0f / real;
        error           += realinv - 1.0f / sqrt( real * real );
    }
    printf("error: %f",error);
}

