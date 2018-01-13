
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

#define PI 3.14159265358979f
#define RAD(DEG)(PI/180*DEG)

TMP<I N>using vc=array<F,N>;
using vc2=vc<2>;
using vc3=vc<3>;
using vc4=vc<4>;
#define VO(OP)                                  \
TMP<I N>vc<N> O OP(const vc<N>&l,const vc<N>&r) \
{                                               \
    vc<N> rv;                                   \
    FOR(i,N)                                    \
        rv[i]=l[i]OP r[i];                      \
    R rv;                                       \
}                                               \
TMP<I N>vc<N> O OP(const vc<N>&l,F r)           \
{                                               \
    vc<N> rv;                                   \
    FOR(i,N)                                    \
        rv[i]=l[i]OP r;                         \
    R rv;                                       \
}
VO(+)
VO(-)
VO(*)
VO(/)

/**
 * TODO : Documentation.
 */
TMP<I N>F dot(vc<N>&l,vc<N>&r){F rv=0;FOR(i,N)rv+=l[i]*r[i];R rv;}

/**
 * TODO : Documentation.
 */
TMP<I N>vc<N>nrmlz(vc<N>v){R v/sqrt(dot(v,v));}

/**
 * TODO : Documentation.
 */
vc3 cross(vc3&l,vc3&r){R{l[1]*r[2]-r[1]*l[2],l[2]*r[0]-r[2]*l[0],l[0]*r[1]-r[0]*
l[1]};}

/**
 * TODO : Documentation.
 */
using mtx=array<vc4, 4>;

/**
 * TODO : Documentation.
 */
mtx O*(const mtx&l,const mtx&r)
{
    vc4 sA0=l[0];
    vc4 sA1=l[1];
    vc4 sA2=l[2];
    vc4 sA3=l[3];
    vc4 sB0=r[0];
    vc4 sB1=r[1];
    vc4 sB2=r[2];
    vc4 sB3=r[3];
    R{
        sA0*sB0[0]+sA1*sB0[1]+sA2*sB0[2]+sA3*sB0[3],
        sA0*sB1[0]+sA1*sB1[1]+sA2*sB1[2]+sA3*sB1[3],
        sA0*sB2[0]+sA1*sB2[1]+sA2*sB2[2]+sA3*sB2[3],
        sA0*sB3[0]+sA1*sB3[1]+sA2*sB3[2]+sA3*sB3[3]
    };
}

/**
 * TODO : Documentation.
 */
vc4 O*(const mtx&m,const vc4&v)
{
    R vc4{
        m[0][0]*v[0]+m[1][0]*v[1]+m[2][0]*v[2]+m[3][0]*v[3],
        m[0][1]*v[0]+m[1][1]*v[1]+m[2][1]*v[2]+m[3][1]*v[3],
        m[0][2]*v[0]+m[1][2]*v[1]+m[2][2]*v[2]+m[3][2]*v[3],
        m[0][3]*v[0]+m[1][3]*v[1]+m[2][3]*v[2]+m[3][3]*v[3]
    };
}

/**
 * TODO : Documentation.
 */
mtx mtxIdnty(){R{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};}

/**
 * TODO : Documentation.
 */
mtx lookAt(vc3&e,vc3&c,vc3&up)
{
    vc3 f=nrmlz(c-e);
    vc3 s=nrmlz(cross(f,up));
    vc3 u=cross(s,f);
    mtx rv=mtxIdnty();
    rv[0][0]=s[0];
    rv[1][0]=s[1];
    rv[2][0]=s[2];
    rv[0][1]=u[0];
    rv[1][1]=u[1];
    rv[2][1]=u[2];
    rv[0][2]=-f[0];
    rv[1][2]=-f[1];
    rv[2][2]=-f[2];
    rv[3][0]=-dot(s,e);
    rv[3][1]=-dot(u,e);
    rv[3][2]=dot(f,e);
    R rv;
}

/**
 * TODO : Documentation.
 */
mtx prspctv(F fv,F ar,F zn,F zf)
{
    F tnHlfFv=tan(fv/2);
    mtx rv{};
    rv[0][0]=1/(tnHlfFv*ar);
    rv[1][1]=1/tnHlfFv;
    rv[2][3]=-1;
    rv[2][2]=zf/(zn-zf);
    rv[3][2]=-(zf*zn)/(zf-zn);
    R rv;
}

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
