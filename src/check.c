/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:10:42 by opanikov          #+#    #+#             */
/*   Updated: 2024/06/14 15:18:32 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder.h"

int	check_pipe(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] && str[i] == '|' && str[i + 1] == '\0')
			return(0);
		i++;
	}
	return(1);
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

	i = check_pipe(str);
	j = check_quote(str);
	if(i == 0 || j == 0)
		return(0);
	return(1);
}
