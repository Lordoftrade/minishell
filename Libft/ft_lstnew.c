/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:55:54 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:57:49 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*first;

	first = (t_list *)malloc(sizeof(t_list));
	if (!first)
		return (0);
	first->content = content;
	first->next = NULL;
	return (first);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*content = "Hello 42";
// 	t_list *new_node = ft_lstnew(content);
// 	printf("content = %s", (char *)new_node->content);
// 	free(new_node);
// }