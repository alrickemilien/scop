#include "libmatrix.h"

void	libmatrixutil_reverse_string(char *str, int n)
{
	int	start;
	int	end;

	start = 0;
	end = n - 1;
	while (start < end)
	{
		str[start] = str[start] ^ str[end];
		str[end] = str[end] ^ str[start];
		str[start] = str[start] ^ str[end];
		start++;
		end--;
	}
}

void	*libmatrixutil_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return ((void*)dest);
}

int		libmatrixutil_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void	libmatrixutil_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)s)[i] = 0;
		i++;
	}
}

void	*libmatrixutil_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void*)&(((unsigned char *)s)[i]));
		i++;
	}
	return (NULL);
}
