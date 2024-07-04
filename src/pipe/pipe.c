/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:39:32 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/04 23:33:51 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_redirect_pipe(t_command *curr)
{
	if (curr && (curr->GT || curr->LT || curr->D_GT))
		if(execute_redirects(&curr) == 0)
			return(1);
	return(0);
	// else if (curr && curr->D_LT)
	// 	redir_heredoc(&curr);
}

void	handle_parent_process(int *prev_fd, int fd[2], t_command **curr)
{
	// waitpid(pid, &(shell->exit_code), 0);
	// shell->exit_code = WEXITSTATUS(shell->exit_code);
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = fd[0];
	if ((*curr)->next)
		close(fd[1]);
	*curr = (*curr)->next;
}

void	setup_child_pipes(int prev_fd, int fd[2], t_command *curr)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (curr->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

int	execute_command_for_pipe(t_command *curr, t_minishell *shell)
{

	if (curr->argv[0] && is_command_implemented(curr->argv[0]))
		execute_implemented(curr->argv, shell); // что вернуть должно
	else
		execute_bin(curr->argv, shell);
	return (0);
}

int	create_and_execute_child(t_command *curr, int prev_fd, int fd[2], t_minishell *shell)
{
	int pid;
	pid = fork();
	
	if (pid == 0)
	{
		setup_child_pipes(prev_fd, fd, curr);
		if (check_redirect(curr))
		{
			execute_redirect_pipe(curr);
		}
		execute_command_for_pipe(curr, shell); //добавить проверку что команда выполнилась
		exit(0);
	}
	return (pid);
}


int	create_pipe(int fd[2])
{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			return -1;
		}
	return (0);
}

void execute_pipeline_one_by_one(t_minishell *shell)
{
	t_command	*curr;
	int			fd[2];
	int			prev_fd;
	// int			pid;
	int			i;

	i = 0;
	curr = shell->commands;
	prev_fd = -1;
	while (curr)
	{
		// if (check_redirect(curr))
		// {
		// 	res = execute_redirect_pipe(curr);
		// 	printf("%d\n", res);
		// }
		if(curr->next)
		{
			if (create_pipe(fd) == -1)
				exit(EXIT_FAILURE); //подумать как должно выходить 
		}
		create_and_execute_child(curr, prev_fd, fd, shell);
		handle_parent_process(&prev_fd, fd, &curr);
	}
	while(i < shell->len)
	{
		wait(&(shell->exit_code));
		shell->exit_code = WEXITSTATUS(shell->exit_code);
		i++;
	}
}

int	check_pipe(t_minishell *shell)
{
	if(shell->len > 1)
		return(1);
	return(0);
}