# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjensen <tjensen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 09:02:38 by tjensen           #+#    #+#              #
#    Updated: 2022/12/19 12:42:28 by tjensen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	PROJECT SPECIFIC														   #
# **************************************************************************** #

NAME			:= miniRT

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -O3#-g -fsanitize=address
DEPFLAGS     	 = -MT $@ -MMD -MP -MF $(DDIR)/$*.d

VPATH			:= src/ src/graphic/ src/math/ src/parse/ src/print/ src/trace/
SRCS			:= main.c								\
				   mrt_color.c							\
				   mrt_light.c							\
				   mrt_obj.c							\
				   mrt_obj_checkerboard.c				\
				   mrt_obj_texture.c					\
				   mrt_obj_texture_utils.c				\
				   mrt_scene.c							\
				   mrt_scene_utils.c
SRCS			+= mrt_graphic.c						\
				   mrt_graphic_move.c					\
				   mrt_graphic_render.c					\
				   mrt_graphic_rotate.c
SRCS			+= mrt_math_color.c						\
				   mrt_math_vec3_1.c					\
				   mrt_math_vec3_2.c
SRCS			+= mrt_parse_amb.c						\
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
SRCS			+= mrt_print_color.c					\
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
SRCS			+= mrt_trace.c							\
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

ODIR			:= obj
OBJS			:= $(SRCS:%.c=$(ODIR)/%.o)

DDIR			:= $(ODIR)/.deps
DEPS			:= $(SRCS:%.c=$(DDIR)/%.d)

LIBS			:= lib/libft/libft.a lib/libmlx/libmlx42.a
LDLIBS          := $(LIBS) -lm -lpthread
LDFLAGS         :=

# **************************************************************************** #
#	SYSTEM SPECIFIC SETTINGS							   					   #
# **************************************************************************** #

UNAME	:= $(shell uname -s)
NUMPROC	:= 8

ifeq ($(UNAME), Linux)
    NUMPROC := $(shell grep -c ^processor /proc/cpuinfo)
	CFLAGS	+= -D LINUX -D THREADS=$(NUMPROC) -Wno-unused-result
	LDLIBS	+= -lglfw -ldl
else ifeq ($(UNAME), Darwin)
    NUMPROC := $(shell sysctl -n hw.ncpu)
	CFLAGS	+= -D DARWIN -D THREADS=$(NUMPROC)
	LDLIBS += lib/libmlx/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit
endif

# **************************************************************************** #
#	RULES																	   #
# **************************************************************************** #

all:
	@$(MAKE) $(NAME) -j$(NUMPROC)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

$(ODIR)/%.o: %.c $(DDIR)/%.d | $(ODIR) $(DDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -I./src -I./lib -c $< -o $@

$(ODIR):
	@mkdir -p $@

$(DDIR):
	@mkdir -p $@

%.a:
	@$(MAKE) -C $(dir $@)

clean:
	@$(MAKE) -C lib/libft fclean
	@$(MAKE) -C lib/libmlx fclean
	$(RM) -r $(DDIR) $(ODIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all

$(DEPS):
include $(wildcard $(DEPS))
