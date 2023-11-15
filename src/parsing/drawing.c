/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:11:32 by apayen            #+#    #+#             */
/*   Updated: 2023/11/15 13:30:29 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	texture_files(t_mlx *game)
{
	if (access(game->no, R_OK))
	{
		perror(game->no);
		return (-1);
	}
	if (access(game->so, R_OK))
	{
		perror(game->so);
		return (-1);
	}
	if (access(game->ea, R_OK))
	{
		perror(game->ea);
		return (-1);
	}
	if (access(game->we, R_OK))
	{
		perror(game->we);
		return (-1);
	}
	return (0);
}

int	init_drawings(t_mlx *game, char **map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!do_drawings(game, map[i]))
		{
			printf("Error\nInvalid textures\n%s\n", map[i]);
			return (0);
		}
		i++;
	}
	while (i < 6)
	{
		if (!floor_ceiling_color(game, map[i]))
		{
			printf("Error\nInvalid colors\n%s\n", map[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	do_drawings2(t_mlx *game, char *str, int i)
{
	char	*s1;

	if (!ft_strncmp(&str[i], "SO ", 3))
	{
		i += 3;
		while (str[i] == ' ')
			i++;
		s1 = ft_strtrim(&str[i], " ");
		game->so = s1;
		return (1);
	}
	else if (!ft_strncmp(&str[i], "WE ", 3))
	{
		i += 3;
		while (str[i] == ' ')
			i++;
		s1 = ft_strtrim(&str[i], " ");
		game->we = s1;
		return (1);
	}
	else
		return (0);
}

int	do_drawings(t_mlx *game, char *str)
{
	int		i;
	char	*s1;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!ft_strncmp(&str[i], "NO ", 3))
	{
		i += 3;
		while (str[i] == ' ')
			i++;
		s1 = ft_strtrim(&str[i], " ");
		game->no = s1;
		return (1);
	}
	else if (!ft_strncmp(&str[i], "EA ", 3))
	{
		i += 3;
		while (str[i] == ' ')
			i++;
		s1 = ft_strtrim(&str[i], " ");
		game->ea = s1;
		return (1);
	}
	return (do_drawings2(game, str, i));
}
