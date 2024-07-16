/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:56:23 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:56:27 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sing;
	int	res;

	sing = 1;
	i = 0;
	res = 0;
	while ((str[i] == ' ' ) || (str[i] == '\n') || (str[i] == '\t') \
		|| (str[i] == '\f') || (str[i] == '\r') || (str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sing = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 +(str[i] - '0');
		i++;
	}
	return (res * sing);
}

//#include <stdio.h>
//#include <stdlib.h>
//
//int	main(void)
//{
//	char	*str = "+548";
//
//	printf("%d\n", ft_atoi(str));
//	printf("%d", atoi(str));
//	return(0);
//}