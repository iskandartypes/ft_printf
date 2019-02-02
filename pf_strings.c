/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 02:36:16 by ikourkji          #+#    #+#             */
/*   Updated: 2019/02/02 12:22:09 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_float(t_vars *v)
{
	(!(v->flags & F_PREC)) ? v->prec = 6 : 0;
	printf("this is for floating nums\n");
}

static int	pf_uchar(t_vars *v, wchar_t c)
{
	wchar_t tmp;
	int		len;

	v->clen = pf_uclen(c);
	len = v->clen;
	if (v->clen == 1 && v->clen--)
		pf_placechar(v, (char)c);
	else
		tmp = c >> (6 * (--v->clen));
	v->clen == 1 ? pf_placechar(v, (char)((tmp & 0x1F) | 0xC0)) : 0;
	v->clen == 2 ? pf_placechar(v, (char)((tmp & 0xF) | 0xE0)) : 0;
	v->clen == 3 ? pf_placechar(v, (char)((tmp & 0x7) | 0xF0)) : 0;
	while (--v->clen > -1)
		pf_placechar(v, (char)((c >> (6 * v->clen) & 0x3F) | 0x80));
	return (len);
}

/*
** this doesn't print UTF-8 sequences by default
** because that is technically incorrect
** wchars can have any encoding
** but, passed # (conversion operator), prints wchars as UTF-8
*/

static int	pf_wchar(t_vars *v, wchar_t s)
{
	wchar_t	c;
	int		len;

	c = (s) ? s : va_arg(v->args, unsigned long int);
	v->clen = (v->flags & F_CONV) ? 1 : pf_wclen(c);
	len = v->clen;
	v->min -= v->clen;
	if (!(v->flags & F_RPAD))
		while (v->min-- > 0)
			pf_placechar(v, v->flags & F_ZPAD ? '0' : ' ');
	if (v->flags & F_CONV)
		len = pf_uchar(v, c);
	else
		while (v->clen--)
			pf_placechar(v, (char)(c >> (v->clen << 3)));
	while (v->min-- > 0)
		pf_placechar(v, ' ');
	return (len);
}

void		pf_char(t_vars *v)
{
	unsigned char	c;

	if (v->flags & F_L)
		pf_wchar(v, '\0');
	else
	{
		c = va_arg(v->args, int);
		v->min--;
		if (!(v->flags & F_RPAD))
			while (v->min-- > 0)
				pf_placechar(v, v->flags & F_ZPAD ? '0' : ' ');
		pf_placechar(v, c);
		while (v->min-- > 0)
			pf_placechar(v, ' ');
	}
}

static void	pf_wstr(t_vars *v)
{
	wchar_t	*s;
	int		len;

	s = va_arg(v->args, wchar_t*);
	v->clen = (v->flags & F_CONV) ? pf_ustrlen(s) : pf_wstrlen(s);
	(v->flags & F_PREC) && (v->clen > v->prec) ? v->clen = v->prec : 0;
	v->min -= v->clen;
	if (!(v->flags & F_RPAD))
		while (v->min-- > 0)
			pf_placechar(v, v->flags & F_ZPAD ? '0' : ' ');
	len = 0;
	while ((len + (v->flags & F_CONV ? pf_uclen(*s) : pf_wclen(*s))) < v->clen)
		len += pf_wchar(v, *(s++));
	while (v->min-- > 0)
		pf_placechar(v, ' ');
}

void	pf_str(t_vars *v)
{
	char	*s;
	int		i;

	if (v->flags & F_L)
		pf_wstr(v);
	else
	{
		s = va_arg(v->args, char*);
		v->clen = ft_strlen(s);
		(v->flags & F_PREC) && (v->clen > v->prec) ? v->clen = v->prec : 0;
		v->min -= v->clen;
		if (!(v->flags & F_RPAD))
			while (v->min-- > 0)
				pf_placechar(v, v->flags & F_ZPAD ? '0' : ' ');
		i = 0;
		while (i < v->clen)
			pf_placechar(v, s[i++]);
		while (v->min-- > 0)
			pf_placechar(v, ' ');
	}
}
