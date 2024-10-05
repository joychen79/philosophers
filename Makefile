NAME			=	philo
HEADERS			=	philosophers.h
SRCS			=	philosophers.c \
					utils.c \
					routine.c \
					threads.c \
					time.c 
					
OBJS			=	$(SRCS:.c=.o)
CC				=	gcc
AR				=	ar rcs
CFLAGS			=	-Wall -Wextra -Werror -g -fsanitize=address
RM				=	rm -rf

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY:	clean fclean re