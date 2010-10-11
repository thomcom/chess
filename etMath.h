//
//  etMath
//
//  Created by  on 2008-11-07.
//  Copyright (c) 2008 Electric Textiles and Thomson Comer. All rights reserved.
//

namespace etMath
{
    /// inverse square root
    float InvSqrt( float f );
    /// fast square root using FastInvSqrt
    float FastSqrt( float f );
    /// fast inverse square root (Gary Tarolli and opGames)
    /// error is not as good as math::sqrt()
    float FastInvSqrt( float f );
}
