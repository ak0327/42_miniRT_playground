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
		  range_check.c \
		  bit_operator.c \


OBJ_DIR	= objs
OBJ		= $(SRCS:%.c=%.o)
OBJS	= $(addprefix $(OBJ_DIR)/, $(OBJ))

all		: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(CFLASG) $^ -o $@

$(OBJ_DIR)/%.o	: %.c
	@mkdir -p $$(dirname $(OBJ_DIR))
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all

print	:
	make re PRINT=1

.PHONY	: all clean fclean re print

