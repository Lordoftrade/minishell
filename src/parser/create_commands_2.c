/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:21:50 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 23:23:14 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_output_redirection(enum e_token_type type,
		char *string, t_command *command)
{
	if (type == GT)
	{
		command->gt = 1;
		if (command->output)
			free(command->output);
		command->output = string;
	}
	else if (type == D_GT)
	{
		command->d_gt = 1;
		if (command->output)
			free(command->output);
		command->output = string;
	}
}

void	handle_input_redirection(enum e_token_type type,
		char *string, t_command *command)
{
	if (type == LT)
	{
		command->lt = 1;
		if (command->input)
			free(command->input);
		command->input = string;
	}
	else if (type == D_LT)
	{
		command->d_lt = 1;
		command->delimiter = string;
	}
}

void	handle_redirection_token_helper(enum e_token_type type,
		char *string, t_command *command)
{
	if (type == GT || type == D_GT)
	{
		handle_output_redirection(type, string, command);
	}
	else if (type == LT || type == D_LT)
	{
		handle_input_redirection(type, string, command);
	}
}

void	handle_argv_tokens(t_lexer **tokens, t_command *command)
{
	int		argc;
	int		i;
	t_lexer	*current_token;

	handle_argv_tokens_sanity_check(*tokens);
	argc = count_argc(*tokens);
	command->argv = malloc(sizeof(char *) * (argc + 1));
	command->argv[argc] = NULL;
	i = 0;
	while (*tokens)
	{
		current_token = *tokens;
		command->argv[i] = current_token->content;
		i++;
		*tokens = current_token->next;
		free(current_token);
	}
}
