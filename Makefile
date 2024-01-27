##
## EPITECH PROJECT, 2024
## B-PDG-300-PAR-3-1-PDGRUSH3-eva.legrand
## File description:
## Makefile
##

NAME	=	MyGKrellm

CC	= g++

SRC	=	src/main.cpp	\
		src/module/RamModule.cpp	\
		src/module/SysInfoModule.cpp	\
		src/module/CpuModule.cpp	\
		src/ncurses/DisplayNcurses.cpp

OBJ	=	$(SRC/.c=.o)

CPPFLAGS	=	-W -Wall -Wextra -lcurses

$(NAME):
	$(CC) $(SRC) -o $(NAME) $(CPPFLAGS) -lncurses -lsfml-graphics -lsfml-window -lsfml-system -g3

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	$(NAME) all clean
