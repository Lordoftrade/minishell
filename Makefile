NAME = minishell

SRCDIR = src
OBJDIR = obj

SRCS = $(addprefix $(SRCDIR)/env/, env.c) \
		$(addprefix $(SRCDIR)/lexer/, token.c token_group.c token_group_2.c token_utils.c) \
		$(addprefix $(SRCDIR)/main/, check.c error.c main.c) \
		$(addprefix $(SRCDIR)/parser/, connection.c create_commands.c parser.c) \
		$(addprefix $(SRCDIR)/redirect/, redirect.c redirect_utils.c) \

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))


HEADER = $(SRCDIR)/include/heder.h
LIBFT = ./Libft
LIBFTA = $(LIBFT)/libft.a
LIBS = -L$(LIBFT) -lft -lreadline
INCLUDES = -I$(SRCDIR)/include -I$(LIBFT)


CC = cc
CFLAGS = -Wall -Wextra -Werror -g
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
SRCS = $(addprefix $(SRCDIR)/env/, env_tools_2.c env_tools.c env_tools3.c) \
		$(addprefix $(SRCDIR)/commands/, shell_cd.c shell_echo.c shell_env.c shell_exit.c shell_export.c shell_export_tools.c shell_pwd.c shell_unset.c) \
		$(addprefix $(SRCDIR)/main/, free.c level_shell.c  main_comm.c) \
		$(addprefix $(SRCDIR)/execution/, execution.c) \