/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:47:29 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/29 00:07:26 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

/*
**  #  conv
**  0  zpad
**  -  rpad
** ' ' blank
**  +  sign
*/

static void	parse_flags_mods(t_vars *v)
{
	int	f;

	f = -1;
	printf("char at parse_flags_mods: %c\n", *v->format);
	while ((f = ft_charat("#0- +", *v->format)) > -1 && ++v->format)
	{
		v->flags |= (1 << f);
		printf("is the charat executing?\n");
	}
	(v->flags & F_RPAD) ? v->flags &= ~F_ZPAD : 0;
	(v->flags & F_SIGN) ? v->flags &= ~F_BLANK : 0;
	if (*v->format >= '0' && *v->format <= '9')
		v->min = ft_atoi_skip(&v->format);
	if (*v->format == '.')
	{
		v->format++;
		v->prec = ft_atoi_skip(&v->format);
		v->flags |= F_PREC;
	}
	if ((f = ft_charat("hljzL", *v->format)) > -1)
	{
		v->flags |= (1 << (f + 8));
		if (f == 0)
			v->flags |= (*(v->format + 1) == 'h' && v->format++) ? F_HH : 0;
		else if (f == 1)
			v->flags |= (*(v->format + 1) == 'l' && v->format++) ? F_LL : 0;
		v->format++;
	}
}

void	test(t_vars *v);

static void	parse_init(t_vars *v)
{
	v->flags = 0;
	v->clen = 0;
	v->min = 0;
	v->prec = 0;
	parse_flags_mods(v);
	test(v);	
}

void		core(t_vars *v)
{
	while (*(v->format))
	{
		if (*(v->format) == '%')
		{
			if (!*(v->format + 1))
				break ;
			v->format++;
			if (*v->format != '%')
				parse_init(v);
		}
		v->buf[v->buf_i] = *(v->format);
		v->buf_i++;
		if (v->buf_i == v->buf_len)
		{
			if (!(v->buf = ft_rememalloc(v->buf, v->buf_len, v->buf_len * 2)))
				return ;
			else
				v->buf_len *= 2;
		}
		v->format++;
	}
	v->buf = ft_rememalloc(v->buf, v->buf_len, v->buf_i);
}

void	test(t_vars *f)
{
	printf("flags: \n-------\nF_CONV: %d\nF_ZPAD: %d\nF_RPAD: %d\nF_BLANK: %d\nF_SIGN: %d\n", \
			f->flags & F_CONV, f->flags & F_ZPAD, f->flags & F_RPAD, f->flags & F_BLANK, f->flags & F_SIGN);
}
