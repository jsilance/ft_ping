#include "ft_ping.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	ptr = NULL;
	while (lst)
	{
		ptr = lst;
		lst = lst->next;
	}
	return (ptr);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (alst && *alst)
		ft_lstlast(*alst)->next = new;
	else if (alst)
		*alst = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*tmp;

	if (!lst || !*lst || !del)
		return ;
	tmp = NULL;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		ft_lstdelone(ptr, (*del));
		ptr = tmp;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
