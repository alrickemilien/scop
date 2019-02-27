/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 17:34:19 by aemilien          #+#    #+#             */
/*   Updated: 2016/12/05 17:00:33 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t		i;
	size_t		j;
	size_t		l;

	l = strlen(s1) + strlen(s2);
	new_str = malloc(sizeof(char) * (l + 1));
	if (!new_str)
		return (NULL);
	new_str[l] = 0;
	j = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		new_str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		new_str[j] = s2[i];
		i++;
		j++;
	}
	return (new_str);
}
