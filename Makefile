NAME = minishell

SRCDIR = src
OBJDIR = obj

SRCS = $(addprefix $(SRCDIR)/env/, env_tools_2.c env_tools.c env_tools3.c) \
		$(addprefix $(SRCDIR)/commands/, shell_cd.c shell_echo.c shell_env.c shell_exit.c shell_export.c shell_export_tools.c shell_pwd.c shell_unset.c shell_export_tools2.c) \
		$(addprefix $(SRCDIR)/main/, free.c level_shell.c  main_comm.c signals.c) \
		$(addprefix $(SRCDIR)/execution/, execution.c exec_bin.c exec_fork.c) \

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))


HEADER = $(SRCDIR)/include/minishell.h
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
