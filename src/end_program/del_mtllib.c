/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_mtllib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:58:00 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:58:03 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	del_mtllib(void *p, size_t s)
{
	t_mtllib	*u;

	(void)s;
	u = (t_mtllib*)p;
	ft_lstdel(&u->materials_list, &del_mtl_data);
	free(u->path);
	free(u);
}
