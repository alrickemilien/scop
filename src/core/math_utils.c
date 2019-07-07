#include "scop.h"

float	deg_to_rad(float deg)
{
	return (deg * ((float)M_PI / 180.0f));
}

/*
** Compute object barycentre
*/

t_vec3 compute_object_barycentre(t_list *positions)
{
	t_vec3	*p;
	t_vec3	barycentre;
	size_t	i;

	barycentre = (t_vec3){0.f, 0.f, 0.f};

	i = 0;
	while (positions)
	{
		p = (t_vec3*)positions->content;

		barycentre.x += p->x;
		barycentre.y += p->y;
		barycentre.z += p->z;

		positions = positions->next;

		i++;
	}

	barycentre.x /= (GLfloat)i;
	barycentre.y /= (GLfloat)i;
	barycentre.z /= (GLfloat)i;

	return (barycentre);
}

float	minf(float a, float b)
{
	return (a < b ? a : b);
}

float	maxf(float a, float b)
{
	return (a > b ? a : b);
}

float	percentage_f(float min, float max, float f)
{
	if (min == max)
		return (0);
	return ((f - min) / (max - min));
}