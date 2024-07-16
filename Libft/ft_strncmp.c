/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:33:56 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 20:00:14 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

//#include <stdio.h>
//#include <string.h>

//int	main(void)
//{
//	//char	*str1 = "aaA";
//	//char	*str2 = "aaB";
//
//	printf("%d\n", ft_strncmp("test\200", "test\0", 6));
//	printf("%d", strncmp("test\200", "test\0", 6));
//}