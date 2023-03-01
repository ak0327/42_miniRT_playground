CC				= cc
CFLAGS			= -Wall -Wextra -Werror -MMD -MP

ifdef WITH_TEST
	CFLAGS 		+= -D LEAKS
endif

NAME			= miniRT

VPATH			= $(SRC_DIR) $(INCLUDE_DIR)

SRC_DIR			= ./srcs
SRC				= main.c

SRCS			= $(addprefix $(SRC_DIR)/, $(SRC))


OBJ_DIR			= ./objs
OBJ				= $(SRC:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR)/, $(OBJ))
DEPS			= $(OBJS:%.o=%:d)

INCLUDE_DIR		= ./includes
IFLAGS			= $(addprefix -I, $(INCLUDE_DIR))

LIBFT_DIR		= ./libs
LIBFT_NAME		= libft.a
LIBFT			= $(addprefix $(LIBFT_DIR)/, $(LIBFT_NAME))

MLX_DIR			= ./minilibx-linux
X11_DIR			= /usr/X11

INCLUDES		= -I $(INCLUDE_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR) -I $(X11_DIR)/include
LIBS_DIR 		= -L $(LIBFT_DIR) -L $(MLX_DIR) -L $(X11_DIR)/lib -L $(X11_DIR)
LIBS 			= $(LIBFT) -lmlx -lX11 -lXext

# OS Check
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	LIBS_DIR 	+= -L /usr/X11R6/lib
	LIBS 		+= -lmlx_Darwin -framework OpenGL -framework AppKit
else
	LIBS 		+= -lmlx_Linux
endif


$(NAME) : $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $^ $(LIBFT_DIR) $(LIBS) -o $@

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(INCLUDES) -c $< -o $@

all				: $(NAME)

clean			:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@#make clean -C $(MLX_DIR)

fclean			: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@#make fclean -C $(MLX_DIR)

re				: fclean all

bonus			:

test			:
	make all WITH_TEST=1

norm			:
	@norminette --version
	norminette $(SRC_DIR) $(INCLUDE_DIR) $(LIBFT_DIR)

.PHONY			: all clean fclean re test norm bonus

