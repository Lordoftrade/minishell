/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:02:03 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 23:26:14 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gt(t_command **command)
{
	int	fd;

	fd = open((*command)->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_error_redir((*command)->output, "No such file or directory\n");
		return (1);
	}
	if ((dup2(fd, STDOUT_FILENO)) < 0)
	{
		ft_error_redir("dup2", "Duplication error\n");
		close(fd);
		return (1);
	}
	return (0);
}

int	d_gt(t_command **command)
{
	int	fd;

	fd = open((*command)->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_error_redir((*command)->output, "No such file or directory\n");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_error_redir("dup2", "Duplication error\n");
		close(fd);
		return (1);
	}
	return (0);
}

int	lt(t_command **command)
{
	int	fd;

	fd = open((*command)->input, O_RDONLY);
	if (fd < 0)
	{
		ft_error_redir((*command)->input, "No such file or directory\n");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_error_redir("dup2", "Duplication error\n");
		close(fd);
		return (1);
	}
	return (0);
}

void	delete_redirect(t_command **command)
{
	if (command)
	{
		if ((*command)->input)
		{
			free((*command)->input);
			(*command)->input = NULL;
			if ((*command)->lt)
				(*command)->lt = 0;
		}
		if ((*command)->output)
		{
			free((*command)->output);
			(*command)->output = NULL;
			if ((*command)->gt)
				(*command)->gt = 0;
			else if ((*command)->d_gt)
				(*command)->d_gt = 0;
		}
	}
}

void	delete_heredoc(t_command *command)
{
	free(command->delimiter);
	free(command->heredoc);
	command->d_lt = 0;
	command->delimiter = NULL;
	command->heredoc = NULL;
}
