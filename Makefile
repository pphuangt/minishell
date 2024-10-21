NAME = minishell
INCLUDES = includes
LIB = lib
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = $(LIB)/libft
HEADERS = -I./$(INCLUDES) -I./$(LIBFT)
LIBS = $(LIBFT)/libft.a -lreadline
SRCS = $(addprefix srcs/, main.c \
	   $(addprefix signals/, signals.c) \
	   $(addprefix environ/, environ.c environ_utils.c) \
	   $(addprefix parse/, constructure.c parse.c parse_utils.c gettoken.c) \
	   $(addprefix expansion/, expansion.c expansion_utils.c expand_env_var.c expand_env_var_utils.c expand_exit_status.c strip_quote.c symbols.c heredoc.c) \
	   $(addprefix execute/, execute.c runbuiltins.c runcmd.c runcmd_utils.c redirect.c file_descriptor.c set_pathname.c) \
	   $(addprefix builtins/, ft_echo.c ft_cd.c ft_pwd.c ft_unset.c ft_env.c ft_exit.c \
		$(addprefix export/, ft_export.c ft_export_output.c ft_export_utils.c)) \
	   $(addprefix common/, err.c err_message.c freecmd.c free_environ.c shell.c))
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) bonus -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(HEADERS)

%.o : %.c
	$(CC) $(CFLAGS) -c $(HEADERS) -o $@ $<

clean :
	$(MAKE) clean -C $(LIBFT)
	rm -rf $(OBJS)

fclean :
	$(MAKE) fclean -C $(LIBFT)
	rm -rf $(OBJS)
	rm -rf $(NAME)

re : fclean all
