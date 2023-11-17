/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:19:18 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/17 13:18:26 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	put_space(char *str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
}

char	**maplistotab(int fd)
{
	char	*s1;
	char	*s2;
	char	**tab;

	s1 = malloc(sizeof(char));
	s1[0] = '\0';
	s2 = "a";
	while (s2)
	{
		s2 = get_next_line(fd);
		if (s2)
			s1 = ft_strjoinlib(s1, s2);
		free(s2);
	}
	close(fd);
	if (map_syntax_check(s1) == -1)
	{
		free(s1);
		return (NULL);
	}
	tab = ft_split(s1, '\n');
	free(s1);
	return (tab);
}

size_t	ft_strlen_tab(char **tab)
{
	size_t	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

char	**map_malloc(char **map)
{
	int		i;
	char	*tmp;
	int		len;
	int		size;

	len = longest_len(map);
	i = 0;
	while (map[i])
	{
		size = len - ft_strlen(map[i]) + 1;
		tmp = malloc(sizeof(char) * size + 1);
		if (!tmp)
			return (NULL);
		put_space(tmp, size);
		map[i] = ft_strjoinlib(map[i], tmp);
		free(tmp);
		i++;
	}
	return (map);
}

double	start_pos(char **tab, int yes)
{
	double		y;
	double		x;
	char		*finder;

	x = 0;
	finder = "NESW";
	while (tab[(int)x])
	{
		y = 0;
		while (tab[(int)x][(int)y])
		{
			if (ft_strchr(finder, tab[(int)x][(int)y]))
			{
				if (yes)
					return (y);
				return (x);
			}
			y++;
		}
		x++;
	}
	return (0);
}
