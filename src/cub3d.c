/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:20:15 by apayen            #+#    #+#             */
/*   Updated: 2023/11/17 08:50:23 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

int	main(int argc, char **argv)
{
	struct s_mlx	game;
	struct s_ray	ray;

	if (parsing(&ray, &game, argc, argv) == -1)
		return (0);
	do_raycasting(&game);
	return (0);
}
