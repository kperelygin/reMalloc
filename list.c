/*
** list.c for malloc in /home/perely_k/work/malloc2
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Mon Mar 23 20:41:02 2009 kyrylo perelygin
** Last update Sun Mar 29 13:56:07 2009 kyrylo perelygin
*/

#include <unistd.h>
#include "malloc.h"

static void	insertInOrder(t_header *last, t_header *tmp, int fusion)
{
  t_header	*current;

  current = last->next;
  while (current)
    {
      if (tmp > current)
	{
	  last = current;
	  current = current->next;
	}
      else
	break;
    }
  last->next = tmp;
  tmp->next = current;
  if (fusion == 1)
    verifyFusion(last);
}

void		deleteFromFreeList(t_header *tmp)
{
  t_header	*begin;
  t_header	*save;

  begin = gl_freelist;
  if (tmp == gl_freelist)
    gl_freelist = gl_freelist->next;
  else
    {
      save = gl_freelist;
      while (save->next != tmp)
	save = save->next;
      save->next = tmp->next;
    }
  if (tmp)
    {
      tmp->magic = MALLOC_MAGIC;
      tmp->next = NULL;
    }
}

void		addToFreeList(t_header *tmp, int fusion)
{
  t_header	*last;

  tmp->magic = FREE_MAGIC;
  tmp->next = NULL;
  last = gl_freelist;
  if (last == NULL)
    gl_freelist = tmp;
  else
    {
      if (tmp < last)
	{
	  tmp->next = gl_freelist;
	  gl_freelist = tmp;
	}
      else
	insertInOrder(last, tmp, fusion);
      verifyFusion(tmp);
    }
}
