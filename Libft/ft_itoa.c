/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:20:47 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:57:02 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_negative(int *negative, long *nbr)
{
	if ((*nbr) < 0)
	{
		(*negative) = 1;
		(*nbr) *= -1;
	}
}

static void	convert(long nbr, int i, char *new)
{
	while (nbr > 0)
	{
		new[i] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i--;
	}
}

static int	ft_digitcount(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		negative;
	long	nbr;
	int		dc;
	int		i;
	char	*new;

	negative = 0;
	nbr = (long)n;
	check_negative(&negative, &nbr);
	dc = ft_digitcount(nbr);
	new = (char *)malloc(sizeof(char) * (dc + negative + 1));
	if (!new)
		return (NULL);
	i = dc + negative - 1;
	if (nbr == 0)
		new[0] = '0';
	convert(nbr, i, new);
	if (negative != 0)
		new[0] = '-';
	new[dc + negative] = '\0';
	return (new);
}

// #include <stdio.h>

// int main()
// {
//     int num = 0;
//     char *str = ft_itoa(num);

//     if (str != NULL) {
//         printf("Integer: %d\nString: %s\n", num, str);
//         free(str);
//     } else {
//         printf("Ошибка выделения памяти.\n");
//     }

//     return 0;
// }