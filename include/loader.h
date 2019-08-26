/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aemilien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 21:02:04 by aemilien          #+#    #+#             */
/*   Updated: 2019/08/26 21:02:21 by aemilien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

# include <stdlib.h>
# include <stdio.h>

# include "utils.h"
# include "libmatrix.h"

# define BUFF_SIZE 1024

# define LOADER_LINE_BUFF_SIZE 512

/*
** A line can be splitted into tokens
** The following structure represents a token
** - cursor is a ptr on a pecific char of the line string
** - size is the size of the token in terms of printable char
*/

typedef struct	s_token {
	char		*cursor;
	size_t		size;
}				t_token;

int				token_to_int(const t_token *tokens, size_t index);
bool			check_tokens_number(const t_token *tokens, size_t size);
bool			is_printable(char c);
t_token			*split_into_tokens(const char *line, const char *delimiters);
float			n_atof(const char *str, size_t size);
int				n_atoi(const char *str, size_t size);
void			print_token(const t_token *tokens);
#endif
