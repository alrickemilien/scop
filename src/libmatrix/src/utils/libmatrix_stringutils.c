#include "libmatrix.h"

size_t  libmatrixutil_strlen(const char *s)
{
	size_t  i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char  *libmatrixutil_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	return ((char*)libmatrixutil_memchr((void*)s, c, libmatrixutil_strlen(s) + 1));
}

char  *libmatrixutil_strndup(const char *s, size_t	n)
{
  size_t  len;
  char    *new;

  len = n;
  new = (char *)malloc(len + 1);
  if (new == NULL)
    return (NULL);
  new[len] = 0;
  return ((char *)libmatrixutil_memcpy(new, s, len));
}

char *libmatrixutil_strdup(const char *s)
{
  size_t  len;
  char    *new;

  len = libmatrixutil_strlen(s);
  new = (char *)malloc(len + 1);
  if (new == NULL)
    return (NULL);
  new[len] = 0;
  return ((char *)libmatrixutil_memcpy(new, s, len));
}

void  libmatrixutil_append_and_release_memory(char **buffer, char *str)
{
  char    *new_buffer;
  size_t  buffer_len;
  size_t  str_len;

  if (*buffer == NULL)
  {
    *buffer = libmatrixutil_strdup(str);
    free(str);
    return ;
  }
  buffer_len = libmatrixutil_strlen(*buffer);
  str_len = libmatrixutil_strlen(str);
  new_buffer = (char*)malloc(sizeof(char) * (buffer_len + str_len + 1));
  if (!new_buffer)
    return ;
  libmatrixutil_memcpy(new_buffer, *buffer, buffer_len);
  libmatrixutil_memcpy(new_buffer + buffer_len, str, str_len);
  new_buffer[buffer_len + str_len] = 0;
  free(*buffer);
  free(str);
  *buffer = new_buffer;
}

/**
* Do not free the str parameter
* it is a static member that we must not touch
*/
void libmatrixutil_append_and_release_memory_static(char **buffer, const char *str)
{
  char    *new_buffer;
  size_t  buffer_len;
  size_t  str_len;

  if (*buffer == NULL)
  {
    *buffer = libmatrixutil_strdup(str);
    return ;
  }
  buffer_len = libmatrixutil_strlen(*buffer);
  str_len = libmatrixutil_strlen(str);
  new_buffer = (char*)malloc(sizeof(char) * (buffer_len + str_len + 1));
  if (!new_buffer)
    return ;
  libmatrixutil_memcpy(new_buffer, *buffer, buffer_len);
  libmatrixutil_memcpy(new_buffer + buffer_len, str, str_len);
  new_buffer[buffer_len + str_len] = 0;
  free(*buffer);
  *buffer = new_buffer;
}
