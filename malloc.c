/*
** malloc.c for malloc in /home/perely_k/work/malloc2
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Sun Mar 22 23:50:11 2009 kyrylo perelygin
** Last update Sun Mar 29 15:24:39 2009 kyrylo perelygin
*/

#include <unistd.h>
#include "malloc.h"

t_header	*gl_freelist = NULL;
void		*gl_lowlimit = NULL;
int		thread_locked = 0;

static void	*getMoreMem(int size)
{
  int		units;
  void		*address;
  t_header	*tmp;

  units = size;
  if (units < MIN_MALLOC)
    units = MIN_MALLOC;
  address = sbrk(units);
  if (address == (void *)-1)
    return (NULL);
  tmp = address;
  tmp->magic = MALLOC_MAGIC;
  tmp->next = NULL;
  if (MIN_MALLOC - size >= THRESHOLD)
    {
      tmp->size = size - sizeof(*tmp);
      split_end(tmp);
    }
  else
    tmp->size = size - sizeof(*tmp);
  if (gl_lowlimit == NULL)
    gl_lowlimit = tmp;
  return (tmp);
}

void		*malloc(int size)
{
  t_header	*tmp;
  int		total_size;

  if (size <= 0)
    return (NULL);
  lock_thread();
  if ((size % sizeof(int)) != 0)
    size += (sizeof(int) - (size % sizeof(int)));
  if ((tmp = (t_header *)findFreeBlock(size)) == NULL)
    tmp = (t_header *)getMoreMem(size + sizeof(*tmp));
  else
    {
      if (tmp->size - size >= THRESHOLD)
	{
	  total_size = tmp->size + sizeof(*tmp);
	  tmp->size = size;
	  split_mid(tmp, total_size);
	}
      deleteFromFreeList(tmp);
    }
  unlock_thread();
  if (tmp == NULL)
    return (NULL);
  return ((void *)((int)tmp + sizeof(*tmp)));
}
