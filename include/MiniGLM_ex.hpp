
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Defines.hpp"

#include <algorithm>
#include <array>
#include <cmath>

TMP<I N>using vc=array<F,N>;
using vc2=vc<2>;
using vc3=vc<3>;
using vc4=vc<4>;
#define VO(OP)                                  \
TMP<I N>vc<N> O OP(const vc<N>&l,const vc<N>&r) \
{                                               \
    vc<N> r;                                    \
    FOR(i,N)                                    \
        r[i]=l[i]OP r[i];                       \
    R r;                                        \
}                                               \
TMP<I N>vc<N> O OP(const vc<N>&l,F r)           \
{                                               \
    vc<N> r;                                    \
    FOR(i,N)                                    \
        r[i]=l[i]OP r;                          \
    R r;                                        \
}
VO(+)
VO(-)
VO(*)
VO(/)

/**
 * Clamps a value to a given range.
 * @param <T>    The type of the value
 * @param [in] v The value to clamp
 * @param [in] a The minimum value
 * @param [in] b The maximum value
 * @return The clamped value
 */
TMP<TYP T>T clmp(T t,T a,T b){R min(max(a,t),b);}

/**
 * Gets a linear interpolation from one floating point value to another using a 0-1 weighting.
 * @param [in] a The value to interpolate from
 * @param [in] b The value to interpolate to
 * @param [in] t The weight of the interpolation
 * @return The interpolated value
 */
F lrp(F a,F b,F t){R fma(t,b,fma(-t,a,a));}
