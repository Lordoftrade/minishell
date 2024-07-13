/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:43:45 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/12 21:34:31 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_lexer(t_lexer *lexer)
{
	t_lexer *tmp;

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

void free_minishell(t_minishell *shell)
{
	if (shell == NULL) // добавить еще под что Миша выделяет память
		return ;
	if (shell->env)
		free_env_list(shell->env);
	if (shell->lexer)
		free_lexer(shell->lexer);
	if (shell->commands)
		free_command_list(shell->commands);
	if (shell->export)
		free_export(shell->export);
	free(shell);
}

void	errors_memory(t_minishell *shell, int error_code)
{
	free_minishell(shell);
	printf("Error: Unable to allocate memory.\n");
	exit(error_code);
}
void	ft_error_redir(char *arg, char *mesg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(mesg, 2);
}

void	ft_error_put(int code, char *com, char *arg, char *mesg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(mesg, 2);
	g_error = code;
}

void	ft_error(int error_code, char *errmsg)
{
	g_error = error_code;
	write(2, "minishell: ", 12);
	ft_putstr_fd(errmsg, 2);
	// free(errmsg);
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
	t_command *tmp;

	while (command_list)
	{
		tmp = command_list;
		command_list = command_list->next;
		free_command(tmp);
	}
}

