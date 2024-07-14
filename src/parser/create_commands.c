/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:58:06 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/14 23:22:39 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split_pipe	split_by_pipe(t_lexer *tokens)
{
	t_split_pipe	result;
	t_lexer			*next_token;

	result.command = 0;
	result.rest = 0;
	while (tokens && tokens->type != PIPE)
	{
		next_token = tokens->next;
		tokens->next = 0;
		add_token_to_list(&result.command, tokens);
		tokens = next_token;
	}
	if (tokens == NULL)
	{
		return (result);
	}
	next_token = tokens->next;
	free(tokens->content);
	free(tokens);
	result.rest = next_token;
	return (result);
}

t_command	*create_new_command(t_minishell *shell)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		errors_memory(shell, 1);
	new_cmd->argv = NULL;
	new_cmd->input = NULL;
	new_cmd->output = NULL;
	new_cmd->delimiter = NULL;
	new_cmd->heredoc = NULL;
	new_cmd->d_gt = 0;
	new_cmd->d_lt = 0;
	new_cmd->gt = 0;
	new_cmd->lt = 0;
	new_cmd->pipe = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_command	*tokens_into_command(t_lexer *tokens, t_minishell *shell)
{
	t_command	*command;

	command = create_new_command(shell);
	turn_single_quotes_into_strings(tokens);
	handle_redirection_tokens(&tokens, command);
	handle_argv_tokens(&tokens, command);
	return (command);
}

void	add_command_to_list(t_command **list, t_command *new_command)
{
	t_command	*current;

	if (*list == NULL)
	{
		*list = new_command;
	}
	else
	{
		current = *list;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_command;
	}
}

void	create_commands_from_tokens(t_minishell *shell)
{
	t_split_pipe	result;
	t_command		*command;

	command = NULL;
	shell->commands = NULL;
	while (shell->lexer)
	{
		result = split_by_pipe(shell->lexer);
		command = tokens_into_command(result.command, shell);
		add_command_to_list(&shell->commands, command);
		shell->lexer = result.rest;
	}
	shell->len = list_size(shell->commands);
}
