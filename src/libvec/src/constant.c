#include "libvec.h"

/*
** Provides constant vector useful for camera manipulation
*/

static const t_vec3 vec3_origin = { 0, 0, 0 };

static const t_vec3 vec3_x = { 1, 0, 0 };
static const t_vec3 vec3_x_minus = { -1, 0, 0 };

static const t_vec3 vec3_y = { 0, 1, 0 };
static const t_vec3 vec3_y_minus = { 0, -1, 0 };

static const t_vec3 vec3_z = { 0, 0, 1 };
static const t_vec3 vec3_z_minus = { 0, 0, -1 };
