/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:33:30 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 23:14:30 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection_token(enum e_token_type type,
		t_command *command, t_lexer **tokens)
{
	t_lexer	*current_token;
	t_lexer	*next_token;
	char	*string;

	current_token = *tokens;
	next_token = current_token->next;
	if (next_token == NULL)
	{
		printf("Syntax error: expected filename after redirection token\n");
		return ;
	}
	string = next_token->content;
	handle_redirection_token_helper(type, string, command);
	*tokens = next_token->next;
	free(current_token->content);
	free(current_token);
	free(next_token);
}

void	handle_redirection_tokens(t_lexer **tokens, t_command *command)
{
	while (*tokens)
	{
		if ((*tokens)->type != STRING)
			handle_redirection_token((*tokens)->type, command, tokens);
		else
			tokens = &(*tokens)->next;
	}
}

void	turn_single_quotes_into_strings(t_lexer *tokens)
{
	while (tokens)
	{
		if (tokens->type == S_QUOTE)
			tokens->type = STRING;
		tokens = tokens->next;
	}
}

void	handle_argv_tokens_sanity_check(t_lexer *tokens)
{
	while (tokens)
	{
		if (tokens->type != STRING)
		{
			ft_error(1, "Tokens have not been processed");
			return ;
		}
		tokens = tokens->next;
	}
}
