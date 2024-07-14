/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:10:52 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 22:27:45 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

void	init_minishell(t_minishell *shell, char **env_in)
{
	int		i;
	t_env	*tmp;

	if (!shell || !env_in)
		return ;
	i = 0;
	g_error = 0;
	shell->env = NULL;
	shell->export = NULL;
	while (env_in[i] != NULL)
	{
		add_env_node(&(shell->env), env_in[i]);
		i++;
	}
	ft_unsetenv("OLDPWD", &shell->env);
	change_lvl(shell->env);
	tmp = shell->env;
	while (tmp)
	{
		add_to_export(&(shell->export), tmp->value);
		tmp = tmp->next;
	}
	add_to_export(&(shell->export), "OLDPWD");
}

void	init_data(t_minishell *shell)
{
	shell->lexer = NULL;
	shell->commands = NULL;
	shell->exit_code = 0;
	shell->len = 0;
	shell->stdin = dup(STDIN_FILENO);
	shell->stdout = dup(STDOUT_FILENO);
	shell->f_success = 1;
}

void	minishell(t_minishell *shell)
{
	int	res;

	res = 0;
	if (check_redirect(shell->commands) && shell->len == 1)
	{
		res = handling_redir(&shell);
		g_error = res;
		if (check_argv(shell->commands) && list_size(shell->commands) && !res)
			g_error = execute_command(shell);
		dup2(shell->stdout, STDOUT_FILENO);
		dup2(shell->stdin, STDIN_FILENO);
	}
	else if (check_pipe(shell))
	{
		execute_pipeline_one_by_one(shell);
		dup2(shell->stdout, STDOUT_FILENO);
		dup2(shell->stdin, STDIN_FILENO);
	}
	else if (check_argv(shell->commands) && !check_pipe(shell) && !res)
		g_error = execute_command(shell);
}

void	display_prompt(t_minishell *shell)
{
	char	*line;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		init_data(shell);
		line = readline(RESET GREEN "minishell" RED "$ " RESET);
		if (line == NULL)
			ft_contral_d(shell);
		add_history(line);
		ft_lexer(line, &shell);
		parser(&(shell->lexer), &shell);
		if (check_sintax_redir(shell->lexer) || check_syntax_redir_part2(shell->lexer))
			free_sintax_error(1, shell->lexer);
		else
		{
			create_commands_from_tokens(shell);
			minishell(shell);
		}
		free_command_list(shell->commands);
		//system("leaks minishell");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*shell;

	(void)argv;
	if (argc > 1)
		exit (1);
	rl_catch_signals = 0;
	shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!shell)
		exit(1);
	init_minishell(shell, env);
	display_prompt(shell);
	free_env_list(shell->env);
	free_export(shell->export);
	return (SUCCESS);
}
