/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:39:32 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/14 23:24:38 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_and_execute_child(t_command *curr, int prev_fd,
	int fd[2], t_minishell *shell)
{
	int	pid;
	int	heredoc_fd;

	pid = fork();
	if (pid == 0)
	{
		setup_child_pipes(prev_fd, fd[0], fd[1], curr);
		if (curr->d_lt)
		{
			heredoc_fd = open(curr->heredoc, O_RDONLY);
			if (heredoc_fd < 0)
				ft_error(1, "Failed to open heredoc file");
			unlink(curr->heredoc);
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		execute_child_command(curr, shell);
		exit(0);
	}
	return (pid);
}

void	process_heredocs(t_command *commands)
{
	t_command	*curr;
	int			j;

	curr = commands;
	j = 0;
	while (curr)
	{
		if (curr->d_lt)
		{
			if (redir_heredoc_pipe(curr, j))
			{
				ft_error(258, "Heredoc error\n");
			}
			j++;
		}
		curr = curr->next;
	}
}

int	execute_commands(t_command *commands, t_minishell *shell)
{
	t_command	*curr;
	int			fd[2];
	int			prev_fd;
	int			last_pid;

	curr = commands;
	prev_fd = -1;
	last_pid = -1;
	while (curr)
	{
		if (curr->next)
		{
			if (create_pipe(fd) == -1)
			{
				free_minishell(shell);
				exit(EXIT_FAILURE);
			}
		}
		last_pid = create_and_execute_child(curr, prev_fd, fd, shell);
		handle_parent_process(&prev_fd, fd[0], fd[1], &curr);
	}
	return (last_pid);
}

void	wait_for_children(int last_pid, int len)
{
	int	i;
	int	pid;
	int	status;

	i = 0;
	while (i < len)
	{
		pid = wait(&status);
		if (pid == last_pid)
			g_error = WEXITSTATUS(status);
		i++;
	}
}

void	execute_pipeline_one_by_one(t_minishell *shell)
{
	int	last_pid;

	process_heredocs(shell->commands);
	last_pid = execute_commands(shell->commands, shell);
	wait_for_children(last_pid, shell->len);
}
