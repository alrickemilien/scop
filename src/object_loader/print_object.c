/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:18:58 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:18:59 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object_loader.h"

static void		lst_print(
	t_list *list,
	void (*p)(void *))
{
	while (list)
	{
		p(list->content);
		list = list->next;
	}
}

static void		print_poly_component(void *data)
{
	t_vertex	*component;

	component = (t_vertex *)data;
	printf("***"
			"POSITION - %ld\n",
			component->position_index);
	print_vec3(&component->position);
	puts("UV");
	print_vec2(&component->uv);
	puts("NORMAL");
	print_vec3(&component->normal);
	puts("***");
}

static void		print_polygons(void *data)
{
	t_list		*components;

	puts("--- POLYGON");
	components = (t_list *)((t_polygon *)data)->vertices;
	lst_print(components, print_poly_component);
	puts("---\n");
}

void			print_object(const t_mesh *data)
{
	puts("--- POLYGONS ---");
	lst_print(data->polygons, print_polygons);
}
