/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:37:04 by apayen            #+#    #+#             */
/*   Updated: 2023/11/16 13:45:56 by apayen           ###   ########.fr       */
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
