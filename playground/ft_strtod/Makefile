NAME	= a.out

CC		= cc
#CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
#CFLAGS	= -g -fsanitize=address
#CFLAGS	= -Wall -Wextra -Werror
CFLAGS	=


ifdef PRINT
	CFLAGS += -D PRINT
endif

SRCS	= test.c \
		  ft_strtod.c \
		  parse.c \
		  convert.c \
		  range_check.c


OBJS	= $(SRCS:%.c=%.o)


all		: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(CFLASG) $^ -o $@

#$(OBJS)	: $(SRCS)
#	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

print	:
	make re PRINT=1

.PHONY	: all clean fclean re print

