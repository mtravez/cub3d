#include "cub3d.h"

void	free_2d(char **str, int i)
{
	while (i != 0)
	{
		free(str[i - 1]);
		i--;
	}
	free(str);
}

static int	str_cmp(const char *s1, const char *s2)
{
	const unsigned char	*a;
	const unsigned char	*b;

	a = (const unsigned char *) s1;
	b = (const unsigned char *) s2;
	while (1)
	{
		if (*a == '\0' || *b == '\0' || *a != *b)
			return (*a - *b);
		a++;
		b++;
	}
	return (*a - *b);
}

int	str_eq(const char *s1, const char *s2)
{
	return (str_cmp(s1, s2) == 0);
}