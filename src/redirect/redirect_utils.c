/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:02:03 by opanikov          #+#    #+#             */
/*   Updated: 2024/06/29 16:33:50 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder.h"

int	gt(t_command **command)
{
	int	fd;

	fd = open((*command)->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		// printf("Failed to open output file\n");
		return(1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		// perror("Failed to redirect stdout");
		return(1);
	}
	return (0);
}

int	d_gt(t_command **command)
{
	int	fd;

	fd = open((*command)->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Failed to open output file");
		return(1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Failed to redirect stdout");
		close(fd);
		return(1);
	}
	return (0);
}
int lt(t_command **command)
{
	int	fd;

	fd = open((*command)->input, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open input file");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Failed to redirect stdin");
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
		}
		if ((*command)->output)
		{
			free((*command)->output);
			(*command)->output = NULL;
		}
	}
}

