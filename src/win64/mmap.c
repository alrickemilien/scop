#include "scop.h"

#ifdef _MSC_VER

void *mmap(char *address, size_t length, int file, int flags, int fildes, off_t offset)
{
    void *map;
    HANDLE handle;

	(void)flags;
	(void)fildes;

    map = (void *) NULL;
    handle = INVALID_HANDLE_VALUE;

    handle = CreateFileMapping((HANDLE) _get_osfhandle(file), 0, PAGE_READONLY, 0, length, 0);
    if (!handle)
           return (NULL);
    map = (void *) MapViewOfFile(handle, FILE_MAP_READ, 0, 0, length);
    CloseHandle(handle);

    if (map == (void *) NULL)
        return(NULL);
    return((void *) ((char *) map + offset));
}

/**
 * https://github.com/icefox/netflixrecommenderframework/blob/b0315e13edab5f3095007cb018bb40686eb2e431/src/winmmap.h
 */

// static void	*test(const char *path)
// {
// 	int			fd;
// 	struct stat	stats;
// 	int length;
// 	void *content;
//
// 	if ((fd = open(path, O_RDONLY)) == -1)
// 	{
// 		fprintf(stderr, "%s: open - File does not exist or permission denied\n", path);
// 		return (NULL);
// 	}
//
// 	if (fstat(fd, &stats) == -1)
// 		return (NULL);
//
// 	if (stats.st_size <= 0)
// 		return (NULL);
//
// 	length = stats.st_size;
//
// 	if (NULL == (content = mmap(NULL, length, fd, 0)))
// 	{
// 		fprintf(stderr, "mmap - File does not exist or permission denied\n");
// 	}
//
// 	close(fd);
// 	return (content);
// }

#endif
