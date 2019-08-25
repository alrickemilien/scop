#include "scop.h"

void	compute_uv_sphere(t_polygon *vertexs_polygon)
{
	size_t      j;
	t_vec3      p;
	float       norm;
	t_vec2      *uv;
    t_vertex    *v;

	j = 0;
	while (j < 3)
	{
        v = (t_vertex*)lst_data_at(vertexs_polygon->vertices, j);
        
		p = *v->position;
		norm = sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
		p = (t_vec3){-p.x / norm, -p.y / norm, -p.z / norm};
	
    	uv = &v->uv_sphere;
	
    	uv->x = atan2f(p.x, p.z) / (2.0f * (float)M_PI) + 0.5f;
		uv->y = 0.5f - asinf(p.y) / (float)M_PI;
	
    	j++;
	}
}

void	normalize_uv_sphere(t_polygon *vertexs_polygon)
{
    GLfloat      u[3];
    t_vertex    *v[3];

    v[0] = (t_vertex*)lst_data_at(vertexs_polygon->vertices, 0);
    v[1] = (t_vertex*)lst_data_at(vertexs_polygon->vertices, 1);
    v[2] = (t_vertex*)lst_data_at(vertexs_polygon->vertices, 2);

	u[0] = v[0]->uv_sphere.x;
	u[1] = v[1]->uv_sphere.x;
	u[2] = v[2]->uv_sphere.x;
	
    if (u[0] < 0.2f && u[1] > 0.8f && u[2] > 0.8f)
		v[0]->uv_sphere.x = 0.99f;
	else if (u[1] < 0.2f && u[0] > 0.8f && u[2] > 0.8f)
		v[1]->uv_sphere.x = 0.99f;
	else if (u[2] < 0.2f && u[0] > 0.8f && u[1] > 0.8f)
		v[2]->uv_sphere.x = 0.99f;
	else if (u[0] > 0.8f && u[1] < 0.2f && u[2] < 0.2f)
		v[0]->uv_sphere.x = 0.0;
	else if (u[1] > 0.8f && u[0] < 0.2f && u[2] < 0.2f)
		v[1]->uv_sphere.x = 0.0f;
	else if (u[2] > 0.8f && u[0] < 0.2f && u[1] < 0.2f)
		v[2]->uv_sphere.x = 0.0f;
}

void	fill_vertex_uvs(t_polygon *vertexs_polygon)
{
	t_vec2	min;
	t_vec2	max;
    t_vertex *v[3];

    v[0] = (t_vertex*)lst_data_at(vertexs_polygon->vertices, 0);
    v[1] = (t_vertex*)lst_data_at(vertexs_polygon->vertices, 1);
    v[2] = (t_vertex*)lst_data_at(vertexs_polygon->vertices, 2);

	min = (t_vec2){minf(v[0]->position->x, v[1]->position->x),
		minf(v[0]->position->y, v[1]->position->y)};
	min = (t_vec2){minf(min.x, v[2]->position->x),
		minf(min.y, v[2]->position->y)};
	
    max = (t_vec2){maxf(v[0]->position->x, v[1]->position->x),
		maxf(v[0]->position->y, v[1]->position->y)};
	max = (t_vec2){maxf(max.x, v[2]->position->y),
		maxf(max.y, v[2]->position->y)};

	v[0]->uv = v[0]->uv ? v[0]->uv : new_vec2(
        percentage_f(min.x, max.x, v[0]->position->x),
		percentage_f(min.y, max.y, v[0]->position->y)
    );

	printf("UV : .x %f - .y %f\n", v[0]->uv->x, v[0]->uv->y);

	v[1]->uv = v[1]->uv ? v[1]->uv : new_vec2(
        percentage_f(min.x, max.x, v[1]->position->x),
		percentage_f(min.y, max.y, v[1]->position->y)
    );

	printf("UV : .x %f - .y %f\n", v[1]->uv->x, v[1]->uv->y);
	
    v[2]->uv = v[2]->uv ? v[2]->uv : new_vec2(
        percentage_f(min.x, max.x, v[2]->position->x),
		percentage_f(min.y, max.y, v[2]->position->y)
    );

	printf("UV : .x %f - .y %f\n", v[2]->uv->x, v[2]->uv->y);
}

void		set_default_uvs(t_polygon *polygon)
{
	t_vertex	*prev_vertex;
	t_vertex	*vertex;
	t_list		*x;

	prev_vertex = NULL;
	x = polygon->vertices;
	while (x)
	{
		vertex = (t_vertex*)x->content;
		
		if (vertex->uv) {
			prev_vertex = vertex;
			x = x->next;
			continue ;
		}

		if (prev_vertex == NULL
			|| (prev_vertex->uv->x == 0.0f && prev_vertex->uv->y == 1.0f))
		{
			vertex->uv = new_vec2(0.0f, 0.0f);
		}
		else if (prev_vertex->uv->x == 0.0f && prev_vertex->uv->y == 0.0f)
		{
			vertex->uv = new_vec2(1.0f, 0.0f);
		}
		else if (prev_vertex->uv->x == 1.0f && prev_vertex->uv->y == 0.0f)
		{
			vertex->uv = new_vec2(1.0f, 1.0f);
		}
		else if (prev_vertex->uv->x == 1.0f && prev_vertex->uv->y == 1.0f)
		{
			vertex->uv = new_vec2(0.0f, 1.0f);
		}

		prev_vertex = vertex;

		x = x->next;
	}
}


void	fill_uvs(t_list *polygon)
{
	// while (polygon)
	// {
	// 	compute_uv_sphere(polygon->content);
	// 	normalize_uv_sphere(polygon->content);
	// 	fill_vertex_uvs(polygon->content);

    //     polygon = polygon->next;
	// }

	while (polygon)
	{
		set_default_uvs(polygon->content);

        polygon = polygon->next;
	}
}