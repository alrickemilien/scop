/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:02:08 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:02:30 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	scale_up(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	env->scale += 0.1f;
}

void	scale_down(
		t_software_environ *env,
		GLFWwindow *window)
{
	(void)window;
	env->scale -= 0.1f;
}
