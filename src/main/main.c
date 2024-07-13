/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:10:52 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 02:27:44 by lelichik         ###   ########.fr       */
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

void print_commands(t_minishell *shell)
{
    t_command *cmd = shell->commands;
    while (cmd)
    {
        // printf("Command: %d\n", cmd->type);
        printf("Arguments:\n");
        char **arg = cmd->argv;
        while (*arg)
        {
            printf("  %s\n", *arg);
            arg++;
        }
        if (cmd->input)
            printf("Input redirection: %s\n", cmd->input);
        if (cmd->output)
            printf("Output redirection: %s\n", cmd->output);
		if (cmd->delimiter)
            printf("Delimetr: %s\n", cmd->delimiter);
		if (cmd->LT)
			printf("LT: %d\n", cmd->LT);
		if (cmd->GT)
			printf("GT: %d\n", cmd->GT);
		if (cmd->D_LT)
			printf("D_LT: %d\n", cmd->D_LT);
		if (cmd->D_GT)
			printf("D_GT: %d\n", cmd->D_GT);
        printf("\n");

        cmd = cmd->next;
    }
}

void	minishell(t_minishell *shell)
{
	int	res;

	res = 0;
	if(check_redirect(shell->commands) && shell->len == 1)
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
		{
			printf("exit\n");
			//очистка всего  clean_up
			exit(g_error);
		}
		add_history(line);
		// line = ft_readline();
		ft_lexer(line, &shell);
		parser(&(shell->lexer), &shell);
	// t_lexer *tem = shell->lexer;
    // while (tem) {
    //     printf("Token type new: %d, content new: %s\n", tem->type, tem->content);
    //     tem = tem->next;
    // }
		if(check_sintax_redir(shell->lexer))
		{
			g_error = 1;
		}
		else
		{
			create_commands_from_tokens(shell);
			// print_commands(shell);
			minishell(shell);
		}
	// 	// // print_commands(shell);
		free_command_list(shell->commands);
		// system("leaks minishell");
	}
}


int	main(int argc, char **argv, char **env)
{
	t_minishell *shell;

	(void)argv;
	if(argc > 1)
		exit (1);
	rl_catch_signals = 0;
	shell = (t_minishell *)malloc(sizeof(t_minishell));
		if(!shell)
			exit (1);
	init_minishell(shell, env);
	display_prompt(shell);
	free_env_list(shell->env);
	free_export(shell->export);
	return (SUCCESS);
}
