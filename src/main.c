/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:10:52 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/01 12:29:11 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *shell, char **env)
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
        printf("Command: %d\n", cmd->type);
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
            printf("Output redirection: %s (append: %d)\n", cmd->output, cmd->append);
		if (cmd->delimiter)
            printf("Delimetr: %s\n", cmd->delimiter);
        printf("\n");

        cmd = cmd->next;
    }
}

void	minishell(t_minishell *shell)
{
	int	res;

	res = 0;
	if(check_redirect(shell->commands))
	{
		res = handling_redir(shell);
		execute_command(shell);
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
	init_env(shell, env);
	while(1)
	{
		init_data(shell);
		line = ft_readline();
		ft_lexer(line, &shell);
		parser(&(shell->lexer), &shell);
	t_lexer *tem = shell->lexer;
    while (tem) {
        printf("Token type new: %d, content new: %s\n", tem->type, tem->content);
        tem = tem->next;
    }
		create_commands_from_tokens(&shell);
		print_commands(shell);
		minishell(shell);
		print_commands(shell);
		free_lexer(shell->lexer);
		free_command_list(shell->commands);
		system("leaks minishell");
	}
	// free_env_list(shell.env);
	// free_export(shell.export);
}
