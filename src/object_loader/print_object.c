#include "object_loader.h"

void lst_print(t_list *list, void (*p)(void *)) {
	while (list) {
		p(list->content);
		list = list->next;
	}
}

void		print_vec3(void *data)
{
	t_vec3		*pos;

	pos = (t_vec3 *)data;
	printf(
		"\tx = %lf\n"
		"\ty = %lf\n"
		"\tz = %lf\n\n",
		pos->x,
		pos->y,
		pos->z);
}

void		print_vec2(void *data)
{
	t_vec2		*pos;

	pos = (t_vec2 *)data;
	printf("\tx = %lf\n"
			"\ty = %lf\n\n",
			pos->x, pos->y);
}

void		print_poly_component(void *data)
{
	t_vertex	*component;

	component = (t_vertex *)data;
	puts("***");
	print_vec3(&component->position);
	print_vec2(&component->uv);
	print_vec3(&component->normal);
	puts("***");
}

void		print_polygons(void *data)
{
	t_list		*components;

	puts("---");
	components = (t_list *)((t_polygon *)data)->vertices;
	lst_print(components, print_poly_component);
	puts("---");
}

void			print_object(const t_obj_data *data)
{
	puts("--- POSITIONS ---");
	lst_print(data->positions, print_vec3);
	// puts("--- UVS ---");
	// lst_print(data->uvs, print_vec2);
	// puts("--- NORMALS ---");
	// lst_print(data->normals, print_vec3);
	// puts("--- POLYGONS ---");
	// lst_print(data->polygons, print_polygons);
}
