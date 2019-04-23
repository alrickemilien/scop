#include "libmatrix.h"

/*
** This is the look at / view matrix
** This matrix is used to move all coordinates
** according to camera position and look at direction
*/

static void step_one(t_matrix *m, t_vec3 *f, t_vec3 *s, t_vec3 *u)
{
  m->value[0] = s->x;
  m->value[4] = s->y;
  m->value[8] = s->z;
  m->value[1] = u->x;
  m->value[5] = u->y;
  m->value[9] = u->z;
  m->value[2] = -f->x;
}

static void step_two(t_matrix *m, t_vec3 *f, t_vec3 *s, const t_vec3 *eye)
{
  m->value[6] = -f->y;
  m->value[10] = -f->z;
  m->value[12] = -dot_product_vec3(s, eye);
}

static void step_three(t_matrix *m, t_vec3 *f, t_vec3 *u, const t_vec3 *eye)
{
  m->value[14] = dot_product_vec3(f, eye);
  m->value[13] = -dot_product_vec3(u, eye);
}

static void compute_direction(const t_vec3 *eye, const t_vec3 *center, t_vec3 *f)
{
	copy_vec3(f, center);
	substract_vec3(f, eye);
	normalize_vec3(f);
}

/*
** - eye is the camera positon
** - center is the position where the cameral looks at
** - up is the vector up of the camera coordinate system in world coordinate system
** ---------------------------------------------------------------------------------------------
** 1. Compute (in world coordinates) the direction z of the z axis of the view coordinate system
**    as the negative normalized view direction (eye - center)
** 2. Compute (again in world coordinates) the direction x of the x axis of the view coordinate system by
** 3. Compute (still in world coordinates) the direction y of the y axis of the view coordinate system
*/

t_mat4	*look_at_mat4(
  const t_vec3 *eye,
  const t_vec3 *center,
	const t_vec3 *up)
{
	t_vec3	f;
	t_vec3	s;
	t_vec3	u;
	t_mat4 *m;

	m = identity_matrix(4, 4);

  if (are_vec3_equal(eye, center))
		return (m);

	compute_direction(eye, center, &f);

	copy_vec3(&s, &f);
	cross_vec3(&s, up);
	normalize_vec3(&s);

	copy_vec3(&u, &s);
	cross_vec3(&u, &f);

	step_one(m, &f, &s, &u);
	step_two(m, &f, &s, eye);
	step_three(m, &f, &u, eye);

  return (m);
}
