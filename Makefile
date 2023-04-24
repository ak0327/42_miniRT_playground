#####################################################
# COMPILE
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -MMD -MP

ifdef WITH_TEST
	CFLAGS 		+= -D LEAKS
endif


#####################################################
# PROGRAM NAME
NAME			= miniRT


#####################################################
# SRC FILE
VPATH			= $(SRC_DIR) $(INCLUDE_DIR)

SRC_DIR			= srcs
SRC				= main.c \
				  screen.c \
				  color.c \
				  ft_strtod.c \
				  init_setting/camera.c \
				  init_setting/get_bump_normal.c \
				  init_setting/get_checker_texture.c \
				  init_setting/get_img_color.c \
				  init_setting/get_input.c \
				  init_setting/get_ppm.c \
				  init_setting/setting_for_ambient.c \
				  init_setting/setting_for_camera.c \
				  init_setting/setting_for_lights.c \
				  init_setting/setting_for_objects.c \
				  init_setting/get_texture_uv_map.c \
				  init_setting/parsing_config.c \
				  init_setting/validate_config.c \
				  vector_matrix/matrix.c \
				  vector_matrix/vector.c \
				  mlx_helper/mlx_keyhooks.c \
				  raytracing/raytrace.c \
				  raytracing/calc_ambient_reflection.c \
				  raytracing/calc_diffuse_reflection.c \
				  raytracing/calc_specular_reflection.c \
				  raytracing/calc_perfect_reflection.c \
				  raytracing/calc_refraction.c \
				  raytracing/intersection.c \




SRCS			= $(addprefix $(SRC_DIR)/, $(SRC))


#####################################################
# OBJECT FILE
OBJ_DIR			= objs
OBJ				= $(SRC:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR)/, $(OBJ))
DEPS			= $(SRCS:%.c=%:d)


#####################################################
# INCLUDE and LIBRARY FILE
INCLUDE_DIR		= includes

LIBFT_DIR		= libs
MLX_DIR			= minilibx-linux
X11_DIR			= /usr/X11
X11_INCLUDE		= /usr/X11/include
X11_LIB			= /usr/X11/lib

INCLUDE_DIRS	= $(INCLUDE_DIR) $(X11_INCLUDE)
LIBS_DIR 		= $(LIBFT_DIR) $(MLX_DIR) $(X11_DIR) $(X11_LIB)

INCLUDES		= $(addprefix -I, $(INCLUDE_DIRS))
LFLAGS			= $(addprefix -L, $(LIBS_DIR))
LIBS 			= -lft -lmlx -lX11 -lXext


#####################################################
# OS Check
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	LIBS_DIR 	+= /usr/X11R6/lib
	LIBS 		+= -lmlx_Darwin -framework OpenGL -framework AppKit
else
	LIBS 		+= -lmlx_Linux
endif


#####################################################
# RULES
all				: $(NAME)

$(NAME)			: $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(LFLAGS) $(LIBS) $^ -o $@

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(INCLUDES) -c $< -o $@


clean			:
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@#make clean -C $(MLX_DIR)

fclean			: clean
	rm -f $(NAME)
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

-include	$(DEPS)