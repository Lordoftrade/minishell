/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/02 23:21:00 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path_com(const char *bin, const char *com)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(bin, "/");
	path = ft_strjoin(tmp, com);
	ft_free_chr(tmp);
	return (path);
}

int	execute_implemented(char **args, t_minishell *shell)
{
	int	result;

	result = 0;
	if (ft_strcmp(args[0], "cd") == 0)
		result = shell_cd(args, shell);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = shell_pwd();
	if (ft_strcmp(args[0], "echo") == 0)
		result = shell_echo(args);
	if (ft_strcmp(args[0], "export") == 0)
		result = shell_export(args, shell);
	if (ft_strcmp(args[0], "unset") == 0)
		result = shell_unset(args, shell);
	if (ft_strcmp(args[0], "env") == 0)
		result = shell_env(shell->env);
	if (ft_strcmp(args[0], "exit") == 0)
	{
		shell_exit(args);
		result = 1;
	}
	g_error = result;
	return (result);
}

int	ft_execve_file_and_path(char **args, t_minishell *shell)
{
	char	*path_bin;
	int		result;

	if (access(args[0], F_OK) != 0)
	{
		ft_error_put(127, args[0], "", "No such file or directory\n");
		return (127);
	}
	if (access(args[0], X_OK) == 0)
	{
		if (is_directory(args[0]))
		{
			ft_error_put(126, args[0], "", "is a directory\n");
			return (g_error);
		}
		path_bin = ft_strdup(args[0]);
		if (path_bin == NULL)
		{
			perror("malloc");
			return (FAILURE);
		}
		result = start_execve(path_bin, args, shell->env);
		free(path_bin);
		return (result);
	}
	else
	{
		ft_error_put(126, args[0], "", "Permission denied\n");
		return (g_error);
	}
}

int	is_command_implemented(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	execute_command(t_minishell *shell)
{
	int	result;

	//g_error = 0;
	if (shell->commands->argv[0] && is_command_implemented(shell->commands->argv[0]))
		result = execute_implemented(shell->commands->argv, shell);
	else
	{
		if (shell->commands->argv[0][0] == '/' || shell->commands->argv[0][0] == '.'
			|| ft_strchr(shell->commands->argv[0], '/') != NULL)
			return (ft_execve_file_and_path(shell->commands->argv, shell));
		result = execute_bin(shell->commands->argv, shell);
	}
	return (result);
}
