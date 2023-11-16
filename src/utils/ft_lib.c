/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:20:10 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/16 12:18:03 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

static int	ft_nbstr(char const *str, char c)
{
	int	i;
	int	comp;

	i = 0;
	comp = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			comp++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (comp);
}

char	**free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	*ft_dup(char const *str, char c)
{
	char	*dest;
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		size++;
	}
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	char	*word;
	int		i;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_nbstr(s, c) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			word = ft_dup(s, c);
			ret[i] = word;
			if (!ret[i++])
				return (free_all(ret));
			s = s + ft_strlen(word);
		}
	}
	ret[i] = NULL;
	return (ret);
}

char	*ft_strjoinlib(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;
	int		len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (s1 == NULL || s2 == NULL || !str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (free(s1), str);
}
