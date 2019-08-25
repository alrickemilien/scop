#include "scop.h"

static bool is_vertex_same(const void *a, const void *b) {
	t_vertex    *va;
	t_vertex    *vb;

	va = (t_vertex*)a;
	vb = (t_vertex*)b;
	
	if (va->position == vb->position)
		return (true);

	return (false);
}

static void look_at_polygon(
    t_vec3 *normal,
    t_vertex *vertex,
    t_list *vertex_list,
    size_t *n)
{
    bool        found;
    t_vertex    *vec[3];
    size_t      i;

    i = 0;
    found = false;
	while (vertex_list)
	{
        vec[i] = (t_vertex*)vertex_list->content;

        // printf("vec[%ld] position index : %ld\n", i, vec[i]->position_index);
        // printf("vertex position index : %ld\n", vertex->position_index);
        // printf("%s\n", "================================================");

        if (is_vertex_same(vec[i], vertex))
            found = true;

		vertex_list = vertex_list->next;
        i++;
	}

    // printf("%s\n", "ooooooooooooooooooooooooooooooooooooooooooooo");

    if (!found)
        return ;
    *n += 1;
    if (is_vertex_same(vec[0], vertex))
        *normal = add_vec3(
            normal,
            cross_vec3(
                sub_vec3(*vec[1]->position, *vec[0]->position),
                sub_vec3(*vec[2]->position, *vec[0]->position)));
    if (is_vertex_same(vec[1], vertex))
        *normal = add_vec3(
            *normal,
            cross_vec3(
                sub_vec3(*vec[0]->position, *vec[1]->position),
                sub_vec3(*vec[2]->position, *vec[1]->position)));
    if (is_vertex_same(vec[2], vertex))
        *normal = add_vec3(
            *normal,
            cross_vec3(
                sub_vec3(*vec[0]->position, *vec[2]->position),
                sub_vec3(*vec[1]->position, *vec[2]->position)));
}

/*
** Look for each polygon
** when polygon has the provided vertex
** sum it's polygon normal
** at the end, divide each component by the number of polygon
** and set the vertex's normal
*/

void        compute_vertex_normal(
    t_mesh *mesh,
    t_vertex *vertex,
    t_vec3 *normal)
{
	t_polygon   *p;
	t_list	    *x;
	size_t	    n;

	memset(normal, 0, sizeof(t_vec3));

	// Look each each polygon
	x = mesh->polygons;
	n = 0;
	while (x)
	{
		p = (t_polygon*)x->content;

        look_at_polygon(
            normal,
            vertex,
            p->vertices,
            &n);
		
		x = x->next;
	}

    if (n == 0)
        return ;

	*normal = (t_vec3){normal->x / n, normal->y / n, normal->z / n};

	// printf("N : .x %f .y %f .z %f \n", normal->x, normal->y, normal->z);
}