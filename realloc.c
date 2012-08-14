/*
** realloc.c for malloc in /home/perely_k/work/malloc2
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Fri Mar 27 18:41:37 2009 kyrylo perelygin
** Last update Sun Mar 29 15:49:26 2009 kyrylo perelygin
*/

#include <string.h>
#include <unistd.h>
#include "malloc.h"

t_header	*verifyPtr(void *ptr)
{
  t_header	*tmp;

  if (ptr == NULL)
    return (NULL);
  lock_thread();
  if (gl_lowlimit == NULL)
    {
      my_fprintf(2, "[malloc] Error: No first malloc found\n");
      unlock_thread();
      return (NULL);
    }
  if (ptr < gl_lowlimit)
    {
      my_fprintf(2, "[malloc] Error: Address is before the low limit.\n");
      unlock_thread();
      return (NULL);
    }
  tmp = (t_header *)((int)ptr - sizeof(*tmp));
  unlock_thread();
  return (tmp);
}

void		*realloc(void *ptr, int size)
{
  t_header	*tmp;
  void		*new;
  int		bak_size;

  if (ptr == NULL)
    return (malloc(size));
  if ((tmp = verifyPtr(ptr)) == NULL)
    return (NULL);
  if (tmp->size == size)
    return (ptr);
  lock_thread();
  bak_size = tmp->size;
  addToFreeList(tmp, 0);
  unlock_thread();
  new = malloc(size);
  lock_thread();
  if (ptr != new)
    {
      if (size > bak_size)
	memcpy(new, ptr, bak_size);
      else
	memcpy(new, ptr, size);
    }
  unlock_thread();
  return (new);
}

void		*reallocf(void *ptr, int size)
{
  void		*addr;
  t_header	*tmp;

  addr = realloc(ptr, size);
  if (addr == NULL)
    {
      tmp = verifyPtr(ptr);
      if (tmp == NULL)
	return (NULL);
      if (tmp->magic == MALLOC_MAGIC)
	free((void *)((int)tmp + sizeof(*tmp)));
    }
  return (addr);
}
