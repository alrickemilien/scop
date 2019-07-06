#include "scop.h"

int		load_bitmap_file(
	t_bitmap *bmp,
	const char *pathname)
{
	FILE				*stream;
	size_t				size_read;

	printf("Start loading bitmap file %s\n", pathname);

	memset(bmp, 0, sizeof(t_bitmap));

	printf("a\n");

	bmp->path = strdup(pathname);

	printf("b\n");

	stream = fopen(pathname, "rb");

	printf("c\n");

	if (stream == NULL) {
		fprintf(stderr, "Unable to load file %s\n", pathname);
		return (-1);
	}

	printf("d\n");

	if ((size_read = fread(&bmp->header, 1, sizeof(t_bmp_header), stream)) != sizeof(t_bmp_header)) {
		fprintf(stderr, "%ld has been read\n", size_read);
		fclose(stream);
		return (-1);
	}

	printf("e\n");

	if (bmp->header.data_offset > bmp->header.data_offset) {
		fclose(stream);
		return (-1);
	}

	printf("f\n");

	if (fread(&bmp->dib_header, 1, sizeof(t_bmp_dib_header), stream) != sizeof(t_bmp_dib_header)) {
		fclose(stream);
		return (-1);
	}

	printf("g\n");

	bmp->width = (size_t)bmp->dib_header.image_width;
	bmp->height = (size_t)bmp->dib_header.image_height;

	fseek(stream, bmp->header.data_offset, SEEK_SET);

	printf("h\n");

	bmp->buffer = (char*)(uint8_t*)malloc(bmp->dib_header.image_size * sizeof(uint8_t));

	memset(bmp->buffer, 0, bmp->dib_header.image_size * sizeof(uint8_t));

	printf("i\n");

	printf("bmp->dib_header.image_size : %d\n", bmp->dib_header.image_size);

	size_read = fread(bmp->buffer, 1, bmp->dib_header.image_size, stream);

	printf("j\n");

	if (size_read != bmp->dib_header.image_size) {
		fprintf(stderr, "%ld has been read\n", size_read);
		fclose(stream);
		return (-1);
	}

	printf("k\n");

	fclose(stream);

	return (0);
}
