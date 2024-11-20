
#include "libft.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];
;
	line = NULL;
	if(BUFFER_SIZE <= 0)
		return NULL;
	while (buffer[0] || (read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		line = ft_strjoin_gnl(line, buffer);
		if (flagfunc(buffer))
			break ;
	}
	return (line);
}

