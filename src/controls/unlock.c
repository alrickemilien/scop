/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlock.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:02:55 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:02:56 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	unlock_z_axis(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	env->z_axis = 0;
}

void	unlock_y_axis(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	env->y_axis = 0;
}

void	unlock_x_axis(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	env->x_axis = 0;
}
