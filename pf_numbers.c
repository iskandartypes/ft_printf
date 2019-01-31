/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:45:00 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/31 00:49:43 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	int_add(t_vars *v, intmax_t n)
{
	char	*tmp;
	int		pad;
	int		zpad;
	int		ng;

	ng = (n < 0) ? -1 : 1;
	if (!(tmp = pf_uitoa_base((uintmax_t)(n * ng), v->base, v->flags & F_UP)))
		return ;
	v->clen = ft_strlen(tmp);
	zpad = v->prec - v->clen;
	pad = v->min - (zpad > 0 ? v->prec : v->clen);
	pad -= ((v->flags & F_BLANK) || (v->flags & F_SIGN)) ? 1 : 0;
	(v->flags & F_ZPAD) ? zpad = pad : 0;
	while (!(v->flags & F_RPAD) && !(v->flags & F_ZPAD) && pad-- > 0)
		pf_placechar(v, ' ');
	(v->flags & F_BLANK) ? pf_placechar(v, ' ') : 0;
	(v->flags & F_SIGN && ng == 1) ? pf_placechar(v, '+') : 0;
	(ng == -1) ? pf_placechar(v, '-') : 0;
	while (zpad-- > 0)
		pf_placechar(v, '0');
	while (*tmp)
		pf_placechar(v, *(tmp++));
	while (pad-- > 0)
		pf_placechar(v, ' ');
	free(tmp - v->clen);
}

void		pf_int(t_vars *v)
{
	intmax_t	n;

	n = 0;
	(v->flags & F_L) && (v->flags & F_LL) ? v->flags &= ~F_L: 0;
	!(v->flags & F_ALL) ? n = (intmax_t)va_arg(*v->args, int) : 0;
	v->flags & F_H ? n = (intmax_t)va_arg(*v->args, int) : 0;
	v->flags & F_L ? n = (intmax_t)va_arg(*v->args, long) : 0;
	v->flags & F_LL ? n = (intmax_t)va_arg(*v->args, long long) : 0;
	v->flags & F_SIZE ? n = (intmax_t)va_arg(*v->args, ssize_t) : 0;
	v->flags & F_MAX ? n = (intmax_t)va_arg(*v->args, intmax_t) : 0;
	int_add(v, n);
}

static void	uint_add(t_vars *v, uintmax_t n)
{
	char	*tmp;
	int		pad;
	int		zpad;

	if (!(tmp = pf_uitoa_base(n, v->base, v->flags & F_UP)))
		return ;
	printf("tmp: %s\n", tmp);//printf here!
	v->clen = ft_strlen(tmp);
	zpad = v->prec - v->clen;
	pad = v->min - (zpad > 0 ? v->prec : v->clen);
	while (!(v->flags & F_RPAD) && pad-- > 0)
		pf_placechar(v, (v->flags & F_ZPAD ? '0' : ' '));
	while (zpad-- > 0)
		pf_placechar(v, '0');
	while (*tmp)
		pf_placechar(v, *(tmp++));
	while (pad-- > 0)
		pf_placechar(v, ' ');
	free(tmp - v->clen);
}

/*
** bBoOuUxX
** note that char and short are cast to int, because variadic functions
** implicitly cast to int all data types narrower than int
** so the following lines were cut:
** (v->flags & F_H) && (v->flags & F_HH) ? v->flags &= ~F_H: 0;
** v->flags & F_HH ? n = (uintmax_t)va_arg(*v->args, unsigned char) : 0;
*/

void		pf_uint(t_vars *v)
{
	uintmax_t	n;

	n = 0;
	(v->flags & F_L) && (v->flags & F_LL) ? v->flags &= ~F_L: 0;
	(!(v->flags & F_ALL)) ? n = (uintmax_t)va_arg(*v->args, unsigned int) : 0;
	v->flags & F_H ? n = (uintmax_t)va_arg(*v->args, unsigned int) : 0;
	v->flags & F_L ? n = (uintmax_t)va_arg(*v->args, unsigned long) : 0;
	v->flags & F_LL ? n = (uintmax_t)va_arg(*v->args, unsigned long long) : 0;
	v->flags & F_SIZE ? n = (uintmax_t)va_arg(*v->args, size_t) : 0;
	v->flags & F_MAX ? n = (uintmax_t)va_arg(*v->args, uintmax_t) : 0;
	uint_add(v, n);
}

void	pf_float(t_vars *v)
{
	printf("this is for floating nums\n");
}

void	pf_char(t_vars *v)
{
	printf("this is for chars\n");
}

void	pf_str(t_vars *v)
{
	printf("this is for strs\n");
}
