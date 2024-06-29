/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:29:12 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:57:22 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// #include <stdio.h>

// void	print(void	*content)
// {
// 	printf("%s\n", (char *)content);
// }

// int	main(void)
// {
// 	t_list *node1;
// 	t_list *node2;

// 	node1 = (t_list *)malloc(sizeof(t_list));
// 	node2 = (t_list *)malloc(sizeof(t_list));

// 	node1 = ft_lstnew("NODE 1");
// 	node2 = ft_lstnew("NODE 2");
// 	node1->next = node2;
// 	node2->next = NULL;
// 	ft_lstiter(node1, print);
// 	return(0);
// }