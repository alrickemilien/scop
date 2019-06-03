#ifndef MAT_4
# define MAT_4

typedef struct  s_matrix {
    GLfloat         value[32];
}               t_matrix;

typedef t_matrix t_mat4;

t_mat4  *new_mat4();

/*
** Simple matrix operations
*/

void    fill_mat4(t_mat4 *m, void *value);

void    delete_matrix(t_matrix *matrix);

void    scale_mat4(t_mat4 *a, GLfloat scalar);
int     multiply_mat4(t_mat4 *a, t_mat4 *b, t_mat4 *result);

void     add_mat4(t_mat4 *a, t_mat4 *b, t_mat4 *result);
void    copy_mat4(t_mat4 *a, t_mat4 *destination);

/**
 ** Utility function used to print a matrix to the standar output.
 ** @param m The matrix that should be printed.
 ** @return int
 ** If the matrix doesn't exists it will return MATRIX_NOT_EXISTS
 ** and NO_ERROR if the matrix was successfully printed.
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

int  pmatrix(char *format, t_mat4 *matrix);

/*
** Specific matrix
*/

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

void  rotate_x_mat4(t_mat4 *m, GLfloat amount);
void  rotate_y_mat4(t_mat4 *m, GLfloat amount);
void  rotate_z_mat4(t_mat4 *m, GLfloat amount);
void  translate_mat4(t_mat4 *dest, const t_vec3 *amount);
void	transpose_mat4(t_matrix *a);

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
# ifdef __gl_h_
int libmatrix_glftoa(void *param, char *buffer);
int libmatrix_glitoa(void *param, char *buffer);
# endif

#endif