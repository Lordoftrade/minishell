/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/13 17:00:00 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	run_execve(char *path_bin, char **args, char **env)
{
	if (is_directory(path_bin))
	{
		ft_error_put(126, args[0], "", "is a directory\n");
		free_string_array(env);
		exit(g_error);
	}
	if (execve(path_bin, args, env) == -1)
	{
		perror("execve");
		free_string_array(env);
		exit(EXIT_FAILURE);
	}
}

int	fork_and_execute(char *path_bin, char **args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, do_sigint_fork);
		run_execve(path_bin, args, env);
	}
	else if (pid < 0)
	{
		perror("fork");
		free_string_array(env);
		return (FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, handle_sigint);
		if (WIFEXITED(status))
			g_error = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_error = 128 + WTERMSIG(status);
	}
	return (g_error);
}
