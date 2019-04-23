#include "libmatrix.h"

static const t_pmatrix_format_map g_pmatrix_format_function[] = {
  { "d", &libmatrix_itoa },
  { "ld", &libmatrix_ltoa },
  { "f", &libmatrix_ftoa },
  #ifdef __gl_h_
  { "glf", &libmatrix_glftoa },
  { "gld", &libmatrix_glitoa },
  #endif
};

static inline bool is_flag(char c)
{
  if (strchr(".0#+", c) == NULL)
    return (false);
  return (true);
}

static int apply_identifier(char *format, t_pmatrix_format_value *options)
{
  int i;

  i = 0;
  while (i * sizeof(t_pmatrix_format_map) < sizeof(g_pmatrix_format_function))
	{
    if (!libmatrixutil_memcmp(
			g_pmatrix_format_function[i].key,
			format,
			sizeof(char) * libmatrixutil_strlen(g_pmatrix_format_function[i].key)))
    {
      options->identifier = g_pmatrix_format_function[i];
      return (libmatrixutil_strlen(g_pmatrix_format_function[i].key));
    }

    i++;
  }

  return (0);
}

static int apply_flag(char *format, t_pmatrix_format_value *options)
{
  int i;

  i = 0;
  while (*format && is_flag(*format))
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

static int get_string_value_according_to_format(t_pmatrix_format_value *options, char *buffer, void *value)
{
  return options->identifier.func(value, buffer);
}

/*
** Print a single value of the matrix with the format given in parameter
** return the size of the buffer
*/

static int pvalue(const char *format, char **whole_buffer, void *value)
{
  char                    *buffer;
  char                    *cursor_of_format;
  int                     ret;
  t_pmatrix_format_value  options;
  char                    value_str[42];

  buffer = NULL;
  ret = 0;
  while (*format)
  {
    cursor_of_format = libmatrixutil_strchr(format, '%');


    if (cursor_of_format == NULL)
    {
      // Minus 1 to not take the % character
      libmatrixutil_append_and_release_memory(&buffer,
        libmatrixutil_strdup(format));

        ret += libmatrixutil_strlen(format);

        return (ret);
    }

    if (*cursor_of_format == '%'
      && *(cursor_of_format + 1) != '%'
      && *(cursor_of_format + 1) != 0)
    {
      cursor_of_format++;

      cursor_of_format += apply_flag(cursor_of_format, &options);

      cursor_of_format += apply_identifier(cursor_of_format, &options);

			ret += get_string_value_according_to_format(&options, value_str, value);

			value_str[ret] = ' ';
			ret++;

      libmatrixutil_append_and_release_memory_static(&buffer, value_str);

      format = cursor_of_format;
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

int pmatrix(char *format, t_matrix *matrix)
{
  size_t    i;
  int       ret;
  char      *buffer;

  i = 0;
  ret = 0;
  buffer = NULL;
  while (i < matrix->lines * matrix->columns)
  {
      ret += pvalue(format, &buffer, &matrix->value[i]);

			if ((i + 1) % matrix->columns == 0) {
				libmatrixutil_append_and_release_memory_static(&buffer, "\n");
				ret++;
			}

      i++;
  }

  if (write(1, buffer, ret) == -1) {
    ret = -1;
  }

  free(buffer);

  return (ret);
}
