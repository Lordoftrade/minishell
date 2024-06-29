/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:04:11 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:56:34 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buf;
	unsigned int	i;

	buf = s;
	i = 0;
	while (i < n)
	{
		buf[i] = 0;
		i++;
	}
}

/*#include <stdio.h>
#include <strings.h>

int	main(void)
{
	char	c[] = "Hello";
	ft_bzero(c, 2);
	printf("%s", c);
	bzero(c, 2);
	printf("%s", c);
	return(0);
}*/