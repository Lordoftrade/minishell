/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 01:09:06 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/01 12:30:04 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
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
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>

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
	//t_token			*array;
	t_env			*env;
	t_lexer			*lexer;
	t_command		*commands;
	char			**export;
	char			*args[1024];
}					t_minishell;


void		change_lvl(t_env *env);

size_t		count_env(t_env *env);
void		add_env_node(t_env **env, char *value);
int			is_in_env(t_env *env, char *args);
int			is_in_env_array(char ***export, char *args);
char		*get_env_value(char *arg, t_env *env);
char		*env_value(char *value);
int			len_env_value(const char *env);
char		*getenv_name(char *dest, const char *src);
int			add_env(const char *value, t_env *env);
void		bubble_sort_env(char **env_array, size_t env_count);
int 		is_valid_identifier(const char *str);
int			ft_unsetenv(const char *name, t_env **env);
char		**env_list_to_array(t_env *env_list);


int			shell_cd(char **args, t_minishell *shell);
int			shell_pwd(void);
int			shell_echo(char **args);
int			shell_export(char **args, t_minishell *shell);
int			shell_unset(char **args, t_minishell *shell);
int			shell_env(t_env *env);
void		shell_exit(char **args);

int			execute_command(t_minishell *shell);

void		*ft_free_chr(void *ptr);
void		free_string_array(char **array);
void		free_export(char **export);
void		free_env_list(t_env *env);

void		add_to_export(char ***export, char *value);
char		*add_quotes_to_value(const char *name, const char *value);
int			count_elements(char **array);
void		copy_array(char **dest, char **src);

t_env *create_env_node(char *value);
void	init_minishell(t_minishell *shell, char **env);
void	init_data(t_minishell *shell);

void	free_env(t_env *env); // ?? наверное то же самое что и фри енв лист
void	free_lexer(t_lexer *lexer);
void	free_minishell(t_minishell *shell);
void	ft_error(char *error_message);

char	*ft_readline(void);
void	to_array(char *str, t_minishell *info);
void	ft_lexer(char *line, t_minishell **shell);
void	init_minishell(t_minishell *shell);
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
void	minishell(t_minishell *shell);
int	handling_redir(t_minishell *shell);
int	run_redirect(t_command **command, t_command **previous);
int	do_redir(t_command **c, t_command **p, t_command **s);
int	execute_redirects(t_command **command);
int lt(t_command **command);
int	d_gt(t_command **command);
int	gt(t_command **command);
void	start(t_command **s, t_command **c, t_command **prev, t_minishell **sh);
void	previous(t_command **previous, t_command **command);
void delete_redirect(t_command **cmd, t_command **head, t_command **prev);

#endif