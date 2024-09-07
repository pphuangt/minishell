NAME = minishell
INCLUDES = includes
LIB = lib
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = $(LIB)/libft
HEADERS = -I./$(INCLUDES) -I./$(LIBFT)
LIBS = $(LIBFT)/libft.a -lreadline
SRCS = $(addprefix srcs/, main.c parse.c err.c token.c constructure.c utils.c expandation.c expandation_utils.c)
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
