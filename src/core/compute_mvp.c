/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_mvp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:42:45 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:42:45 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4	*compute_mvp(t_software_environ *env, t_mat4 *mvp)
{
	identity_mat4(mvp);
	multiply_mat4(mvp, &env->model_matrix);
	multiply_mat4(mvp, &env->view_matrix);
	multiply_mat4(mvp, &env->projection_matrix);
	return (mvp);
}
