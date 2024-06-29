/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:35:14 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 20:00:21 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		while (haystack[i + j] == needle[j] && needle[j] != '\0' && j + i < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
		j = 0;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	//char	a[30] = "aaabcabcd";
// 	//char	b[10] = "aabc";
// 	char * empty = (char*)"";

// 	printf("%s\n", ft_strnstr(empty, "", 0));
// 	//printf("%s", strnstr(empty, "", 0));
// }