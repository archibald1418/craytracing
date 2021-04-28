#include "minirt.h"

static int		is_in(char const c, char const *set)
{
	size_t i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t		iter_chars(char const *s, char *set, size_t flag)
{
	size_t i;

	i = 0;
	while ((((size_t)is_in(s[i], set) == flag)) && (s[i] != '\0'))
		i++;
	return (i);
}

static size_t		count_words(char const *s, char *set)
{
	size_t flag;
	size_t words;

	flag = 1;
	words = 0;
	while (*s != '\0')
	{
		s += iter_chars(s, set, flag);
		if (flag == 0)
			words++;
		flag = !flag;
	}
	return (words);
}

static char			**fill_arr(char **arr, size_t len, char const *s, char *set)
{
	size_t leni;
	size_t flag;
	size_t i;

	i = 0;
	flag = 1;
	leni = 0;
	while (i < len && *s != '\0')
	{
		leni = iter_chars(s, set, flag);
		if (flag == 0)
		{
			arr[i] = malloc((leni + 1) * sizeof(char));
			if (arr[i] == NULL)
				return ((char**)free_arr((void**)arr, i));
			ft_strlcpy(arr[i], s, leni + 1);
			i++;
		}
		flag = !flag;
		s += leni;
	}
	arr[i] = NULL;
	return (arr);
}

char				**ft_strsplit(char const *s, char *set)
{
	size_t	nwords;
	char	**out;

	out = NULL;
	nwords = 0;
	if (s != NULL)
	{
		nwords = count_words(s, set);
		out = malloc((nwords + 1) * sizeof(char *));
		if (out != NULL)
			out = fill_arr(out, nwords, s, set);
	}
	return (out);
}