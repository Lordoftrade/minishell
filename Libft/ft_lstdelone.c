/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:59:06 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:57:18 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	if (lst->content)
		del(lst->content);
	free(lst);
}

// #include <stdio.h>

// void	ft_free_content(void *content)
// {
// 	free(content);
// }

// int	main(void)
// {
// 	t_list *node1;

// 	node1 = (t_list *)malloc(sizeof(t_list));
// 	node1 = ft_lstnew("NODE 1");

// 	printf("node1 = %s\n", node1->content);

// 	ft_lstdelone(node1, ft_free_content);
// 	if(!node1)
// 		printf("node1 - delete");

// 	return(0);
// }