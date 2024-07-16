/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:42:45 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:59:47 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	size_src;

	i = 0;
	size_src = ft_strlen(src);
	if (size == 0)
		return (size_src);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (size_src);
}

//#include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	//char	*src = "Hello";
// 	char	dst[10];
// 	printf("%lu", ft_strlcpy(dst, "lorem ipsum dolor sit amet", 15));
// 	//ft_strlcpy(dst, src, 10);
// 	printf("%s \n", dst);
// 	return(0);
// }
