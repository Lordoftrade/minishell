/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 23:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/12 22:06:59 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_execve(char *path_bin, char **args, char **env)
{
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
