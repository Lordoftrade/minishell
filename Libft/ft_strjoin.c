/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:07:50 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:59:38 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	conct(const char *s1, const char *s2, char *str_dest, t_for_norm *s)
{
	while (s1[(s->i)] != '\0')
	{
		str_dest[(s->i)] = s1[(s->i)];
		(s->i)++;
	}
	while (s2[(s->j)] != '\0')
	{
		str_dest[(s->i) + (s->j)] = s2[(s->j)];
		(s->j)++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str_dest;
	t_for_norm	s;

	s.i = 0;
	s.j = 0;
	if (!s1 || !s2)
		return (NULL);
	s.len_s1 = ft_strlen(s1);
	s.len_s2 = ft_strlen(s2);
	str_dest = (char *)malloc((s.len_s1 + s.len_s2 + 1) * sizeof(char));
	if (!str_dest)
		return (NULL);
	conct(s1, s2, str_dest, &s);
	str_dest[s.i + s.j] = '\0';
	return (str_dest);
}

// #include <stdio.h>

// int main(void)
// {
// 	char	s1[] = "hello ";
// 	char	s2[] = "ооо";
// 	printf("%s\n", ft_strjoin(s1, s2));
// 	 	return(0);
// }