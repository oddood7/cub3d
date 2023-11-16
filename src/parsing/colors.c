/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:19:04 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/16 13:44:30 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	get_color(t_ray *ray, t_img *texture)
{
	char	*dst;

	if (ray->texx < 0 || ray->texy < 0 || ray->texy > HEIGHT - 1 \
	|| ray->texx > WIDTH - 1)
		return (0);
	dst = texture->addr + (ray->texy * texture->line_len + ray->texx \
	* (texture->bpp / 8));
	return (*(int *)dst);
}

void	check_colors(t_mlx *game, t_color colors, char **tab)
{
	if (colors.red < 0 || colors.red > 255 || colors.green < 0 \
	|| colors.green > 255 || colors.blue < 0 || colors.blue > 255)
	{
		printf("Error\nInvalid color value\n");
		free_textures(game);
		free_tab(game->firstmap->fmap);
		free(game->firstmap);
		free_tab(tab);
		exit (1);
	}
}

void	check_color_syn(t_mlx *game, char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			while (tab[i][j] == ' ' || tab[i][j] == '\t')
				j++;
			if (!ft_isdigit(tab[i][j]))
			{
				printf("Error\nnon digit character in colors : \
				%c\n", tab[i][j]);
				free_tab(tab);
				free_tab(game->firstmap->fmap);
				free(game->firstmap);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	do_colors(t_mlx *game, char **tab, char c, char *str)
{
	check_str(game, str, tab);
	if (c == 'C')
	{
		game->ceiling.red = ft_atoi(tab[0]);
		game->ceiling.green = ft_atoi(tab[1]);
		game->ceiling.blue = ft_atoi(tab[2]);
		check_colors(game, game->ceiling, tab);
	}
	if (c == 'F')
	{
		game->floor.red = ft_atoi(tab[0]);
		game->floor.green = ft_atoi(tab[1]);
		game->floor.blue = ft_atoi(tab[2]);
		check_colors(game, game->floor, tab);
	}
}

int	floor_ceiling_color(t_mlx *game, char *str)
{
	int		i;
	char	**tab;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!strncmp(&str[i], "C ", 2))
	{
		i += 2;
		tab = ft_split(&str[i], ',');
		do_colors(game, tab, 'C', &str[i]);
		check_color_syn(game, tab);
		free_tab(tab);
		return (1);
	}
	if (!strncmp(&str[i], "F ", 2))
	{
		i += 2;
		tab = ft_split(&str[i], ',');
		do_colors(game, tab, 'F', &str[i]);
		check_color_syn(game, tab);
		free_tab(tab);
		return (1);
	}
	return (0);
}
