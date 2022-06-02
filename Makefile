##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

CC	=	gcc

SRC	=	sources/bin_commands.c	\
		sources/cd_commands.c	\
		sources/env_commands.c	\
		sources/extra_commands.c	\
		sources/commands.c	\
		sources/error_handling.c	\
		sources/mysh.c

OBJ	=	$(SRC:.c=.o)

NAME	=	mysh

LIBMY	=	-Llib -lmy

DEBUG	=	-g -Wall -Wextra

CPPFLAGS	=	-Iinclude/

all:	$(NAME)

$(NAME):	$(OBJ)
	cd lib/my && make && cd ../..
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LIBMY)

clean:
	find . -type f \( -name "*.o" -or -name "*#*" -or -name "*~" \
	-or -name "*.gcno" -or -name "*.gcda" \) -delete

fclean:	clean
	rm -f $(NAME)

re:	fclean all

debug:	$(OBJ)
	cd lib/my && make && cd ../..
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LIBMY) $(DEBUG)

.PHONY: all tests_run clean fclean re debug
