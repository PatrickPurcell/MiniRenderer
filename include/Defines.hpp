
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

// #define MINI_RENDERER_UNGOLFED

#if defined _WIN32||defined _WIN64
#define WIN_32_LEAN_AND_MEAN
#define NOMINMAX
#define PW 1
#include<Windows.h>
#endif
#if defined __linux
#define PL 1
#include<X11/Xlib.h>
#endif

#define A auto
#define B uint8_t
// #define C Reserved for use in templates...TODO : Remove
#define D
#define E
#define F float
#define G
// #define H Reserved for global height
#define I int
#define J
#define K
#define L
#define M
// #define N Reserved for use in templates
#define O operator
#define P
#define Q
#define R return
#define S
// #define T Reserved for use in templates
#define U uint32_t // TODO : Remove
#define V void
// #define W Reserved for global width
#define X
#define Y
#define Z size_t // TODO : Remove
#define FOR(IT,NM)for(I IT=0;IT<NM;++IT)
#define TMP template
#define TYP typename
using namespace std;
