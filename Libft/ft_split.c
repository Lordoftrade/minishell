/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:22:42 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:59:16 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	foo_for_norm(char c, const char **s, int *i)
{
	while (*(*s) && *(*s) != c)
		(*s)++;
	(*i)++;
}

static int	ft_wordcount(char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			j++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (j);
}

static char	*ft_putword(char const *str, char c)
{
	char	*w;
	int		i;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	w = (char *)malloc(sizeof(char) * (i + 1));
	if (!w)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		w[i] = str[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

static void	ft_free(char **new, int count)
{
	while (count > 0)
	{
		free(new[count - 1]);
		count--;
	}
	free(new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		i;
	int		word_count;

	if (!s)
		return (NULL);
	i = 0;
	word_count = ft_wordcount(s, c);
	new = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!new)
		return (NULL);
	while (i < word_count)
	{
		while (*s && *s == c)
			s++;
		new[i] = ft_putword(s, c);
		if (!new[i])
		{
			ft_free(new, i);
			return (NULL);
		}
		foo_for_norm(c, &s, &i);
	}
	new[i] = 0;
	return (new);
}

// #include <stdio.h>

// int main(void)
// {
// 	char const *str = "       ";
// 	char **result = ft_split(str, ' ');

// 	if (!result)
// 	{
// 		printf("Memory allocation failed\n");
// 		return 1;
// 		}

//     int i = 0;
//     while (result[i])
//     {
//         printf("Word %d: %s\n", i + 1, result[i]);
//         i++;
//     }

//     i = 0;
//     while (result[i])
//     {
//         free(result[i]);
//         i++;
//     }
//     free(result);

//     return 0;
// }