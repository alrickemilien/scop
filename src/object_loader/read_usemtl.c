#include "object_loader.h"

int				read_usemtl(t_mesh *data, const t_token *tokens)
{
	t_usemtl	usemtl;

	memset(&usemtl, 0, sizeof(t_usemtl));
	usemtl.mtl = strndup(tokens[0].cursor, tokens[0].size);
	usemtl.start = data->faces_count - 1;
	if (data->usemtl != NULL)
		((t_usemtl*)data->usemtl->content)->end = usemtl.start;
	ft_lstadd(&data->usemtl, ft_lstnew(&usemtl, sizeof(t_usemtl)));
	return (0);
}
