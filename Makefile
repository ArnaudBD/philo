NAME =	philo


SRCS = 		main.c\
			init.c\
			utils.c\
			kill.c

OBJS =	$(SRCS:.c=.o)

CC =	gcc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread #-fsanitize=address

RM = 	rm -f

INCS	=	includes/

HEADERS	=	-I $(INCS)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

all : $(NAME)

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all


.PHONY :
		all clean fclean re
