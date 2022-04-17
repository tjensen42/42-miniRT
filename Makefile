# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 09:02:38 by tjensen           #+#    #+#              #
#    Updated: 2022/04/17 14:07:54 by tjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	PROJECT SPECIFIC														   #
# **************************************************************************** #

NAME			:= miniRT

CC				:= cc
CFLAGS			:= -O3 -Wall -Wextra -Werror -pthread

SRCS			:= miniRT.c
SRCS_GLOBAL		:= vec3.c color.c object.c
SRCS_SCENE		:= scene.c scene_check.c scene_parser.c scene_open.c scene_setup.c
SRCS_SCENE_PROC	:= scene_process_amb.c scene_process_bg.c scene_process_cam.c scene_process_cylinder.c \
				   scene_process_light.c scene_process_plane.c scene_process_ppm.c scene_process_img.c scene_process_sampling.c \
				   scene_process_sphere.c scene_process_utils.c
SRCS_SCENE_PRINT:= scene_print.c scene_print_amb.c scene_print_bg.c scene_print_cam.c scene_print_cylinder.c scene_print_plane.c \
				   scene_print_img.c scene_print_sampling.c scene_print_sphere.c scene_print_utils.c

SRCS			+= $(addprefix global/, $(SRCS_GLOBAL)) \
				   $(addprefix scene/, $(SRCS_SCENE)) \
				   $(addprefix scene/scene_process/, $(SRCS_SCENE_PROC)) \
				   $(addprefix scene/scene_print/, $(SRCS_SCENE_PRINT))

IDIR			:= inc
SDIR			:= src
ODIR			:= obj
OBJS			:= $(addprefix $(ODIR)/, $(SRCS:.c=.o))

LIBDIRS			:= lib/libft lib/libmlx
LDLIBS			:= $(addprefix -L./, $(LIBDIRS)) -lm -lft \
				   -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit
INCLUDES		:= -I$(IDIR) \
			   	   -I./lib/libft/inc \
			   	   -I./lib/libmlx

# **************************************************************************** #
#	SYSTEM SPECIFIC SETTINGS							   					   #
# **************************************************************************** #

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

$(NAME): lib/libmlx/libmlx42.a lib/libft/libft.a $(ODIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

$(ODIR)/%.o: $(SDIR)/%.c $(IDIR)/*
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

all: $(NAME)

clean:
	make -C lib/libft clean
	make -C lib/libmlx clean
	$(RM) -r $(ODIR)
	$(RM) -r *.dSYM $(SDIR)/*.dSYM

fclean:
	make -C lib/libft fclean
	make -C lib/libmlx fclean
	$(RM) -r $(ODIR)
	$(RM) -r *.dSYM $(SDIR)/*.dSYM
	$(RM) $(NAME)

lib/libft/libft.a:
	make -C lib/libft/

lib/libmlx/libmlx42.a:
	make -C lib/libmlx/

re: fclean all

debug: CFLAGS += -O0 -DDEBUG -g
debug: all
