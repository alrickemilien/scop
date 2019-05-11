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
  # include <math.h>
  # include <GL/gl.h>
# else
  # include <OpenGL/gl.h>
  # include <unistd.h>
#endif

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <string.h>

# include "libmatrixerror.h"

# include "vec2.h"
# include "vec3.h"
# include "vec4.h"

/*
** Function that will have all matrix
** in order to acess specific value into it
** Use it like GLint = matrix->at(4, 2)
*/

typedef struct  s_matrix {
    GLfloat         value[32];
    size_t          lines;
    size_t          columns;
    float           determinant;
    float           trace;
    struct s_matrix *inverse;
}               t_matrix;

GLfloat   *matrix_at(t_matrix *m, size_t line, size_t column);
t_matrix  *new_matrix(size_t lines, size_t columns);
t_matrix  *new_matrix_from_raw(const float *raw, size_t lines, size_t columns);

/*
** Simple matrix operations
*/

bool compare_matrix(t_matrix *a, t_matrix *b);

t_matrix *get_minor(t_matrix *a, size_t line, size_t columns);

void fill_matrix(t_matrix *m, void *value);

// t_matrix destroyer
void  delete_matrix(t_matrix *matrix);

void fill_matrix(t_matrix *m, void *value);

t_matrix  *identity_matrix(size_t lines, size_t columns);

int inverse_matrix(t_matrix *a);

void multiply_matrix_with_scalar(t_matrix *a, GLfloat scalar);
int multiply_matrix(t_matrix *a, t_matrix *b, t_matrix *result);

int     add_matrix(t_matrix *a, t_matrix *b, t_matrix *result);
void copy_matrix(t_matrix *a, t_matrix *destination);
t_matrix *matrix_pow(t_matrix *a, int power);


GLfloat   get_transpose(t_matrix *a, t_matrix *transpose);
int       compute_inverse(t_matrix *a);
int       get_determinant(t_matrix *a);


/**
 * Utility function used to print a matrix to the standar output.
 *
 * @param m The matrix that should be printed.
 *
 * @return int
 * If the matrix doesn't exists it will return MATRIX_NOT_EXISTS
 * and NO_ERROR if the matrix was successfully printed.
 */

 typedef struct  s_pmatrix_format_map {
   char          *key;
   int           (*func)(void *i, char *buffer);
 }               t_pmatrix_format_map;

 typedef struct  s_pmatrix_format_value {
   int           point;
   int           zero;
   int           hashtag;
   int           plus;
   t_pmatrix_format_map identifier;
 }               t_pmatrix_format_value;

int  pmatrix(char *format, t_matrix *matrix);

/*
** Libmatrix utils
*/

void      libmatrixutil_reverse_string(char *str, int n);
void      *libmatrixutil_memcpy(void *dest, const void *src, size_t n);
int       libmatrixutil_memcmp(const void *s1, const void *s2, size_t n);
void	    libmatrixutil_bzero(void *s, size_t n);
void	    *libmatrixutil_memchr(const void *s, int c, size_t n);
size_t	  libmatrixutil_strlen(const char *s);
char	    *libmatrixutil_strchr(const char *s, int c);
char      *libmatrixutil_strndup(const char *s, size_t n);
char      *libmatrixutil_strdup(const char *s);
void      libmatrixutil_append_and_release_memory(char **buffer, char *str);
void      libmatrixutil_append_and_release_memory_static(char **buffer, const char *str);

/*
** Limatrix utils xtoa
*/

int libmatrix_itoa_hex(uint64_t value, char *buffer, uint64_t base);
int libmatrix_itoa(void *param, char *buffer);
int libmatrix_ltoa(void *param, char *buffer);
int libmatrix_ftoa(void *param, char *buffer);
int libmatrix_dtoa(void *v, char *buffer);
#ifdef __gl_h_
int libmatrix_glftoa(void *param, char *buffer);
int libmatrix_glitoa(void *param, char *buffer);
#endif

/*
** Specific matrix
*/

typedef t_matrix t_mat4;
typedef t_matrix t_mat3;

t_mat3 new_mat3();

t_mat4 *new_mat4();

t_mat4 *identity_mat4();

t_mat4	*look_at_mat4(
  const t_vec3 *eye,
  const t_vec3 *center,
	const t_vec3 *up);

t_mat4  *look_at_mat4_2(
  const t_vec3 *eye,
  const t_vec3 *center,
	const t_vec3 *up);

t_mat4 *perspective_mat4(
	GLfloat fov,
	GLfloat aspect,
	GLfloat near_plane,
	GLfloat far_plane);

t_mat4	*rotate_x_mat4(t_mat4 *m, GLfloat amount);
t_mat4	*scale_mat4(GLfloat amount);
t_mat4	*translate_mat4(t_mat4 *dest, const t_vec3 *amount);

#endif