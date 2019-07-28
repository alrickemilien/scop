#include "libmatrix.h"

/*
** Provides constant vector useful for camera manipulation
*/

static const t_vec3	vec3_origin = { 0, 0, 0 };

static const t_vec3	vec3_x = { 1, 0, 0 };
static const t_vec3	vec3_x_minus = { -1, 0, 0 };

static const t_vec3	vec3_y = { 0, 1, 0 };
static const t_vec3	vec3_y_minus = { 0, -1, 0 };

static const t_vec3	vec3_z = { 0, 0, 1 };
static const t_vec3	vec3_z_minus = { 0, 0, -1 };

void garabage() {
	(void)vec3_origin;
	(void)vec3_x;
	(void)vec3_x_minus;
	(void)vec3_y;
	(void)vec3_y_minus;
	(void)vec3_z;
	(void)vec3_z_minus;
}
