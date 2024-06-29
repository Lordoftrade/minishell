/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:57:35 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:57:38 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// #include <stdio.h>

// void	ft_free_content(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list *node1;
// 	t_list *node2;
// 	t_list *node3;

// 	node1 = (t_list *)malloc(sizeof(t_list));
// 	node2 = (t_list *)malloc(sizeof(t_list));
// 	node3 = (t_list *)malloc(sizeof(t_list));
// 	node1->next = node2;
// 	node2->next = node3;
// 	node3->content = (char *)"cat";
// 	node3->next = NULL;
// 	printf("%s\n", (char *)ft_lstlast(node1)->content);	
// 	ft_lstclear(&node1, ft_free_content);
// 	return(0);
// }