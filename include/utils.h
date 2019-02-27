#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <string.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			ft_lstreverse(t_list **lst);
void			*lst_data_at(t_list *list, size_t n);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *node);
size_t			ft_lstlen(t_list *lst);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

#endif
