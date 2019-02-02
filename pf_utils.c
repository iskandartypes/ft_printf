/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 21:11:19 by ikourkji          #+#    #+#             */
/*   Updated: 2019/02/02 12:19:16 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_placechar(t_vars *v, char c)
{
	printf("that block in hex: %#x\n", c);
	v->buf[v->buf_i] = c;
	v->buf_i++;
	if (v->buf_i == v->buf_len)
	{
		if (!(v->buf = ft_rememalloc(v->buf, v->buf_len, v->buf_len * 2)))
			return ;
		else
			v->buf_len *= 2;
	}
}

char	*pf_uitoa_base(uintmax_t n, int base, int up)
{
	char		*ret;
	int			len;
	uintmax_t	tmp;
	char		*b;

	tmp = n;
	len = 1;
	b = (up ? "0123456789ABCDEF" : "0123456789abcdef");
	while (tmp >= base && len++)
		tmp /= base;
	if (!(ret = ft_strnew(len)))
		return (0);
	len--;
	while (len > -1)
	{
		ret[len--] = b[n % base];
		n /= base;
	}
	return (ret);
}
