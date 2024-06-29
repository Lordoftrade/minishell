/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:27 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:27 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_echo(char **args)
{
	int	i;
	int	n_line;

	i = 1;
	n_line = 1;
	if (args[i] && strncmp(args[i], "-n", 2) == 0)
	{
		n_line = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_line)
		printf("\n");
	return (SUCCESS);
}
