/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:07:12 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:58:50 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int c, size_t len)
{
	size_t			i;
	unsigned char	*b;

	i = 0;
	b = (unsigned char *)buf;
	while (i < len)
	{
		b[i] = (unsigned char)c;
		i++;
	}
	return (buf);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	c[100];
// 	int		i = 48;
// 	printf("%s\n", ft_memset(c, 48, 42));
// 	printf("%s", memset(c, i, 4));
// 	return(0);
// }