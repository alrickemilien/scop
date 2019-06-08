#include "utils.h"

/*
** Return index of node if list node's content fits
** into provided function
** or -1 if no found
*/

size_t  ft_lstindex(t_list *root,
                    const void *provided_content,
                    bool (*f)(const void *node_content, const void *provided_content))
{
    size_t i;

    i = 0;
    while (root)
    {
        if (f(root->content, provided_content))
            return (i);

        i++;
        root = root->next;
    }

    return ((size_t)-1);
}