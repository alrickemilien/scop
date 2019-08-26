/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:01:42 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:01:45 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	lock_z_axis(t_software_environ *env, GLFWwindow *window)
{
	(void)window;
	env->x_axis = 0;
	env->y_axis = 0;
	env->z_axis = 1;
}

void	lock_y_axis(t_software_environ *env, GLFWwindow *window)
{
	(void)window;
	env->x_axis = 0;
	env->y_axis = 1;
	env->z_axis = 0;
}

void	lock_x_axis(t_software_environ *env, GLFWwindow *window)
{
	(void)window;
	env->x_axis = 1;
	env->y_axis = 0;
	env->z_axis = 0;
}
