# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hepple <hepple@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/17 11:48:30 by hepple            #+#    #+#              #
#    Updated: 2022/06/08 12:19:59 by hepple           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ********************* #
#   V A R I A B L E S   #
# ********************* #

NAME	=	libft.a
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -O2
INCLUDE	=	-I./inc
SRC_DIR	=	src
SRC_MDT	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_itoa.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strjoin.c \
			ft_strmapi.c \
			ft_strtrim.c \
			ft_substr.c
SRC_BNS	=	ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c
SRC_ADD	=	ft_free_split.c ft_strcmp.c ft_gnl_without_buffer.c \
			ft_split_count_str.c ft_strncmp_rev.c ft_str_count_chr.c \
			ft_rand.c ft_double_from_str.c ft_int_from_str.c
OBJ_DIR	=	obj
OBJ_MDT	=	$(addprefix $(OBJ_DIR)/, $(SRC_MDT:.c=.o))
OBJ_BNS	=	$(addprefix $(OBJ_DIR)/, $(SRC_BNS:.c=.o))
OBJ_ADD	=	$(addprefix $(OBJ_DIR)/, $(SRC_ADD:.c=.o))
OBJ		=	$(OBJ_MDT) $(OBJ_BNS) $(OBJ_ADD)

# ********************* #
#      S Y S T E M      #
# ********************* #

ifeq ($(shell uname -s), Linux)
	CFLAGS += -D LINUX -Wno-unused-result
endif

# ********************* #
#       R U L E S       #
# ********************* #

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	@echo "ar create libft (libft.a)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) -r *.dSYM
	$(RM) $(NAME)

fclean: clean

re: fclean all
