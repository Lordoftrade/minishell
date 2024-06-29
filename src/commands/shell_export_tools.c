/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:15:44 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/12 21:15:44 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//либфт
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	if (!dst || !src)
		return (0);

	src_len = strlen(src);
	if (size > 0)
	{
		for (i = 0; i < size - 1 && src[i] != '\0'; i++)
		{
			dst[i] = src[i];
		}
		dst[i] = '\0';
	}
	return (src_len);
}
/////

void	copy_array(char **dest, char **src)
{
	int	i;

	if (!src)
		return ;
	i = 0;
	while (src[i])
	{
		dest[i] = strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
}

int	count_elements(char **array)
{
	int	count;

	count = 0;
	while (array && array[count])
		count++;
	return (count);
}

char	*add_quotes_to_value(const char *name, const char *value)
{
	size_t	name_len;
	size_t	value_len;
	size_t	total_len;
	char	*quoted_value;

	if (!name || !value)
		return (NULL);
	name_len = strlen(name);
	value_len = strlen(value);
	total_len = name_len + value_len + 4;
	quoted_value = (char *)malloc(total_len);
	if (!quoted_value)
		return (NULL); // выход и статус - 1 ?
	ft_strlcpy(quoted_value, name, name_len + 1);
	quoted_value[name_len] = '=';
	quoted_value[name_len + 1] = '"';
	ft_strlcpy(quoted_value + name_len + 2, value, value_len + 1);
	quoted_value[total_len - 2] = '"';
	quoted_value[total_len - 1] = '\0';
	return (quoted_value);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0] || ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && (i != 0 && str[i] != '='))
			return (0);
		i++;
	}
	return (1);
}
