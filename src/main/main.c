/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:10:52 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/04 23:53:21 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *shell, char **env_in)
{
	int		i;
	t_env	*tmp;

	if (!shell || !env_in)
		return ;
	i = 0;
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
	shell->exit_code = 0;
	shell->stdin = dup(STDIN_FILENO);
	shell->stdout = dup(STDOUT_FILENO); 
}

char	*ft_readline(void)
{
	char	*line;

	line = readline("minishell$ ");
	if(line == NULL)
		exit(0);
	add_history(line);
	return(line);
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
	if(check_redirect(shell->commands) && shell->len == 1) // добавить проверку что нет пайпов 
	{
		res = handling_redir(&shell);
		if (check_argv(shell->commands) && list_size(shell->commands) && !res)
			execute_command(shell);
		dup2(shell->stdout, STDOUT_FILENO);
		dup2(shell->stdin, STDIN_FILENO);
	}
	else if (check_pipe(shell))
	{
		execute_pipeline_one_by_one(shell);
		dup2(shell->stdout, STDOUT_FILENO);
		dup2(shell->stdin, STDIN_FILENO);
	}
	else
		execute_command(shell);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell *shell;
	char	*line;

	(void)argv;
	if(argc > 1)
	{
		printf("ошибка в количестве аргументов");
		exit(1);
	}
	shell = (t_minishell *)malloc(sizeof(t_minishell));
		if(!shell)
		ft_error("Memory allocation error");
	init_minishell(shell, env);
	while(1)
	{
		init_data(shell);
		line = ft_readline();
		ft_lexer(line, &shell);
		parser(&(shell->lexer), &shell);
	// t_lexer *tem = shell->lexer;
    // while (tem) {
    //     printf("Token type new: %d, content new: %s\n", tem->type, tem->content);
    //     tem = tem->next;
    // }
		create_commands_from_tokens(&shell);
		// print_commands(shell);
		minishell(shell);
		// print_commands(shell);
		free_lexer(shell->lexer);
		free_command_list(shell->commands);
		// system("leaks minishell");
	}
	// free_env_list(shell.env);
	// free_export(shell.export);
}