/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:12:49 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 20:03:17 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*cpylst;
	t_list	*r;

	if (!lst || !f || !del)
		return (NULL);
	cpylst = lst;
	new = ft_lstnew((*f)(cpylst->content));
	if (!new)
		return (NULL);
	r = new;
	cpylst = cpylst->next;
	while (cpylst)
	{
		new->next = ft_lstnew((*f)(cpylst->content));
		if (!new->next)
		{
			ft_lstclear(&r, (*del));
			return (NULL);
		}
		new = new->next;
		cpylst = cpylst->next;
	}
	return (r);
}

// #include <stdio.h>

// void	del(void *d)
// {
// 	if(!d)
// 		free(d);
// }

// void	*print(void *lst)
// {
// 	char *str = (char *)lst;
// 	int	i = 0;

// 	while(str[i])
// 	{
// 		printf("%c", str[i]);
// 		i++;
// 	}
// 	return (str);
// }

// int	main(void)
// {
// 	t_list *node1;
// 	t_list *node2;
// 	t_list *node3;

// 	node1 = ft_lstnew("NODE1");
// 	node2 = ft_lstnew("NODE2");
// 	node3 = ft_lstnew("NODE3");
// 	node1->next = node2;
// 	node2->next = node3;
// 	node3->next = NULL;
// 	ft_lstmap(node1, print, del);
// 	return(0);
// }