/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:21:06 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 21:27:18 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_sintax_error(int exit_code, t_lexer *lexer)
{
	free_lexer(lexer);
	g_error = exit_code;
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	if (lexer == NULL)
		return ;
	while (lexer != NULL)
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_minishell(t_minishell *shell)
{
	if (shell == NULL)
		return ;
	if (shell->env)
		free_env_list(shell->env);
	if (shell->lexer)
		free_lexer(shell->lexer);
	if (shell->commands)
		free_command_list(shell->commands);
	if (shell->export)
		free_string_array(shell->export);
	free(shell);
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	if (command)
	{
		if (command->argv)
		{
			while (command->argv[i])
				free(command->argv[i++]);
			free(command->argv);
		}
		if (command->input)
			free(command->input);
		if (command->output)
			free(command->output);
		if (command->delimiter)
			free(command->delimiter);
		free(command);
	}
}

void	free_command_list(t_command *command_list)
{
	t_command	*tmp;

	while (command_list)
	{
		tmp = command_list;
		command_list = command_list->next;
		free_command(tmp);
	}
}
