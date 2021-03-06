# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 09:02:38 by tjensen           #+#    #+#              #
#    Updated: 2022/06/09 22:50:13 by tjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	PROJECT SPECIFIC														   #
# **************************************************************************** #

NAME			:= miniRT

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -pthread -O3#-g -fsanitize=address

SRCS			:= main.c								\
				   mrt_color.c							\
				   mrt_light.c							\
				   mrt_obj.c							\
				   mrt_obj_checkerboard.c				\
				   mrt_obj_texture.c					\
				   mrt_obj_texture_utils.c				\
				   mrt_scene.c							\
				   mrt_scene_utils.c
SRCS_GRAPHIC	:= mrt_graphic.c						\
				   mrt_graphic_move.c					\
				   mrt_graphic_render.c					\
				   mrt_graphic_rotate.c
SRCS_MATH		:= mrt_math_color.c						\
				   mrt_math_vec3_1.c					\
				   mrt_math_vec3_2.c
SRCS_PARSE		:= mrt_parse_amb.c						\
				   mrt_parse_bg.c						\
				   mrt_parse_cam.c						\
				   mrt_parse_color.c					\
				   mrt_parse_light_disc.c				\
				   mrt_parse_light_rectangle.c			\
				   mrt_parse_light_sphere.c				\
				   mrt_parse_material.c					\
				   mrt_parse_obj_cuboid.c				\
				   mrt_parse_obj_cylinder.c				\
				   mrt_parse_obj_disc.c					\
				   mrt_parse_obj_plane.c				\
				   mrt_parse_obj_rectangle.c			\
				   mrt_parse_obj_sphere.c				\
				   mrt_parse_obj_tube.c					\
				   mrt_parse_res.c						\
				   mrt_parse_sampling.c					\
				   mrt_parse_scene.c					\
				   mrt_parse_texture.c					\
				   mrt_parse_utils.c					\
				   mrt_parse_vec3.c
SRCS_PRINT		:= mrt_print_color.c					\
				   mrt_print_error.c					\
				   mrt_print_light.c					\
				   mrt_print_material.c					\
				   mrt_print_obj_disc.c					\
				   mrt_print_obj_plane.c				\
				   mrt_print_obj_rectangle.c			\
				   mrt_print_obj_sphere.c				\
				   mrt_print_obj_tube.c					\
				   mrt_print_scene.c					\
				   mrt_print_scene_debug.c				\
				   mrt_print_textures.c					\
				   mrt_print_vec3.c
SRCS_TRACE		:= mrt_trace.c							\
				   mrt_trace_dielectric.c				\
				   mrt_trace_diffuse.c					\
				   mrt_trace_light_pdf.c				\
				   mrt_trace_light_random.c				\
				   mrt_trace_obj_intersect_1.c			\
				   mrt_trace_obj_intersect_2.c			\
				   mrt_trace_obj_intersect_2_utils.c	\
				   mrt_trace_obj_normal_1.c				\
				   mrt_trace_obj_normal_2.c				\
				   mrt_trace_onb.c						\
				   mrt_trace_random.c					\
				   mrt_trace_specular.c

SRCS			+= $(addprefix graphic/, $(SRCS_GRAPHIC))	\
				   $(addprefix math/, $(SRCS_MATH)) 		\
				   $(addprefix parse/, $(SRCS_PARSE))		\
				   $(addprefix print/, $(SRCS_PRINT))		\
				   $(addprefix trace/, $(SRCS_TRACE))

SDIR			:= src
ODIR			:= obj
OBJS			:= $(addprefix $(ODIR)/, $(SRCS:%.c=%.o))

IDIR			:= $(SDIR)
INCLUDES		:= $(wildcard $(IDIR)/*.h) $(wildcard $(IDIR)/**/*.h)

LIBS			:= lib/libft/libft.a lib/libmlx/libmlx42.a
LDFLAGS			:= $(LIBS) -lm

# **************************************************************************** #
#	SYSTEM SPECIFIC SETTINGS							   					   #
# **************************************************************************** #

UNAME	:= $(shell uname -s)
NUMPROC	:= 8

ifeq ($(UNAME), Linux)
    NUMPROC := $(shell grep -c ^processor /proc/cpuinfo)
	CFLAGS	+= -D LINUX -D THREADS=$(NUMPROC) -Wno-unused-result
	LDFLAGS	+= -lglfw -ldl
else ifeq ($(UNAME), Darwin)
    NUMPROC := $(shell sysctl -n hw.ncpu)
	CFLAGS	+= -D DARWIN -D THREADS=$(NUMPROC)
	LDFLAGS += lib/libmlx/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit
endif

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

all:
	@$(MAKE) $(NAME) -j$(NUMPROC)

$(NAME): $(LIBS) $(ODIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. $(addprefix -I, $(IDIR)) -c $< -o $@

$(ODIR):
	@mkdir -p $(ODIR)

lib/libft/libft.a:
	@$(MAKE) -C lib/libft/

lib/libmlx/libmlx42.a:
	@$(MAKE) -C lib/libmlx/

clean:
	@$(MAKE) -C lib/libft fclean
	@$(MAKE) -C lib/libmlx fclean
	$(RM) -r $(ODIR)

fclean: clean
	$(RM) -r *.dSYM $(SDIR)/*.dSYM
	$(RM) $(NAME)

re: fclean all

bonus: all

debug: CFLAGS += -O0 -DDEBUG -g
debug: all
