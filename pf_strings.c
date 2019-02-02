/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 02:36:16 by ikourkji          #+#    #+#             */
/*   Updated: 2019/02/02 10:45:37 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_float(t_vars *v)
{
	(!(v->flags & F_PREC)) ? v->prec = 6 : 0;
	printf("this is for floating nums\n");
}

static void	pf_uchar(t_vars *v, wchar_t s)
{
	wchar_t	c;
	wchar_t tmp;

	c = (s) ? s : va_arg(v->args, unsigned long int);
	v->clen = pf_wcharlen(c);
	printf("len: %d\n", v->clen);

}

/*
** this doesn't print unicode sequences by default
** because that is technically incorrect
** wchars can have any encoding, not just unicode
** but, passed # (conversion operator), prints wchars as unicode
*/

static void	pf_wchar(t_vars *v, wchar_t s)
{
	wchar_t	c;
	wchar_t	tmp;

	c = (s) ? s : va_arg(v->args, unsigned long int);
	v->clen = pf_wcharlen(c);
	printf("len: %d\n", v->clen);
	if (v->flags & F_CONV)
	{
		v->clen = pf_ucharlen(c);
		if (v->clen == 1 && v->clen--)
			pf_placechar(v, (char)c);
		else
			tmp = c >> (6 * (--v->clen));
		v->clen == 1 ? pf_placechar(v, (char)((tmp & 0x1F) | 0xC0)) : 0;
		v->clen == 2 ? pf_placechar(v, (char)((tmp & 0xF) | 0xE0)) : 0;
		v->clen == 3 ? pf_placechar(v, (char)((tmp & 0x7) | 0xF)) : 0;
		while (--v->clen)
			pf_placechar(v, (char)((c >> (6 * v->clen) & 0x3F) | 0x80));
	}
	else
		while (v->clen--)
			pf_placechar(v, (char)(c >> (v->clen << 3)));
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

	s = va_arg(v->args, wchar_t*);
	while (*s)
		pf_wchar(v, *s++);
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
