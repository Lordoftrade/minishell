/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:16:10 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 23:29:06 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_argc(t_lexer *tokens)
{
	int	argc;

	argc = 0;
	while (tokens)
	{
		argc++;
		tokens = tokens->next;
	}
	return (argc);
}

void	copy_over(t_lexer *current, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = current->next;
	current->content = ft_strdup(new->content);
	current->next = new->next;
	free(new->content);
	free(new);
	free(tmp->content);
	free(tmp);
}
