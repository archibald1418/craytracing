#include "get_next_line.h"

int	ft_strlen_(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = c;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == '\0' && (char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlcpy_(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen_(src));
	while (src[i] != '\0' && (i < dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen_(src));
}

char	*ft_strjoin_(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	newstr = (char *)malloc(sizeof(*newstr) \
		* (ft_strlen_(s1) + ft_strlen_(s2) + 1));
	if (!newstr)
		return (NULL);
	while (s1 != NULL && *s1 != '\0')
	{
		newstr[i] = *s1;
		i++;
		s1++;
	}
	while (s2 != NULL && *s2 != '\0')
	{
		newstr[i] = *s2;
		i++;
		s2++;
	}
	newstr[i] = '\0';
	return (newstr);
}
