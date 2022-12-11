#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int	ft_countword(char const *s, char c)
{
	int	i;
	int	cw;

	i = 0;
	cw = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			if (s[i] == c || s[i] == '\0')
				cw++;
		}
	}
	return (cw);
}

char	*ft_malloc_word(const char *str, char c, int *start)
{
	char	*word;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str[*start] == c)
		*start += 1;
	while (str[*start + len] != c && str[*start + len] != '\0')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		word[i] = str[*start + i];
		i++;
	}
	*start += len;
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		cw;
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	cw = ft_countword(s, c);
	split = (char **)malloc(sizeof(char *) * (cw + 1));
	if (!split)
		return (NULL);
	while (i < cw)
	{
		split[i] = ft_malloc_word(s, c, &start);
		i++;
	}
	split[i] = NULL;
	return (split);
}

#include <fcntl.h>
#include <unistd.h>
int main(int ac, char **av, char **envp)
{
	int		i;
	char	**split_path;

	i = 0;
	while(envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf("%s\n", envp[i]);
	printf("%s\n", getenv("PATH"));
	// while (envp[i])
	// {
	// 	if (strnstr(envp[i], "PATH=", 5))
	// 		split_path = ft_split(envp[i], ':');
	// 	i++;
	// }
    // i = 0;
    // while (split_path[i])
    //     printf("%s\n", split_path[i++]);

   	// char *s1 = "A";
	// char *str = "Hello how are you";
	// char *find = "are";
	// printf("%s\n", strnstr(str, find, 13));
	// printf("%s\n", strnstr(s1, s1, 2));
    // printf("%d\n", STDOUT_FILENO);
}

