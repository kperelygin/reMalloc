/*
** test.c for test in /home/perely_k/work/malloc_RENDU
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Sun Mar 29 16:55:29 2009 kyrylo perelygin
** Last update Sun Mar 29 16:56:40 2009 kyrylo perelygin
*/

int	main(int argc, char **argv)
{
  malloc(200);
  malloc(100);
  malloc(300);
  malloc(560);
  malloc(99);
  malloc(3399);
  show_alloc_mem();
}
