/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 21:45:26 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/27 00:26:54 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** man 3 printf:
** The sprintf() and vsprintf() functions
** effectively assume a size of INT_MAX + 1.
** They both also won't be NULL-terminated if the last arg isn't.
** This is slightly edited here; both are always NULL-terminated
** (unlike the OG), although they can still both overwrite the end of the buf.
*/
int	ft_vsprintf(char *str, const char *format, va_list ap)
{
	int		len;
	size_t	max;
	char	**ret;

	max = 1 << (sizeof(int) * 8);
	len = ft_vasprintf(ret, format, ap);
	if (!*ret)
		return (-1);
	str = ft_memcpy(str, *ret, len);
	ft_memdel(*ret);
	return (len);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	int		len;
	va_list	args;

	va_start(args, format);
	len = ft_vsnprintf(str, size, format, args);
	va_end(args);
	return (len);
}

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	char	**ret;
	int		len;

	len = vasprintf(ret, format, ap);
	if (!*ret)
		return (-1);
	str = ft_memcpy(str, *ret, size);
	ft_memdel(*ret);
	if (size)
		str[size] = '\0';
	return (len);
}

int	ft_asprintf(char **ret, const char *format, ...)
{
	int		len;
	va_list	args;

	va_start(args, format);
	len = ft_vasprintf(ret, format, args);
	va_end(args);
	return (len);
}
int ft_vasprintf(char **ret, const char *format, va_list ap)
{
	t_vars	*v;
	int		len;

	if (!(v = ft_memalloc(sizeof(*v))))
		return (-1);
	v->format = (char *)format;
	v->args = (va_list *)&ap;
	core(v);
	len = v->len;
	ft_memdel(v);
	return (len);
}
