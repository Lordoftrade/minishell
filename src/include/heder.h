/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:05:55 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/01 13:01:01 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEDER_H
# define HEDER_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h> // PATH_MAX
# include <stddef.h>

# define FAILURE 1
# define SUCCESS 0
# define PATH_SIZE 1024
# define BUFF_SIZE 2048

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

enum token_type
{
	STRING, //строка
	PIPE,
	S_QUOTE, //'
	D_QUOTE, //"
	GT, //> 
	LT, //< 
	D_GT, //>> 
	D_LT, // << 
	SPACE,
	DOLLAR,
};

typedef struct s_token_lexer
{
	enum token_type	type;
	char			*content;
	struct s_token_lexer	*next;
}					t_lexer;

typedef struct s_command
{
    enum				token_type	type;    // Тип команды или оператора (например, "command", ">", ">>", "|")
    char                **argv;   // Аргументы команды
    char                *input;   // Файл для перенаправления ввода (если есть)
    char                *output;  // Файл для перенаправления вывода (если есть)
	char				*delimiter;
    int                 append;   // Флаг для добавления в файл (если 1 - добавление, если 0 - перезапись)
    struct s_command    *next;    // Указатель на следующую команду в пайпе
} t_command;

typedef struct s_minishell
{
	int				stdin;
	int				stdout;
	t_env			*env;
	t_lexer			*lexer;
	t_command		*commands;
}					t_minishell;



int		len_env_value(const char *env);
char	*env_value(char *value);
char	*getenv_name(char *dest, const char *src);
char	*get_env_value(char *arg, t_env *env);
void	free_env_list(t_env *env);
t_env *create_env_node(char *value);
void	add_env_node(t_env **env, char *value);
void	init_env(t_minishell *shell, char **env);

void free_env(t_env *env);
void free_lexer(t_lexer *lexer);
void free_minishell(t_minishell *shell);
void	ft_error(char *error_message);

char	*ft_readline(void);
void	to_array(char *str, t_minishell *info);
void	ft_lexer(char *line, t_minishell **shell);
void	init_minishell(t_minishell *shell);
int	ft_strlen(const char *str);
int	check_pipe(char *str);
int	check_quote(char *str);
int	check_symbol(char *str);
t_lexer	*create_new_token(enum token_type type, char *content);
void	add_token_to_list(t_lexer **head, t_lexer *new_token);
char	*ft_strndup(const char *src, size_t n);
void	single_quote_token(char *str, int *i, t_minishell *shell);
void	to_list_lexer(char *str, t_minishell *shell);
void	double_quote_token(char *str, int *i, t_minishell *shell);
void	space_token(char *str, int *i, t_minishell *shell);
void	pipe_token(char *str, int *i, t_minishell *shell);
void	dollar_token(char *str, int *i, t_minishell *shell);
void	gt_token(char *str, int *i, t_minishell *shell);
void	lt_token(char *str, int *i, t_minishell *shell);
void	string_token(char *str, int *i, t_minishell *shell);
void	symbol_dollar(t_lexer **tokens, t_minishell *info);
int		is_breaking_character(char	c);
void	parser(t_lexer **tokens, t_minishell **shell);
char	*open_dollar(char *str, int *i, t_minishell *shell);
void	symbol_d_quote(t_lexer **token, t_minishell *shell);
char	*ft_mystrjoin(char *s1, char const *s2);
void	process_other_chars(char *string, int *i, char **result);
void	process_dollar(char *string, int *i, t_minishell *shell, char **result);
void	connect_tokens(t_lexer **token, t_minishell **shell);
void	concatenate_nodes(t_lexer *current, t_minishell **shell);
void	copy_over(t_lexer *current, t_lexer *new);
void	change_current(t_lexer **current, t_lexer **previous);
void	free_empty_token(t_lexer **token, t_minishell **shell);
void	free_space(t_lexer **token, t_minishell **shell);
void	create_commands_from_tokens(t_minishell **shell);
void add_command_to_list(t_command **cmd_list, t_command **last_cmd, t_command *new_cmd);
void handle_redirections_and_here_document(t_command *new_cmd, t_lexer **current);
void fill_command_argv(t_command *cmd, t_lexer **current);
t_command *create_new_command();
void free_command(t_command *cmd);
void free_command_list(t_command *cmd_list);
int	check_redirect(t_command *command);
void	minishell(t_minishell **shell);
int	handling_redir(t_minishell **shell);
int	run_redirect(t_command **current);
int	do_redir(t_command **c);
int	execute_redirects(t_command **command);
int lt(t_command **command);
int	d_gt(t_command **command);
int	gt(t_command **command);
// void	start(t_command **s, t_command **c, t_command **prev, t_minishell **sh);
// void	previous(t_command **previous, t_command **command);
void	delete_redirect(t_command **command);

#endif