/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:26 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/14 15:49:31 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_long_max(const char *str, t_minishell *shell)
{
	unsigned long long	result;
	int					i;

	result = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		if (result > 9223372036854775807)
		{
			printf("minishell: exit: %s: numeric argument required\n", str);
			do_exit(2, shell);
		}
	}
	return (0);
}

int	check_long_min(const char *str)
{
	char	*line;
	char	*tmp;
	int		cmp_result;
	size_t	len;

	line = ft_strdup(str);
	if (!line)
		return (1);
	tmp = line;
	if (*tmp == '-')
		tmp++;
	while (*tmp == '0')
		tmp++;
	len = ft_strlen(tmp);
	if (len > 19)
		return (free(line), 1);
	cmp_result = ft_strncmp(tmp, "9223372036854775808", 19);
	free(line);
	if (cmp_result > 0)
		return (1);
	else
		return (0);
}
