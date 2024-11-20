
#include "libft.h"

int	ft_putchar_printf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putptr_base(unsigned long long ptr, char *base, int f)
{
	int	count;

	count = 0;
	if (!ptr)
	{
		return (write(1, "(nil)", 5));
	}
	if (f == 0)
	{
		write(1, "0x", 2);
		count += 2;
	}
	if (ptr / 16 > 0)
	{
		count += ft_putptr_base((ptr / 16), base, 1);
	}
	ft_putchar_printf(base[ptr % 16]);
	count++;
	return (count);
}
int	ft_putstr_printf(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr_printf("(null)"));
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	printbase(long nbr, int base, char *symbols)
{
	int	count;

	if (nbr < 0)
	{
		write(1, "-", 1);
		return (printbase(-nbr, base, symbols) + 1);
	}
	else if (nbr < base)
	{
		return (ft_putchar_printf(symbols[nbr]));
	}
	else
	{
		count = printbase(nbr / base, base, symbols);
		return (count + printbase(nbr % base, base, symbols));
	}
}