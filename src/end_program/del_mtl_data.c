/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_mtl_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:56:25 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:56:35 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	del_mtl_data(void *p, size_t s)
{
	t_mtl_data	*u;

	(void)s;
	u = (t_mtl_data*)p;
	if (u->label)
		free(u->label);
	free(u);
}