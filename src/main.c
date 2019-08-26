/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:04:45 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:07:27 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_software_environ	*g_env = NULL;

void				stop_on_sigint(
	int signo)
{
	if (signo == SIGINT && g_env != NULL)
		glfwSetWindowShouldClose(WINDOW, GLFW_TRUE);
}

/*
** Could not continue if the system ressources
** are fully and successfully loaded
*/

int					main(
	int argc,
	char **argv)
{
	if (NULL == (g_env = malloc(sizeof(t_software_environ))))
		exit_error_with_message("Not enought memory to run the program");
	memset(g_env, 0, sizeof(t_software_environ));
	if (signal(SIGINT, stop_on_sigint) == SIG_ERR)
		fprintf(stderr, "Can't catch SIGINT\n");
	if (system_init(g_env, argc, argv) < 0)
		return (-1);
	glfw_init(g_env, argc, argv);
	run(g_env);
	end_program(0);
	return (0);
}
