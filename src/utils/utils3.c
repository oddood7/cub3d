/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:37:04 by apayen            #+#    #+#             */
/*   Updated: 2023/11/16 18:43:05 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	too_many_infos(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			j++;
		if (j == 2)
		{
			i++;
			while (str[i] >= '0' && str[i] <= '9')
				i++;
			if (str[i] != '\0' && str[i] != '\n')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

void	check_str(t_mlx *game, char *str, char **tab)
{
	if (too_many_infos(str) == 1)
	{
		printf("Error\ntoo many informations in colors : %s\n", str);
		free(game->so);
		free(game->we);
		free(game->ea);
		free(game->no);
		free_tab(tab);
		free_tab(game->firstmap->fmap);
		free(game->firstmap);
		exit(1);
	}
}

void	init_texture_security(t_ray *ray, t_mlx *game)
{
	ray->sno = ft_strdup(game->no);
	if (!ray->sno)
		malloc_err(ray, "Error allocating ray->sno");
	ray->sso = ft_strdup(game->so);
	if (!ray->sso)
		malloc_err(ray, "Error allocating ray->sso");
	ray->sea = ft_strdup(game->ea);
	if (!ray->sea)
		malloc_err(ray, "Error allocating ray->sea");
	ray->swe = ft_strdup(game->we);
	if (!ray->swe)
		malloc_err(ray, "Error allocating ray->swe");
}
