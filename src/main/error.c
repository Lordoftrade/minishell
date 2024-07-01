/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:43:45 by lelichik          #+#    #+#             */
/*   Updated: 2024/06/28 18:41:27 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder.h"

void free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->value);
		free(tmp);
	}
}

// Очистка памяти для структуры t_lexer
void free_lexer(t_lexer *lexer)
{
	t_lexer *tmp;
	
	if (lexer == NULL)
		return;
	while (lexer != NULL)
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp->content);
		free(tmp);
	}
}

// Очистка памяти для основной структуры t_minishell
void free_minishell(t_minishell *shell)
{
	if (shell == NULL)
		return;
	if(shell->env)
		free_env(shell->env);
	if(shell->lexer)
		free_lexer(shell->lexer);
	if(shell->commands)
		free_command_list(shell->commands);
	free(shell);
}

void	ft_error(char *error_message)
{
	write(2, "Error\n", 6);
	ft_putstr_fd(error_message, 2);
	exit(1);
}

void free_command(t_command *command)
{
	int	i;

	i = 0;
	if(command)
	{
		// if (command->type)
		// 	free(command->type);
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

void free_command_list(t_command *command_list)
{
	t_command *tmp;
	
	while (command_list)
	{
		tmp = command_list;
		command_list = command_list->next;
		free_command(tmp);
	}
}

void	free_env_list(t_env *env)
{
	t_env *cur;

	while (env != NULL)
	{
		cur = env;
		env = env->next;
		free(cur->value);
		free(cur);
	}
}

