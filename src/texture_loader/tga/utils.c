#include "scop.h"

uint32_t	uint32_color(
    uint8_t alpha,
    uint8_t red,
    uint8_t green,
    uint8_t blue)
{
	uint32_t    color;

	color = alpha;
	color = (color * 256) + red;
	color = (color * 256) + green;
	color = (color * 256) + blue;
	return (color);
}