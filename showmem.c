/*
** showmem.c for malloc in /home/perely_k/work/malloc2
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Mon Mar 23 19:49:50 2009 kyrylo perelygin
** Last update Fri Mar 27 19:26:07 2009 kyrylo perelygin
*/

#include <unistd.h>
#include "malloc.h"

void		show_alloc_mem()
{
  void		*addr;
  void		*end;
  t_header	*tmp;
  int		offset;
  int		size;

  addr = gl_lowlimit;
  end = sbrk(0);
  my_fprintf(2, "break : 0x%x\n", end);
  if (addr == NULL)
    return ;
  while ((int)addr <= (int)end)
    {
      tmp = addr;
      offset = sizeof(*tmp) + tmp->size + (int)tmp;
      size = tmp->size + sizeof(*tmp);
      if (tmp->magic == MALLOC_MAGIC)
	my_fprintf(2, "0x%x - 0x%x : %d octets\n", tmp, offset, size);
      addr = (void *)((int)addr + tmp->size + sizeof(*tmp));
    }
}
