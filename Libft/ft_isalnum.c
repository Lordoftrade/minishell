/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:53:49 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:56:44 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int	i = 127;
	printf("%d\n", ft_isalnum(i));
	printf("%d", isalnum(i));
	return(0);
}*/