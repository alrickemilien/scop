/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:01:17 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:01:37 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	reduce_ambient_lighting(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	env->ambient_lighting -= 0.05f;
	if (env->ambient_lighting < 0.0f)
		env->ambient_lighting = 0.0f;
}

void	increase_ambient_lighting(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	env->ambient_lighting += 0.05f;
	if (env->ambient_lighting > 1.0f)
		env->ambient_lighting = 1.0f;
}
