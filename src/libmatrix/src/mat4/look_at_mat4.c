#include "libmatrix.h"

/*
** This is the look at / view matrix
** This matrix is used to move all coordinates
** according to camera position and look at direction
*/

static void compute_forward(const t_vec3 *eye, const t_vec3 *center, t_vec3 *f)
{
	copy_vec3(f, eye);
	substract_vec3(f, center);
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
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_mat4 *m;

	m = identity_matrix(4, 4);

  if (are_vec3_equal(eye, center))
		return (m);

	// Compute forward
	compute_forward(eye, center, &forward);

	// Compute right
	copy_vec3(&right, &up);
	normalize_vec3(&right);
	cross_vec3(&right, &forward);

	// Compute up
	copy_vec3(&up, &forward);
	cross_vec3(&up, &right);

	// Setup matrix
  m->value[0] = right->x;
  m->value[1] = right->y;
  m->value[2] = right->z;

  m->value[4] = up->x;
  m->value[5] = up->y;
  m->value[6] = up->z;

  m->value[8] = forward->x;
  m->value[9] = forward->y;
  m->value[10] = forward->z;

  m->value[12] = eye->x;
  m->value[13] = eye->y;
  m->value[14] = eye->z;

  return (m);
}
