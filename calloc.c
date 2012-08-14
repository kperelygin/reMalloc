/*
** calloc.c for malloc in /home/perely_k/work/malloc2
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Fri Mar 27 18:30:06 2009 kyrylo perelygin
** Last update Sat Mar 28 21:42:52 2009 kyrylo perelygin
*/

#include <unistd.h>
#include "malloc.h"

void	*calloc(int number, int size)
{
  void	*addr;
  char	*str;
  int	i;

  i = 0;
  addr = malloc(number * size);
  if (addr == NULL)
    return (addr);
  str = addr;
  while (i < number * size)
    {
      str[i] = 0;
      i++;
    }
  return (addr);
}
