/*
** free.c for malloc in /home/perely_k/work/malloc2
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Mon Mar 23 10:47:11 2009 kyrylo perelygin
** Last update Sun Mar 29 14:34:35 2009 kyrylo perelygin
*/

#include <unistd.h>
#include "malloc.h"

void		verifyFusion(t_header *begin)
{
  t_header	*block;

  if (begin && begin->next)
    {
      block = (t_header *)((int)begin + begin->size + sizeof(*begin));
      if (block->magic == FREE_MAGIC)
	{
	  begin->size = begin->size + block->size + sizeof(*block);
	  begin->next = block->next;
	}
    }
}

void		*findFreeBlock(int size)
{
  t_header	*begin;
  t_header	*tmp;
  unsigned int	min_size;

  tmp = NULL;
  min_size = -1;
  begin = gl_freelist;
  while (begin)
    {
      if ((unsigned int)begin->size < min_size && begin->size >= size)
	{
	  tmp = begin;
	  min_size = begin->size;
	}
      begin = begin->next;
    }
  return (tmp);
}

void		free(void *addr)
{
  t_header	*tmp;

  tmp = verifyPtr(addr);
  if (tmp == NULL)
    return ;
  lock_thread();
  if (tmp->magic == FREE_MAGIC)
    my_fprintf(2, "[malloc] Error: The block is already free.\n");
  if (tmp->magic == MALLOC_MAGIC)
    addToFreeList(tmp, 1);
  else
    my_fprintf(2, "[malloc] Error: Junk Pointer.\n");
  unlock_thread();
}
