#ifndef LIBMATRIX_H
#define LIBMATRIX_H

/*
** Scop embed it's own matrix library
** the library target is for graphic transformation
** It is a row major matrix implementation
** In a row-major order, the consecutive elements of a row
** reside next to each other
** For example the matrix :
**     [a11 a12 a13]
** A = [a21 a22 a23]
** Row-major order (lexographical access order) :
** Address  Access    Value
** 0        A[0]   a11
** 1        A[1]   a12
** 2        A[2]   a13
** 3        A[3]   a21
** 4        A[4]   a22
** 5        A[5]   a23
*/

#ifdef _MSC_VER
  #define _USE_MATH_DEFINES // for C
  # include <windows.h>
  # include <GL/gl.h>
# else
  # include <OpenGL/gl.h>
  # include <unistd.h>
#endif

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <string.h>

# include "libmatrixerror.h"

# include "vec2.h"
# include "vec3.h"
# include "vec4.h"
# include "mat4.h"

#endif