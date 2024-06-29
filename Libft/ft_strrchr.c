/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:46:39 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 20:00:26 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	res = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char) c)
		{
			res = (char *)(s + i);
			return (res);
		}
		i--;
	}
	return (res);
}

//#include <stdio.h>
//#include <string.h>
//
//int	main(void)
//{
//	char	c[] = "bonjourno";
//	int		i = 'o';
//	printf("%s\n", ft_strrchr(c, i));
//	printf("%s", strrchr(c, i));
//	return(0);
//}
