/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:01:07 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:01:09 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	close_window_callback(t_software_environ *env, GLFWwindow *window)
{
	(void)env;
	glfwSetWindowShouldClose(window, 1);
}
