/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_usemtl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:56:48 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:57:48 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Clear the environnement in memory
*/

void	del_usemtl(void *p, size_t s)
{
	t_usemtl	*u;

	(void)s;
	u = (t_usemtl*)p;
	free(u->mtl);
	free(u);
}
