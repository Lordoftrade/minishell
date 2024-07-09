/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:44 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:44 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//убрать когда добавлю либфт
static int	nbr_len(int nbr)
{
	int	len;

	len = (nbr <= 0);
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static char	*ft_from_nbr_to_str(char *str, int n, int len)
{
	long long	nbr;

	nbr = n;
	if (n < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	str[len] = '\0';
	len--;
	while (nbr)
	{
		str[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

char	*itoa(int n)
{
	char	*str;
	int		len;

	len = nbr_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[len--] = '\0';
		str[len] = '0';
	}
	else
		ft_from_nbr_to_str(str, n, len);
	return (str);
}
// //убрать когда добавлю либфт по сюда

void	change_lvl(t_env *env)
{
	char	env_name[PATH_SIZE];
	char	*shlvl_value;
	int		level;
	size_t	var_name_len;
	char	*new_lvl;

	var_name_len = 0;
	shlvl_value = get_env_value("SHLVL", env);
	level = atoi(shlvl_value) + 1; // изменить на либфт
	ft_free_chr(shlvl_value);
	while (env)
	{
		getenv_name(env_name, env->value);
		var_name_len = strlen(env_name);
		if (strncmp("SHLVL", env_name, var_name_len) == 0) // SHLVL && SHLVLA
		{
			ft_free_chr(env->value);
			new_lvl = itoa(level);
			env->value = ft_strjoin("SHLVL=", new_lvl);  // либфт не не забыть
			ft_free_chr(new_lvl);
			return ;
		}
		env = env->next;
	}
}
