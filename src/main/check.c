/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:10:42 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/05 14:26:48 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (0);
	while(str[i])
	{
		if(str[i] && str[i] == '|' && str[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	check_quote(char *str)
{
	int	single_quote_open;
	int	double_quote_open;
	int	i;

	i = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	while(str[i])
	{
		if(str[i] == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		if(str[i] == '"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		i++;
	}
	return !single_quote_open && !double_quote_open;
}

int	check_symbol(char *str)
{
	int		i;
	int		j;

	i = 2;
	j = 2;

	i = check_pipe_syntax(str);
	j = check_quote(str);
	if(j == 0 || i == 0)
		return(1);
	return(0);
}
