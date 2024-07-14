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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i  = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

void	copy_array(char **dest, char **src)
{
	int	i;

	if (!src)
		return ;
	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
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
	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	total_len = name_len + value_len + 4;
	quoted_value = (char *)malloc(total_len);
	if (!quoted_value)
		return (NULL);
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
	if (!str || !str[0] || str[0] == '=' || ft_isdigit(str[0]))
	{
		g_error = 1;
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			g_error = 1;
			return (0);
		}
		i++;
	}
	g_error = 0;
	return (1);
}
