#ifndef VEC2_H
#define VEC2_H

/*
** Pragma for packing data, no byte padding for alignement 
*/

#pragma pack(push, 1)
typedef struct	s_vec2 {
	GLfloat		x;
	GLfloat		y;
}				t_vec2;
#pragma pack(pop)

#endif