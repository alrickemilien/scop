/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_mtl_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:22:33 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:22:34 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material_template_library_loader.h"

int	read_mtl_error(const char *msg)
{
	fprintf(stderr, "%s\n", msg);
	return (-1);
}
