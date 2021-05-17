#include "get_next_line.h"

static int	fill_data_buf(int fd, char **data_buf)
{
	char	*buf;
	char	*old_data_buf;
	int		num_of_read_bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(buf))
		return (-1);
	num_of_read_bytes = read(fd, buf, BUFFER_SIZE);
	if (num_of_read_bytes == -1)
	{
		free(buf);
		return (-1);
	}
	buf[num_of_read_bytes] = '\0';
	old_data_buf = *data_buf;
	*data_buf = ft_strjoin_(*data_buf, buf);
	if (!*data_buf)
		return (-1);
	free(old_data_buf);
	free(buf);
	return (num_of_read_bytes);
}

static int	check_result_of_read(int n_bytes, char **data_buf, char **line)
{
	if (n_bytes == -1)
	{
		free(*data_buf);
		*data_buf = 0;
		return (-1);
	}
	if (n_bytes == 0)
	{
		*line = ft_strjoin_(*data_buf, 0);
		if (!*line)
			return (-1);
		free(*data_buf);
		*data_buf = 0;
		return (0);
	}
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	char		*nl_founder;
	static char	*data_buf;
	int			num_of_read_bytes;

	if (!line || BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) == -1)
		return (-1);
	nl_founder = ft_strchr_(data_buf, '\n');
	while (!(nl_founder))
	{
		num_of_read_bytes = fill_data_buf(fd, &data_buf);
		if (num_of_read_bytes <= 0)
			return (check_result_of_read(num_of_read_bytes, &data_buf, line));
		nl_founder = ft_strchr_(data_buf, '\n');
	}
	*nl_founder = '\0';
	nl_founder++;
	*line = ft_strjoin_(0, data_buf);
	if (!*line)
		return (-1);
	ft_strlcpy_(data_buf, nl_founder, ft_strlen_(nl_founder) + 1);
	return (1);
}
