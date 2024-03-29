#ifndef MAT4_H
# define MAT4_H

typedef struct		s_matrix {
	GLfloat			value[16];
}					t_matrix;

typedef t_matrix	t_mat4;

/*
** Simple matrix operations
*/

void				fill_mat4(
		t_mat4 *m,
		void *value);

t_mat4				scale_mat4(
		t_mat4 *a,
		GLfloat scalar);

t_mat4				scale_to_mat4(
		const t_mat4 *src,
		t_mat4 *dest,
		GLfloat scalar);

t_mat4				multiply_mat4(
		t_mat4 *a,
		const t_mat4 *b);
t_mat4				multiply_to_mat4(
		const t_mat4 *a,
		const t_mat4 *b,
		t_mat4 *result);

t_mat4				add_mat4(
		t_mat4 *a,
		const t_mat4 *b);
t_mat4				add_to_mat4(
		const t_mat4 *a,
		const t_mat4 *b,
		t_mat4 *result);

t_mat4				copy_mat4(
		t_mat4 *a,
		t_mat4 *destination);

/*
** Utility function used to print a matrix to the standar output.
** @param m The matrix that should be printed.
** @return int
** If the matrix doesn't exists it will return MATRIX_NOT_EXISTS
** and NO_ERROR if the matrix was successfully printed.
*/

typedef struct		s_pmatrix_fmt {
	char			*key;
	int				(*func)(
			const void *i,
			char *buffer);
}					t_pmatrix_fmt;

typedef struct		s_pmatrix_format_value {
	int				point;
	int				zero;
	int				hashtag;
	int				plus;
	t_pmatrix_fmt	identifier;
}					t_pmatrix_format_value;

int					pmatrix(
		const char *format,
		const t_mat4 *matrix);
void				printmat4(const t_mat4 *m);

/*
** Specific matrix
*/

t_mat4				identity_mat4(t_mat4 *m);

t_mat4				look_at_mat4(
		const t_vec3 *eye,
		const t_vec3 *center,
		const t_vec3 *up);

t_mat4				perspective_mat4(
		GLfloat fov,
		GLfloat aspect_ratio,
		GLfloat znear,
		GLfloat zfar);

t_mat4				rotate_x_mat4(
		t_mat4 *m,
		GLfloat amount);
t_mat4				rotate_y_mat4(
		t_mat4 *m,
		GLfloat amount);
t_mat4				rotate_z_mat4(
		t_mat4 *m,
		GLfloat amount);

t_mat4				rotate_x_to_mat4(
		t_mat4 *src, t_mat4 *dest, GLfloat angle);
t_mat4				rotate_y_to_mat4(
		t_mat4 *src, t_mat4 *dest, GLfloat angle);
t_mat4				rotate_z_to_mat4(
		t_mat4 *src, t_mat4 *dest, GLfloat angle);

t_mat4				translate_mat4(
		t_mat4 *dest,
		const t_vec3 *amount);
t_mat4				translate_to_mat4(
		const t_mat4 *src,
		t_mat4 *dest,
		const t_vec3 *amount);
t_mat4				transpose_mat4(
		t_mat4 *a);
t_mat4				transpose_to_mat4(
		const t_mat4 *src,
		t_mat4 *dest);

t_vec3				mat4_on_vec3(
		t_vec3 *v,
		const t_mat4 *m);
t_vec3				mat4_to_vec3(
		const t_vec3 *src,
		t_vec3 *dest,
		const t_mat4 *m);

/*
** Libmatrix utils
*/

void				libmatrixutil_reverse_string(
		char *str, int n);
void				*libmatrixutil_memcpy(
		void *dest, const void *src, size_t n);
int					libmatrixutil_memcmp(
		const void *s1, const void *s2, size_t n);
void				libmatrixutil_bzero(
		void *s, size_t n);
void				*libmatrixutil_memchr(
		const void *s, int c, size_t n);
size_t				libmatrixutil_strlen(
		const char *s);
char				*libmatrixutil_strchr(
		const char *s, int c);
char				*libmatrixutil_strndup(
		const char *s, size_t n);
char				*libmatrixutil_strdup(
		const char *s);
void				libmatrixutil_append_and_release_memory(
		char **buffer, char *str);
void				libmatrixutil_append_and_release_memory_static(
		char **buffer, const char *str);

/*
** Limatrix utils xtoa
*/

int					libmatrix_itoa_hex(
		uint64_t value, char *buffer, uint64_t base);
int					libmatrix_itoa(
		const void *param, char *buffer);
int					libmatrix_ltoa(
		const void *param, char *buffer);
int					libmatrix_ftoa(
		const void *param, char *buffer);
int					libmatrix_dtoa(
		const void *v, char *buffer);

#endif
