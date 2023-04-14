# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:03:28 by lciullo           #+#    #+#              #
#    Updated: 2023/04/14 13:02:33 by lciullo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include paths/headers_execution.mk
include paths/headers_parsing.mk
include paths/sources_execution.mk
include paths/sources_parsing.mk

# ====================== VARIABLES ====================== #

# ---- Final executable ---- #

NAME 		= minishell

DIR_LIB 	= libft

LIBRARY 	= ${DIR_LIB}/libft.a 

# ---- Directories and path files ---- #

DIR_HEAD 		= 	head/

DIR_OBJS 	=	.objs

OBJS 		=	$(addprefix ${DIR_OBJS}/, ${SRC:.c=.o})

DEBUG		=	no

VALGRIND	= 	no

# ---- Compilation flags ---- #

CC 			= cc

CFLAGS 		= -Wall -Werror -Wextra -I ${DIR_HEAD} -I ${DIR_LIB}

# ---- Debug Compilation flags ---- #

DFLAGS		= -g3 -fsanitize=address

ifeq (${DEBUG}, yes)
CFLAGS		+= ${DFLAGS}
endif

# ---- Leaks Compilation flags ---- #

LEAKS	=	valgrind --suppressions=ignore_readline_reachable.txt --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes

# ---- Commands ---- #

RMF			=	rm -rf

# ====================== RULES ====================== #

# ---- Compilation rules ---- #

all :
	${MAKE} lib
	${MAKE} ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} $^ ${LIBRARY} -o $@ -lreadline

${DIR_OBJS}/%.o: %.c ${HEAD} ${LIBRARY}
	mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

# ---- Library ---- #

lib :
	${MAKE} -C ./libft
	
# ---- Debug rules ---- #

debug:
	${MAKE} re DEBUG=yes
	
leaks:
	clear
	$(MAKE) re VALGRIND=yes
	$(LEAKS) ./minishell

# ---- Clean rules --- #

clean :
	${MAKE} -C libft clean
	${RMF} ${DIR_OBJS}

fclean : clean 
	${MAKE} -C libft fclean
	${RMF}  ${NAME}

re : fclean
	${MAKE} all

.PHONY: all lib clean fclean re