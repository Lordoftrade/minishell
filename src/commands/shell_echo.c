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

int	is_n_flag(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	shell_echo(char **args)
{
	int	i;
	int	n_line;

	i = 1;
	n_line = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		n_line = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "$?") == 0)
			printf("%d", g_error);
		else
			printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_line)
		printf("\n");
	return (SUCCESS);
}

/*либо
while (args[i] != NULL)
{
	printf("%s", args[i]);
	if (args[i + 1] != NULL)
		printf(" ");
	i++;
}*/
