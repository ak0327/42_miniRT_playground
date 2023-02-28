CC				= cc
CFLAGS			= -Wall -Wextra -Werror -MMD -MP

ifdef WITH_TEST
	CFLAGS 		+= -D LEAKS
endif

NAME			= miniRT

SRC_DIR			= ./srcs
SRC				=
DEPS			= $(SRC:%.c=%:d) $(LIB:%.c=%:d)

OBJ_DIR			= ./objs
OBJ				= $(SRC:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR)/, $(OBJ))

INCLUDE_DIR		= ./includes
IFLAGS			= $(addprefix -I, $(INCLUDE_DIR))

LIB_DIR			= ./libs
LIB				= libft

MLX_DIR			= ./minilibx-linux
X11_DIR			= /usr/X11

INCLUDES		= -I $(INCLUDE_DIR) -I $(MLX_DIR) -I $(X11_DIR)/include
LIBS_DIR 		= -L $(LIB_DIR) -L $(MLX_DIR) -L $(X11_DIR)/lib -L $(X11_DIR)
LIBS 			= -lft -lmlx -lX11 -lXext

# OS Check
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	LIBS_DIR 	+= -L /usr/X11R6/lib
	LIBS 		+= -lmlx_Darwin -framework OpenGL -framework AppKit
else
	LIBS 		+= -lmlx_Linux
endif

$(NAME)			: %(OBJS)
	@make -C $(LIB_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $^ $(LIB_DIR) $(LIBS) -o $@

$(OBJ_DIR)/%.o 	: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(INCLUDE) -c $< -o $@

all				: $(NAME)

clean			:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)
	@make clean -C $(MLX_DIR)

fclean			: clean
	rm -rf $(NAME)
	@make fclean -C $(LIB_DIR)
	@make fclean -C $(MLX_DIR)

re				: fclean all

test			:
	make all WITH_TEST=1

norm			:
	@norminette --version
	norminette $(SRC_DIR) $(INCLUDE_DIR) $(LIB_DIR)

.PHONY			: all clean fclean re

