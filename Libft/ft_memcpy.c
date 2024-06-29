/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:50:26 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:58:42 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*str;
	unsigned char	*buf;

	if (!dst && !src)
		return (0);
	i = 0;
	str = (unsigned char *)dst;
	buf = (unsigned char *)src;
	while (i < n)
	{
		str[i] = buf[i];
		i++;
	}
	return (dst);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	src[10] = "123456";
	char	dst[10];

	ft_memcpy(dst, src, 4);
	printf("%s\n", dst);
	memcpy(dst, src, 4);
	printf("%s\n", dst);
	return(0);
}*/