/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_folder_from_path.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:00:25 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 19:00:26 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

/*
** This function extract the folder from the provided path
** where it is located.
** =======================================================
** Examples : the binary is executed at /root/
** /path/to/file => /path/to/
** path => /root/
** ./path/to/file => /root/path/to/
** path/to/file => ./path/to/
** /path/to/ => /path/
** ../ => /
** ../../path/to/file => /path/to/
** ./ => /
** . => /
** .. => /
*/

char	*extract_folder_from_path(
		const char *path)
{
	char	*tmp;
	char	*ret;

	tmp = strdup(path);
	ret = dirname(tmp);
	free(tmp);
	return (ret);
}
