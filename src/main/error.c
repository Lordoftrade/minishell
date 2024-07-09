/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:43:45 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/05 14:55:46 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free_env_list(shell->env);
	if(shell->lexer)
		free_lexer(shell->lexer);
	if(shell->commands)
		free_command_list(shell->commands);
	if(shell->export)
		free_export(shell->export);
	free(shell);
}

void	errors_memory(t_minishell *shell, int error_code)
{
	free_minishell(shell);
	printf("Error: Unable to allocate memory.\n");
	exit(error_code);
}

void ft_error(t_minishell *shell, int error_code, char *errmsg)
{
	shell->exit_code = error_code;
	write(2, "minishell: ", 12);
	ft_putstr_fd(errmsg, 2);
	// free(errmsg);
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

