/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:10:52 by opanikov          #+#    #+#             */
/*   Updated: 2024/06/28 18:49:18 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder.h"

void	init_env(t_minishell *shell, char **env)
{	
	int	i;

	i = 0;
	shell->env = NULL;

	while (env[i] != NULL)
		add_env_node(&(shell->env), env[i++]);
}

void	init_minishell(t_minishell *shell)
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
	}
	printf("%d\n", res);
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
	// t_env *temp = shell->env;
    // while (temp != NULL) {
    //     printf("%s\n", temp->value);
    //     temp = temp->next;
    // }
	while(1)
	{
		init_minishell(shell);
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
}
