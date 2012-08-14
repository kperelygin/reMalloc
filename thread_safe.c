/*
** thread_safe.c for malloc in /home/perely_k/work/malloc_RENDU
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Sun Mar 29 15:07:33 2009 kyrylo perelygin
** Last update Tue Mar 31 12:29:57 2009 kyrylo perelygin
*/

#include <unistd.h>
#include "malloc.h"

void	lock_thread()
{
  while (thread_locked == 1)
    usleep(1);
  thread_locked = 1;
}

void	unlock_thread()
{
  thread_locked = 0;
}
