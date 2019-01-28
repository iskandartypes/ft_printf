/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:52:18 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/28 02:58:30 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "./libft/libft.h"

typedef struct	s_vars
{
	va_list	*args;
	char	*format;
	char	*buf;
	size_t	buf_len;
	size_t	buf_i;
	int		clen;
	int		min;
	int		base;
	int		pad;
	int		prec;
	int		flags;
}				t_vars;

typedef void	(*f_array)(t_vars*);

//flags
# define F_CONV		0x1; //# reqs conversions
# define F_ZPAD		0x2; //0 pads w/zero instead of blank (ignore if precis.)
# define F_RPAD		0x4; //- pads on right (left adjusted for min width). Overrides 0.
# define F_BLANK	0x8; //' ' leaves blank before positive number
# define F_SIGN		0x10; //+ all signed nums get a sign (so -17/+17). Overrides ' '
# define F_MINWIDTH	0x20; //#s specifying min field width
# define F_PREC		0x40; //. if no #s after presumed 0; min digits for diouxX,
//								# of digits after . for double, # sig digs for sci,
//								# of chars in string (from front)
# define F_BASE		0x80; //_, added flag for base
# define F_H		0x100; //h short / unsigned short (all formatted di / ouxX)
# define F_HH		0x200; //hh signed char / unsigned char
# define F_L		0x400; //l long / unsigned long
# define F_LL		0x800; //ll long long / unsigned long long
# define F_MAX		0x1000; //j intmax_t / uintmax_t
# define F_SIZE		0x2000; //z ssize_t / size_t

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_vprintf(const char *format, va_list ap);
int		ft_vdprintf(int fd, const char *format, va_list ap);
int		ft_sprintf(char *str, const char *format, ...);

int		ft_vsprintf(char *str, const char *format, va_list ap);
int		ft_snprintf(char *str, size_t size, const char *format, ...);
int		ft_vsnprintf(char *str, size_t size, const char *format, va_list ap);
int		ft_asprintf(char **ret, const char *format, ...);
int		ft_vasprintf(char **ret, const char *format, va_list ap);

void	core(t_vars *v);

#endif
