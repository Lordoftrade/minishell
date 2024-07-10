NAME = minishell

SRCDIR = src
OBJDIR = obj

SRCS = $(addprefix $(SRCDIR)/env/, env_tools_2.c env_tools.c env_tools3.c) \
		$(addprefix $(SRCDIR)/lexer/, token.c token_group.c token_group_2.c token_utils.c) \
		$(addprefix $(SRCDIR)/main/, check.c error.c main.c free.c level_shell.c signals.c) \
		$(addprefix $(SRCDIR)/parser/, connection.c create_commands.c parser.c create_commands2.c parser_utils.c) \
		$(addprefix $(SRCDIR)/redirect/, redirect.c redirect_utils.c) \
		$(addprefix $(SRCDIR)/commands/, shell_cd.c shell_echo.c shell_env.c shell_exit.c shell_export.c shell_export_tools.c shell_pwd.c shell_unset.c shell_export_tools2.c) \
		$(addprefix $(SRCDIR)/execution/, execution.c exec_bin.c exec_fork.c) \
		$(addprefix $(SRCDIR)/pipe/, pipe.c)

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

HEADER = $(SRCDIR)/include/minishell.h
LIBFT = ./Libft
LIBFTA = $(LIBFT)/libft.a
LIBS = -L$(LIBFT) -lft ./read_lib/lib/libreadline.a -lncurses
INCLUDES = -I$(SRCDIR)/include -I$(LIBFT) -I./read_lib/include

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIBFTA)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFTA):
	@$(MAKE) -C $(LIBFT)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all


.PHONY: all clean fclean re