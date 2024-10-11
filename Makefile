NAME = minishell
INCLUDES = includes
LIB = lib
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = $(LIB)/libft
HEADERS = -I./$(INCLUDES) -I./$(LIBFT) -I/usr/local/opt/readline/include
LIBS = $(LIBFT)/libft.a -L/usr/local/opt/readline/lib -lreadline
SRCS = $(addprefix srcs/, main.c \
	   $(addprefix signals/, signals.c) \
	   $(addprefix environ/, environ.c) \
	   $(addprefix parse/, constructure.c parse.c parse_utils.c heredoc.c gettoken.c) \
	   $(addprefix expansion/, expansion.c expansion_utils.c expansion_utils2.c expand_env_var.c expand_env_var_utils.c expand_exit_status.c strip_quote.c) \
	   $(addprefix execute/, execute.c) \
	   $(addprefix common/, free.c err.c err_message.c utils.c))
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT)
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
