/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 02:02:01 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/26 20:18:00 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;

	va_start(args, format);
	len = ft_vdprintf(1, format, args);
	va_end(args);
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		len;
	va_list	args;

	va_start(args, format);
	len = ft_vdprintf(fd, format, args);
	va_end(args);
	return (len);
}

int ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}

int	ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_vars	*v;
	int		ret;

	if (!(v = ft_memalloc(sizeof(*v))))
		return (-1);
	ft_bzero(v, sizeof(*v));
	v->format = (char *)format;
	v->args = (va_list *)&ap;
	v->fd = fd;
//	v->len = 0;
	v->len = core(v);
	ret = v->len;
	free(v);
	return (ret);
}
