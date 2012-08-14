##
## Makefile for malloc in /u/all/perely_k/cu/rendu/proj/malloc
## 
## Made by kyrylo perelygin
## Login   <perely_k@epitech.net>
## 
## Started on  Fri Mar 27 22:15:03 2009 kyrylo perelygin
## Last update Mon Mar 30 17:41:32 2009 kyrylo perelygin
##

SRCS	=	malloc.c \
		free.c \
		showmem.c \
		thread_safe.c \
		split.c \
		list.c \
		my_fprintf.c \
		calloc.c \
		realloc.c \

OBJS	=	$(SRCS:.c=.o)
CC	=	gcc
NAME	=	libmy_malloc_$(HOSTTYPE).so
INCLUDES=	-I.
CFLAGS	=	-W -Wall -pedantic -O3 $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) -fpic -shared $(SRCS) -o $(NAME)
##	ln -f -s libmy_malloc_$(HOSTTYPE).so libmy_malloc.so

all:	$(NAME)

clean:
	rm -f $(OBJS)
	rm -f *~

fclean:	clean
	rm -f $(NAME)
	rm -f libmy_malloc.so

re: 	fclean all

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
