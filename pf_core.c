/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:47:29 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/30 21:16:55 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while ((f = ft_charat("#0- +", *v->format)) > -1 && ++v->format)
		v->flags |= (1 << f);
	(v->flags & F_RPAD) ? v->flags &= ~F_ZPAD : 0;
	(v->flags & F_SIGN) ? v->flags &= ~F_BLANK : 0;
	if (*v->format >= '1' && *v->format <= '9')
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

/*
** the _ is a bonus base thing I wanted to add up to 16
** overwrites conversion base if in range, otherwise goes back to default
*/

static void	parse_base_long(t_vars *v)
{
	int i;

	i = -1;
	if (*v->format == '_' && *(++v->format))
	{
		v->base = ft_atoi_skip(&v->format);
		if (v->base > 1 && v->base < 17)
			i = 0;
	}
	if (i && (i = ft_charat("bBbboOxX", *v->format)) > -1)
		v->base = 2 << (i >> 1);
	if (i == -1)
		v->base = 10;
	if (ft_charat("DOUCS", *v->format) > -1)
		v->flags |= F_L;
	if (ft_charat("FBX", *v->format) > -1)
		v->flags |= F_UP;
}

static void	parse(t_vars *v)
{
	int i;

	i = 0;
	v->flags = 0;
	v->clen = 0;
	v->min = 0;
	v->prec = 0;
	v->base = 10;
	parse_flags_mods(v);
	parse_base_long(v);
	if ((i = ft_charat("dDiibBoOuUxXfFcCsS", *v->format)) > -1 && v->format++)
		v->ftab[i >> 1](v);
	else
		v->format++;
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
				parse(v);
		}
		pf_placechar(v, *v->format);
		if (!(v->buf))
			return ;
		v->format++;
	}
	v->buf = ft_rememalloc(v->buf, v->buf_len, v->buf_i);
}

void		make_ftab(t_vars *v)
{
	int i;

	if (!(v->ftab = malloc(sizeof(*v->ftab) * NCONV)))
		return ;
	i = 0;
	while (i < ICONV)
		v->ftab[i++] = &pf_int;
	while (i < (ICONV + UICONV))
		v->ftab[i++] = &pf_uint;
	v->ftab[i++] = &pf_float;
	v->ftab[i++] = &pf_char;
	v->ftab[i++] = &pf_str;
}

/*
void	test(t_vars *f)
{
	printf("flags: \n-------\nF_CONV: %d\nF_ZPAD: %d\nF_RPAD: %d\nF_BLANK: %d\nF_SIGN: %d\n", \
			f->flags & F_CONV, f->flags & F_ZPAD, f->flags & F_RPAD, f->flags & F_BLANK, f->flags & F_SIGN);
	printf("flags: \n-------\nF_PREC: %d & prec: %d\nF_H: %d\nF_HH: %d\nF_L: %d\nF_LL: %d\nF_MAX: %d\nF_SIZE: %d\n\n", \
			f->flags & F_PREC, f->prec, f->flags & F_H, f->flags & F_HH, f->flags & F_L, f->flags & F_LL, f->flags & F_MAX, f->flags & F_SIZE);
}
*/
