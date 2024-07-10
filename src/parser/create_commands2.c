/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:21:50 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/10 19:01:52 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_here_document(t_command *new_cmd, t_lexer **current)
{
	if (strcmp((*current)->content, "<<") == 0)
	{
		*current = (*current)->next;
		if (*current && (*current)->type == STRING)
		{
			new_cmd->D_LT = 1;
			new_cmd->delimiter = ft_strdup((*current)->content);
			*current = (*current)->next;
		}
	}
}

void	handle_input_redirection(t_command *new_cmd, t_lexer **current)
{
	*current = (*current)->next;
	if (*current && (*current)->type == STRING)
	{
		new_cmd->LT = 1;
		new_cmd->input = ft_strdup((*current)->content);
		*current = (*current)->next;
	}
}

void	handle_output_redirection(t_command *new_cmd, t_lexer **current)
{
	*current = (*current)->next;
	if (*current && (*current)->type == STRING)
	{
		new_cmd->GT = 1;
		new_cmd->output = ft_strdup((*current)->content);
		*current = (*current)->next;
	}
}

void	handle_append_redirection(t_command *new_cmd, t_lexer **current)
{
	*current = (*current)->next;
	if (*current && (*current)->type == STRING)
	{
		new_cmd->D_GT = 1;
		new_cmd->output = ft_strdup((*current)->content);
		*current = (*current)->next;
	}
}

void	handle_redirections(t_command *new_cmd, t_lexer **current)
{
	if (strcmp((*current)->content, "<") == 0)
		handle_input_redirection(new_cmd, current);
	else if (strcmp((*current)->content, ">") == 0)
		handle_output_redirection(new_cmd, current);
	else if (strcmp((*current)->content, ">>") == 0) 
		handle_append_redirection(new_cmd, current);
}

void	handle_redirections_and_heredoc(t_command *new_cmd, t_lexer **current)
{
	while (*current && (*current)->type != STRING)
	{
		if (strcmp((*current)->content, "|") == 0) //написать функцию если нет в либе
		{
			*current = (*current)->next;
			break;
		}
		handle_redirections(new_cmd, current);
		handle_here_document(new_cmd, current);
	}
}

void	copy_over(t_lexer *current, t_lexer *new)
{
	t_lexer *tmp;

	tmp = current->next;
	current->content = ft_strdup(new->content);
	current->next = new->next;
	free(new->content);
	free(new);
	free(tmp->content);
	free(tmp);
}

