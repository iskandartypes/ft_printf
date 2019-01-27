/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 21:45:26 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/26 22:25:39 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_vsprintf(char *str, const char *format, va_list ap)
{
	int		len;
	size_t	max;
	int		pow;
	char	**ret;

	max = 0;
	pow = sizeof(int) * 8;
	while (pow--)
	{
		max <<= 1;
		max |= 1;
	}
	max++;
	len = ft_vasprintf(ret, format, ap);
	str = ft_memcpy(str, *ret, max);
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
	str = ft_memcpy(str, *ret, size);
	ft_memdel(*ret);
	if (size)
		str[size] = '\0';
	len = len > size ? size : len;
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

}
