#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
char	*ft_strchr_(const char *s, int c);
char	*ft_strjoin_(char const *s1, char const *s2);
size_t	ft_strlcpy_(char *dst, const char *src, size_t dstsize);
int		ft_strlen_(const char *s);

#endif
