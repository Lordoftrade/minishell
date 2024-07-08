/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:19 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:19 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h> // getcwd
# include <limits.h> // PATH_MAX
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

# include <signal.h>


# include <string.h> // убрать!


# define FAILURE 1
# define SUCCESS 0
# define PATH_SIZE 1024
# define BUFF_SIZE 2048

# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define RESET "\033[0m"

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;


typedef struct	s_minishell
{
	//t_token			*array;
	t_env			*env;
	char			**export;
	char		*args[1024];
}				t_minishell;

extern int	g_error;

void		handle_sigint(int sig);
void		do_sigint_fork(int signal);

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
int			start_execve(char *path_bin, char **args, t_env *env_list);
char		*check_path_bin(char *bin, char *command);
char		*join_path_com(const char *bin, const char *com);
int			execute_bin(char **args, t_minishell *shell);
int			fork_and_execute(char *path_bin, char **args, char **env);
void		run_execve(char *path_bin, char **args, char **env);

void		*ft_free_chr(void *ptr);
void		free_string_array(char **array);
void		free_export(char **export);
void		free_env_list(t_env *env);

void		add_to_export(char ***export, char *value);
char		*add_quotes_to_value(const char *name, const char *value);
int			count_elements(char **array);
void		copy_array(char **dest, char **src);
int			update_export_var(char ***export, char *env_name, char *quoted_value, char *env_value_str);

void		do_exit(long value);


int			ft_strcmp(const char *s1, const char *s2);

// убрать
//char *ft_strjoin(char const *s1, char const *s2);
//int	ft_isalnum(int c);
//int	ft_isdigit(int c);

#endif
