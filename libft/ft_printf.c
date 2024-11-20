
#include "libft.h"

int	ft_conversions(char format, va_list args)
{
	int	count;

	count = 0;

		if (format == 'c')
			count += ft_putchar_printf(va_arg(args, int));
		else if (format == 's')
			count += ft_putstr_printf(va_arg(args, char *));
		else if (format == 'p')
			count += ft_putptr_base(va_arg(args, unsigned long), "0123456789abcdef",
					0);
		else if (format == 'd' || format == 'i')
			count += printbase(va_arg(args, int), 10, "0123456789");
		else if (format == 'u')
			count += printbase(va_arg(args, unsigned int), 10, "0123456789");
		else if (format == 'x')
			count += printbase(va_arg(args, unsigned int), 16, "0123456789abcdef");
		else if (format == 'X')
			count += printbase(va_arg(args, unsigned int), 16, "0123456789ABCDEF");
		else if (format == '%')
			count += ft_putchar_printf('%');

	return (count);
}

int	ft_printf(const char *str, ...)
{
	int	i;
	va_list	args;
	int		count;

	count = 0;
	i = -1;
	if(str == NULL)
		return (-1);
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%')
		{
				count += ft_conversions(str[i + 1], args);
				i++;
		}
		else
			count += ft_putchar_printf(str[i]);
	}
	va_end(args);
	return (count);
}