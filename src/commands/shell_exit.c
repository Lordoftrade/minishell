/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:00 by mgreshne         ###   ########.fr       */
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

int	check_long(const char *str, t_minishell *shell)
{
	int	overflow;

	if (str[0] == '-')
		overflow = check_long_min(str);
	else
		overflow = check_long_max(str, shell);
	return (overflow);
}

long	exit_atol(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_is_num(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	do_exit(long value, t_minishell *shell)
{
	free_minishell(shell);
	//system("leaks minishell");
	exit((int)((unsigned char)value % 256));
}

void	shell_exit(char **args, t_minishell *shell)
{
	printf("exit\n");
	if (!args[1])
		do_exit(g_error, shell);
	if (args[2])
	{
		if (ft_is_num(args[1]))
		{
			ft_error_put(1, args[0], "", "too many arguments\n");
			return ;
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			do_exit(2, shell);
		}
	}
	if (!ft_is_num(args[1]))
	{
		ft_error_put(1, args[0], args[1], ": numeric argument required\n");
		do_exit(255, shell);
	}
	check_long(args[1], shell);
	do_exit(exit_atol(args[1]), shell);
}
