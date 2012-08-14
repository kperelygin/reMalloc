/*
** malloc.h for malloc in /home/perely_k/work/malloc2
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Mon Mar 23 10:47:48 2009 kyrylo perelygin
** Last update Sun Mar 29 14:30:46 2009 kyrylo perelygin
*/

#ifndef __MALLOC_H__
# define __MALLOC_H__

# define MIN_MALLOC 4096
# define THRESHOLD 16
# define MALLOC_MAGIC 0xDEADBEEF
# define FREE_MAGIC 0x42424242

typedef struct		s_header
{
  unsigned int		magic;
  int			size;
  struct s_header	*next;
}			t_header;

extern t_header	*gl_freelist;
extern void	*gl_lowlimit;
extern int	thread_locked;

int		my_fprintf(const int fd, char *src, ...);
void		*malloc(int size);
void		*calloc(int number, int size);
void		*realloc(void *ptr, int size);
void		*reallocf(void *ptr, int size);
void		free(void *address);
void		*findFreeBlock(int size);
void		addToFreeList(t_header *tmp, int fusion);
void		deleteFromFreeList(t_header *tmp);
int		getListNb(int size);
void		split_mid(t_header *tmp, int total_size);
void		split_end(t_header *tmp);
void		show_alloc_mem(void);
void		verifyFusion(t_header *begin);
t_header	*verifyPtr(void *ptr);
void		lock_thread();
void		unlock_thread();

#endif /* __MALLOC_H__ */
