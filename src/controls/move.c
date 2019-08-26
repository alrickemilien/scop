/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:01:51 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:01:52 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	move_forward_on_axis(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	if (env->x_axis)
		env->mesh_offset.x++;
	if (env->y_axis)
		env->mesh_offset.y++;
	if (env->z_axis)
		env->mesh_offset.z++;
}

void	move_backward_on_axis(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	if (env->x_axis)
		env->mesh_offset.x--;
	if (env->y_axis)
		env->mesh_offset.y--;
	if (env->z_axis)
		env->mesh_offset.z--;
}
