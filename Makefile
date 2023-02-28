NAME	= miniRT

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP



SRC_DIR	= ./srcs
SRC		=

OBJ_DIR = ./objs
OBJ		=
OBJS	= $(addprefix $(OBJ_DIR)/, $(OBJ))

INCLUDES_DIR = ./includes
IFLAGS		 = $(addprefix -I, $(INCLUDES_DIR))

DEPS	= $()


$(NAME)	:


all		:


clean	:


fclean	:


re		:


test	:


.PHONY	: all clean fclean re

