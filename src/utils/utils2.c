/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:21:46 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/17 18:35:05 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	is_not_valid_char(char c)
{
	if (c == ' ' || c == '\n' || c == '0' || c == '1')
		return (0);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (0);
	printf("Error\nMap has invalid char: '%c'\n", c);
	return (1);
}

void	free_textures(t_mlx *game)
{
	if (game->no)
		free(game->no);
	if (game->ea)
		free(game->ea);
	if (game->so)
		free(game->so);
	if (game->we)
		free(game->we);
}

int	longest_len(char **map)
{
	long unsigned int	len;
	int					i;

	i = 0;
	len = ft_strlen(map[i]);
	while (map[i])
	{
		if ((long unsigned int)ft_strlen(map[i]) > len)
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}

char	**good_map(t_ray *ray, t_mlx *game, char **old)
{
	int		i;
	char	**tab;

	i = 0;
	while (old[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
	{
		free_tab(game->firstmap->fmap);
		free(game->firstmap);
		malloc_err(ray, "good map but you broke malloc :(");
	}
	i = 0;
	while (old[i])
	{
		tab[i] = ft_strdup(old[i]);
		i++;
	}
	tab[i] = 0;
	free_tab(game->firstmap->fmap);
	free(game->firstmap);
	return (tab);
}
