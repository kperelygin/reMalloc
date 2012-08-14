/*
** my_fprintf.c for lib in /home/perely_k/work/my_script/Lib
** 
** Made by kyrylo perelygin
** Login   <perely_k@epitech.net>
** 
** Started on  Mon Mar  2 22:49:04 2009 kyrylo perelygin
** Last update Fri Mar 27 16:46:39 2009 kyrylo perelygin
*/

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include "malloc.h"

static int	my_fputchar(int fd, char c)
{
  int	x;

  x = write(fd, &c, 1);
  return (x);
}

static void	my_fputnbr(int fd, int nb)
{
  int	beg;
  int	end;

  if (nb < 0)
    {
      my_fputchar(fd, '-');
      my_fputnbr(fd, -nb);
    }
  else
    {
      end = nb % 10;
      beg = nb / 10;
      if (beg != 0)
	my_fputnbr(fd, beg);
      my_fputchar(fd, end + '0');
    }
}

static int	my_fputstr(int fd, char *str)
{
  int	x;

  x = write(fd, str, strlen(str));
  return (x);
}

static void	my_fputnbr_base(int fd, int nbr)
{
  int		beg;
  int		end;
  int		p;
  char		*base;

  p = 16;
  base = "0123456789ABCDEF";
  if (nbr < 0)
    {
      my_fputchar(fd, '-');
      my_fputnbr_base(fd, -nbr);
    }
  else
    {
      end = nbr % p;
      beg = (nbr - end) / p;
      if (beg != 0)
	my_fputnbr_base(fd, beg);
      my_fputchar(fd, base[end]);
    }
}

int		my_fprintf(const int fd, char *src, ...)
{
  va_list	ap;

  va_start(ap, src);
  while (*src != '\0')
    {
      if (*src == '%')
	{
	  src++;
	  if (*src == 'd')
	    my_fputnbr(fd, va_arg(ap, int));
	  else if (*src == 'c')
	    my_fputchar(fd, va_arg(ap, int));
	  else if (*src == 's')
	    my_fputstr(fd, va_arg(ap, char *));
	  else if (*src == 'x')
	    my_fputnbr_base(fd, va_arg(ap, int));
	}
      else
	my_fputchar(fd, *src);
      src++;
    }
  return (0);
}
