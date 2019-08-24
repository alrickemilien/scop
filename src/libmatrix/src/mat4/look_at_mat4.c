#include "libmatrix.h"

/*
** This is the look at / view matrix
** This matrix is used to move all coordinates
** according to camera position and look at direction
*/

static void	compute_forward(
		const t_vec3 *eye,
		const t_vec3 *center,
		t_vec3 *f)
{
	copy_vec3(f, eye);
	substract_vec3(f, center);
	normalize_vec3(f);
}

static void	compute_right(
		const t_vec3 *up,
		const t_vec3 *forward,
		t_vec3 *right)
{
	copy_vec3(right, up);
	cross_vec3(right, forward);
	normalize_vec3(right);
}

static void	compute_cam_up(
		const t_vec3 *forward,
		const t_vec3 *right,
		t_vec3 *cam_up)
{
	copy_vec3(cam_up, forward);
	cross_vec3(cam_up, right);
}

/*
** - eye is the camera positon
** - center is the position where the cameral looks at
** - up is the vector up of the camera coordinate system
**   in world coordinate system
** -----------------------------------------------------
** 1. Compute (in world coor) the direction z
**    of the z axis of the view coordinate system
**    as the negative normalized view direction (eye - center)
** 2. Compute (again in world coordinates) the direction x
**    of the x axis of the view coordinate system by
** 3. Compute (still in world coordinates) the direction y
**    of the y axis of the view coordinate system
*/

t_mat4		*look_at_mat4(
		const t_vec3 *eye,
		const t_vec3 *center,
		const t_vec3 *up)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	cam_up;
	t_mat4	*m;

	m = identity_mat4();
	if (are_vec3_equal(eye, center))
		return (m);
	compute_forward(eye, center, &forward);
	compute_right(up, &forward, &right);
	compute_cam_up(&forward, &right, &cam_up);
	m->value[0] = right.x;
	m->value[1] = cam_up.x;
	m->value[2] = forward.x;
	m->value[4] = right.y;
	m->value[5] = cam_up.y;
	m->value[6] = forward.y;
	m->value[8] = right.z;
	m->value[9] = cam_up.z;
	m->value[10] = forward.z;
	m->value[12] = -dot_product_vec3(&right, eye);
	m->value[13] = -dot_product_vec3(&cam_up, eye);
	m->value[14] = -dot_product_vec3(&forward, eye);
	return (m);
}
