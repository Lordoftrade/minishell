/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:46:38 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:56:55 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int	ch = 124;
	printf("%d\n", ft_isdigit(ch));
	printf("%d", isdigit(ch));
	return(0);
}*/