/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pmatrix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 20:26:24 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 20:26:25 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

static const t_pmatrix_fmt	g_pmatrix_format_function[] = {
	{ "d", &libmatrix_itoa },
	{ "ld", &libmatrix_ltoa },
	{ "f", &libmatrix_ftoa },
	{ "glf", &libmatrix_ftoa },
	{ "gld", &libmatrix_itoa },
};

static int					apply_identifier(
		char *format,
		t_pmatrix_format_value *options)
{
	int i;

	i = 0;
	while (i * sizeof(t_pmatrix_fmt) < sizeof(g_pmatrix_format_function))
	{
		if (!libmatrixutil_memcmp(
					g_pmatrix_format_function[i].key,
					format,
					sizeof(char) * libmatrixutil_strlen(
						g_pmatrix_format_function[i].key)))
		{
			options->identifier = g_pmatrix_format_function[i];
			return (libmatrixutil_strlen(g_pmatrix_format_function[i].key));
		}
		i++;
	}
	return (0);
}

static int					apply_flag(
		char *format,
		t_pmatrix_format_value *options)
{
	int i;

	i = 0;
	while (*format && strchr(".0#+", *format) != NULL)
	{
		if (*format == '.')
			options->point = 1;
		else if (*format == '0')
			options->zero = 1;
		else if (*format == '#')
			options->hashtag = 1;
		else if (*format == '+')
			options->plus = 1;
		i++;
		format++;
	}
	return (0);
}

static int					apply_value(
	char **cursor_of_format,
	t_pmatrix_format_value *options,
	const void *value,
	char *value_str)
{
	int	ret;

	*cursor_of_format += apply_flag(++(*cursor_of_format), options);
	*cursor_of_format += apply_identifier(*cursor_of_format, options);
	ret = options->identifier.func(value, value_str);
	value_str[ret++] = ' ';
	return (ret);
}

/*
** Print a single value of the matrix with the format given in parameter
** return the size of the buffer
*/

static int					pvalue(
		const char *format,
		char **whole_buffer,
		const void *value)
{
	char					*buffer;
	char					*cof;
	int						ret;
	t_pmatrix_format_value	options;
	char					value_str[42];

	buffer = NULL;
	ret = 0;
	while (*format)
	{
		if ((cof = libmatrixutil_strchr(format, '%')) == NULL)
		{
			libmatrixutil_append_and_release_memory(&buffer,
					libmatrixutil_strdup(format));
			return ((ret += libmatrixutil_strlen(format)));
		}
		if (*cof == '%' && *(cof + 1) != '%' && *(cof + 1) != 0)
		{
			ret += apply_value(&cof, &options, value, value_str);
			libmatrixutil_append_and_release_memory_static(&buffer, value_str);
			format = cof;
		}
	}
	libmatrixutil_append_and_release_memory(whole_buffer, buffer);
	return (ret);
}

/*
** @param
** format - The format to follow for each value
** matrix - The matrix to print
*/

int							pmatrix(
		const char *format,
		const t_mat4 *matrix)
{
	size_t	i;
	int		ret;
	char	*buffer;

	i = 0;
	ret = 0;
	buffer = NULL;
	while (i < 16)
	{
		ret += pvalue(format, &buffer, &matrix->value[i]);
		if ((i + 1) % 4 == 0)
		{
			libmatrixutil_append_and_release_memory_static(&buffer, "\n");
			ret++;
		}
		i++;
	}
	if (write(1, buffer, ret) == -1)
		ret = -1;
	free(buffer);
	return (ret);
}
