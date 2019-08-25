#ifndef VEC4_H
#define VEC4_H

/*
** Pragma for packing data, no byte padding for alignement 
*/

#pragma pack(push, 1)
typedef struct	s_vec4 {
	GLfloat		x;
	GLfloat		y;
	GLfloat		z;
	GLfloat		w;
}				t_vec4;
#pragma pack(pop)

#endif