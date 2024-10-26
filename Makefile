NAME = minishell
INCLUDES = includes
LIB = lib
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = $(LIB)/libft
HEADERS = -I./$(INCLUDES) -I./$(LIBFT) -I/usr/local/opt/readline/include
LIBS = $(LIBFT)/libft.a -L/usr/local/opt/readline/lib -lreadline
SRCS = $(addprefix srcs/, main.c)
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

.PHONY: all clean fclean re
