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

void	change_lvl(t_env *env)
{
	char	env_name[PATH_SIZE];
	char	*shlvl_value;
	int		level;
	size_t	var_name_len;
	char	*new_lvl;

	var_name_len = 0;
	shlvl_value = get_env_value("SHLVL", env);
	level = ft_atoi(shlvl_value) + 1;
	ft_free_chr(shlvl_value);
	while (env)
	{
		getenv_name(env_name, env->value);
		var_name_len = ft_strlen(env_name);
		if (ft_strncmp("SHLVL", env_name, var_name_len) == 0)
		{
			ft_free_chr(env->value);
			new_lvl = ft_itoa(level);
			env->value = ft_strjoin("SHLVL=", new_lvl);
			ft_free_chr(new_lvl);
			return ;
		}
		env = env->next;
	}
}

int	check_syntax_redir_part2(t_lexer *lexer)
{
	t_lexer	*current;

	current = lexer;
	while (current && current->next)
		current = current->next;
	if (current && (current->type == GT || current->type == D_GT
			|| current->type == LT || current->type == D_LT))
	{
		ft_error(258, "syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
