#include "scop.h"

/*
** Compute "smartly" the camera position according to object size
** and barycentre it must face
*/

static void update_max(const t_vec3 *barycentre, t_vec3 *max, t_polygon *polygon)
{
	t_list		*y;
	t_vertex	*vertex;

	y = polygon->vertices;

	while (y) {
		vertex = (t_vertex*)y->content;

		if (max->x < (vertex->position->x - barycentre->x))
			max->x = vertex->position->x - barycentre->x;
        
        if (max->y < (vertex->position->y - barycentre->y))
			max->y = vertex->position->y - barycentre->y;

        if (max->z < (vertex->position->z - barycentre->z))
			max->z = vertex->position->z - barycentre->z;

        y = y->next;
	}
}

void smart_camera_position(t_software_environ *env,
    t_vec3 *camera_position,
    t_vec3 *camera_look_at_position,
    t_vec3 *camera_up)
{
	t_vec3 barycentre;
	t_vec3 max;
	t_list		*x;

	barycentre = compute_object_barycentre(env->data.positions);
	max = (t_vec3){0.0f, 0.0f, 0.0f};

	x = env->data.polygons;
	while (x)
	{
        update_max(&barycentre, &max, x->content);

		x = x->next;
	}

	printf("MAX : .x %f .y %f .z %f \n", max.x, max.y, max.z);

	// When empty object
	if (magnitude_vec3(&max) == 0)
	{
    	*camera_position = (t_vec3){5.f, 5.f, 5.f};
    	*camera_look_at_position = (t_vec3){0.f, 0.f, 0.f};;
    	*camera_up = (t_vec3){ 0.f, 1.f, 0.f };
		return;
	}

    // Get the module of the distance between the barycentre and the most far point

    GLfloat coeff = 1.5f;

    *camera_position = (t_vec3){barycentre.x + coeff * magnitude_vec3(&max), barycentre.y + coeff * magnitude_vec3(&max), barycentre.z + coeff * magnitude_vec3(&max)};
    *camera_look_at_position = barycentre;
    *camera_up = (t_vec3){ 0.f, 1.f, 0.f };
}