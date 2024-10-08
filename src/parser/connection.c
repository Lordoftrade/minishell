/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:32:36 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/14 20:05:08 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concatenate_nodes(t_lexer *current, t_minishell **shell)
{
	t_lexer	*new;
	int		i;

	i = 0;
	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		errors_memory((*shell), 1);
	new->type = STRING;
	new->content = ft_mystrjoin(current->content, current->next->content);
	if (current == (*shell)->lexer)
		i = 1;
	if (current->next->next)
		new->next = current->next->next;
	else
		new->next = NULL;
	copy_over(current, new);
	if (i)
		(*shell)->lexer = current;
}

void	connect_tokens(t_lexer **token, t_minishell **shell)
{
	t_lexer	*current;

	current = *token;
	while (current != NULL && current->next != NULL)
	{
		if ((current->type == STRING || current->type == S_QUOTE)
			&& (current->next->type == STRING
				|| current->next->type == S_QUOTE))
			concatenate_nodes(current, shell);
		else
			current = current->next;
	}
}

void	change_current(t_lexer **current, t_lexer **previous)
{
	*previous = *current;
	*current = (*current)->next;
}

void	free_empty_token(t_lexer **token, t_minishell **shell)
{
	t_lexer	*current;
	t_lexer	*previous;
	t_lexer	*tmp;

	current = *token;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strlen(current->content) == 0)
		{
			tmp = current;
			current = current->next;
			if (previous)
				previous->next = current;
			else
				(*shell)->lexer = current;
			free(tmp->content);
			free(tmp);
		}
		else
			change_current(&current, &previous);
	}
}

void	free_space(t_lexer **token, t_minishell **shell)
{
	t_lexer	*current;
	t_lexer	*previous;
	t_lexer	*tmp;

	current = *token;
	previous = NULL;
	while (current != NULL)
	{
		if (current->type == MY_SPACE)
		{
			tmp = current;
			current = current->next;
			if (previous)
				previous->next = current;
			else
				(*shell)->lexer = current;
			free(tmp->content);
			free(tmp);
		}
		else
			change_current(&current, &previous);
	}
}
