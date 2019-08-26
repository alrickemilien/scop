/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:42:38 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:42:39 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_matrix	rotate_object_around_point(
		t_software_environ *env, t_vec3 v)
{
	t_matrix	model_matrix;
	t_vec3		minus_v;

	minus_v = (t_vec3){-v.x, -v.y, -v.z};
	identity_mat4(&model_matrix);
	identity_mat4(&env->translation_matrix);
	translate_mat4(&env->translation_matrix, &v);
	multiply_mat4(&model_matrix, &env->translation_matrix);
	identity_mat4(&env->rotation_matrix);
	rotate_y_mat4(&env->rotation_matrix, env->y_auto_rotate_angle);
	multiply_mat4(&model_matrix, &env->rotation_matrix);
	identity_mat4(&env->translation_matrix);
	translate_mat4(&env->translation_matrix, &minus_v);
	multiply_mat4(&model_matrix, &env->translation_matrix);
	return (model_matrix);
}

void			apply_rotation(t_software_environ *env)
{
	t_vec3	minus_b;
	t_vec3	b;

	b = compute_object_barycentre(env->data.positions);
	b.x += env->mesh_offset.x;
	b.y += env->mesh_offset.y;
	b.z += env->mesh_offset.z;
	minus_b = (t_vec3){-b.x, -b.y, -b.z};
	env->y_auto_rotate_angle += 0.5f;
	if (env->y_auto_rotate_angle >= 360.f)
		env->y_auto_rotate_angle = 30.f;
	env->model_matrix = rotate_object_around_point(env, minus_b);
}
