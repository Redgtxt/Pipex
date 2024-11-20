
#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	newstr = (char *)malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!newstr)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	free(s1);
	while (s2[j] != '\0' && s2 != NULL)
	{
		newstr[i++] = s2[j++];
		if (s2[j - 1] == '\n')
			break ;
	}
	newstr[i] = '\0';
	return (newstr);
}

int	flagfunc(char *buffer)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (buffer[j] != '\0')
	{
		if (flag == 1)
			buffer[i++] = buffer[j];
		if (buffer[j] == '\n')
			flag = 1;
		buffer[j++] = '\0';
	}
	return (flag);
}
