/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:02:03 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/12 18:28:54 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gt(t_command **command)
{
	int	fd;

	int i = 0;
	
	fd = open((*command)->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror((*command)->output);
		return (1);
	}
	if ((i = dup2(fd, STDOUT_FILENO)) < 0)
	{
		perror("dup2");
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
		perror((*command)->output);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	return (0);
}
int lt(t_command **command)
{
	int	fd;

	fd = open((*command)->input, O_RDONLY);
	if (fd < 0)
	{
		perror((*command)->input);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
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
			if((*command)->LT)
				(*command)->LT = 0;
		}
		if ((*command)->output)
		{
			free((*command)->output);
			(*command)->output = NULL;
			if((*command)->GT)
				(*command)->GT = 0;
			else if((*command)->D_GT)
				(*command)->D_GT = 0;
		}
	}
}

