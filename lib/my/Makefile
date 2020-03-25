##
## EPITECH PROJECT, 2019
## PSU_my_printf_bootstrap_2019
## File description:
## Makefile
##

SRC = src/printf.c \
	src/printf_utility.c \
	src/my_putlonglong_base.c \
	src/formaters/string_formater.c \
	src/formaters/string_nonprintable_formater.c \
	src/formaters/char_formater.c \
	src/formaters/int_formater.c \
	src/formaters/uint_formater.c \
	src/formaters/ptr_formater.c \
	src/formaters/ubinary_formater.c \
	src/formaters/octal_formater.c \
	src/formaters/hexa_formater.c \
	src/formaters/big_hexa_formater.c \
	src/formaters/float_formater.c \
	src/formaters/no_format.c \
	src/get_nbr_size.c \
	my/*.c

OBJ = *.o

TESTS = tests/test_printf.c

INCLUDE = -I ./include

COVERAGE = --coverage -lcriterion

CC = gcc

CFLAGS = -Wall -Wshadow -Wextra -Wno-unused-parameter

NAME = libmy.a

UT = ut

all: $(NAME)

$(NAME):
	$(CC) -c $(SRC) $(INCLUDE) $(CFLAGS)
	ar rc $(NAME) $(OBJ)

tests_run:
	$(CC) -o $(UT) $(SRC) $(TESTS) $(INCLUDE) $(COVERAGE) $(CFLAGS)
	./$(UT)

clean:
	rm -rf $(OBJ)
	rm -rf *.gc*

fclean: clean
	rm -rf $(NAME)
	rm -rf $(UT)

re: fclean all

.PHONY = all build clean fclean