/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:10:25 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 20:00:39 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

/*#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int	i = 'A';
	printf("%d\n", ft_tolower(i));
	printf("%d", tolower(i));
	return(0);
}*/