#include "scop.h"

static void	asscoiate_materials_to_mesh(
		t_mtllib *lib,
		const char *mtl,
		t_list *usemtl)
{
	t_list	*x;

	x = lib->materials_list;
	while (x)
	{
		printf("Test %s on %s\n",
				mtl,
				((t_mtl_data*)x->content)->label);
		if (memcmp(
					mtl,
					((t_mtl_data*)x->content)->label,
					strlen(mtl) * sizeof(char)) == 0)
		{
			printf("Associate %s with %s\n",
					mtl,
					((t_mtl_data*)x->content)->label);
			((t_usemtl*)usemtl->content)->material = x->content;
			break ;
		}
		x = x->next;
	}
}

static int	load_mtllib_error(const char *path)
{
	printf("Unable to load mtllib %s, exit.\n", path);
	return (-1);
}

int			load_mtllib(
		t_list *mtllib,
		t_list *usemtl)
{
	t_list	*x;

	printf("Load mtllibs ...\n");
	x = mtllib;
	while (x)
	{
		if (load_mtl_file(x->content) < 0)
			return (load_mtllib_error(((t_mtllib*)x->content)->path));
		x = x->next;
	}
	printf("Load mtllibs done, association process ...\n");
	while (usemtl)
	{
		x = mtllib;
		while (x)
		{
			asscoiate_materials_to_mesh(
					x->content,
					((t_usemtl*)usemtl->content)->mtl,
					usemtl);
			x = x->next;
		}
		usemtl = usemtl->next;
	}
	return (0);
}
