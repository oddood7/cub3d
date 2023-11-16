/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:53:48 by apayen            #+#    #+#             */
/*   Updated: 2023/11/16 12:11:40 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	map_start(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && j < 6)
	{
		if (!strncmp(&str[i], "NO ", 3) || !strncmp(&str[i], "SO ", 3))
			j++;
		if (!strncmp(&str[i], "EA ", 3) || !strncmp(&str[i], "WE ", 3))
			j++;
		if (!strncmp(&str[i], "F ", 2) || !strncmp(&str[i], "C ", 2))
			j++;
		i++;
	}
	if (j != 6)
	{
		printf("\nError\nMissing textures or colors information\n");
		return (-1);
	}
	while (str[i] && str[i] != '\n')
		i++;
	while (str[i] == '\n')
		i++;
	return (i);
}

int	map_syntax_check(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = map_start(str) - 1;
	while (i > 0 && str[++i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			printf("Error\nEmpty line in map\n");
		if (str[i] == '\n' && str[i + 1] == '\n')
			return (-1);
		if (is_not_valid_char(str[i]))
			return (-1);
		if (ft_isalpha(str[i]))
			j++;
		if (j > 1)
			printf("Error\nTwo starting positions\n");
		if (j > 1)
			return (-1);
	}
	if (j == 0 && i > 0)
		printf("Error\nNo starting position\n");
	if (j == 0 || i < 0)
		return (-1);
	return (0);
}

int	checkclosedrule(char **map, int x, int y)
{
	if ((y == 0 || y == (int)ft_strlen_tab(map) - 1) && (map[y][x] == '0' \
	|| ft_isalpha(map[y][x])))
		return (printf("Error\nMap isn't closed\n"));
	if (x == 0 && map[y][x] == '0')
		return (printf("Error\nMap isn't closed"));
	if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'E' \
	|| map[y][x] == 'W' || map[y][x] == 'S')
	{
		if (y != (int)ft_strlen_tab(map) - 1 && y != 0 && x != 0 \
		&& x != (int)ft_strlen(map[y]) - 1)
		{
			if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
				return (printf("Error\nMap isn't closed\n"));
			if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
				return (printf("Error\nMap isn't closed\n"));
		}
	}
	return (0);
}

int	go_through_map(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (checkclosedrule(map, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	init_map(t_firstmap *firstmap, char *name)
{
	firstmap->fd = open(name, O_RDWR);
	if (firstmap->fd < 0)
	{
		perror(name);
		return (-1);
	}
	firstmap->fmap = maplistotab(firstmap->fd);
	if (firstmap->fmap == NULL)
		return (-1);
	firstmap->map = &(firstmap->fmap[6]);
	firstmap->map = map_malloc(firstmap->map);
	if (!go_through_map(firstmap->map))
		return (-1);
	return (0);
}
