/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:22:18 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 20:00:35 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	size_dest;
	size_t	i;
	size_t	size_s;

	i = 0;
	if (!s)
		return (NULL);
	size_s = ft_strlen(s);
	if (start >= size_s)
		return (ft_calloc(1, sizeof(char)));
	size_dest = ft_strlen(&s[start]);
	if (len < size_dest)
		size_dest = len;
	dest = (char *)malloc((size_dest + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < size_dest && s[start + i] != '\0')
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s", ft_substr("test", 400, 20));
// 	return(0);
// }