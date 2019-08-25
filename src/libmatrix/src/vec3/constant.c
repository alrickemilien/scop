#include "libmatrix.h"

/*
** Provides constant vector useful for camera manipulation
*/

static const	t_vec3	g__libvec__vec3_origin = { 0, 0, 0 };

static const	t_vec3	g__libvec__vec3_x = { 1, 0, 0 };
static const	t_vec3	g__libvec__vec3_x_minus = { -1, 0, 0 };

static const	t_vec3	g__libvec__vec3_y = { 0, 1, 0 };
static const	t_vec3	g__libvec__vec3_y_minus = { 0, -1, 0 };

static const	t_vec3	g__libvec__vec3_z = { 0, 0, 1 };
static const	t_vec3	g__libvec__vec3_z_minus = { 0, 0, -1 };

void garabage()
{
	(void)g__libvec__vec3_origin;
	(void)g__libvec__vec3_x;
	(void)g__libvec__vec3_x_minus;
	(void)g__libvec__vec3_y;
	(void)g__libvec__vec3_y_minus;
	(void)g__libvec__vec3_z;
	(void)g__libvec__vec3_z_minus;
}
