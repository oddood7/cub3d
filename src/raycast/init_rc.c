/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:20:43 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/15 23:16:53 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	init_dir(t_ray *ray)
{
	if (ray->map[(int)ray->posx][(int)ray->posy] == 'N')
	{
		ray->dirx = -1;
		ray->diry = 0;
		ray->planex = 0;
		ray->planey = 0.66;
	}
	else if (ray->map[(int)ray->posx][(int)ray->posy] == 'S')
	{
		ray->dirx = 1;
		ray->diry = 0;
		ray->planex = 0;
		ray->planey = -0.66;
	}
	init_dir2(ray);
}

void	init_dir2(t_ray *ray)
{
	if (ray->map[(int)ray->posx][(int)ray->posy] == 'W')
	{
		ray->dirx = 0;
		ray->diry = -1;
		ray->planex = -0.66;
		ray->planey = 0;
	}
	else if (ray->map[(int)ray->posx][(int)ray->posy] == 'E')
	{
		ray->dirx = 0;
		ray->diry = 1;
		ray->planex = 0.66;
		ray->planey = 0;
	}
}

void	init_malloc_move(t_ray *ray)
{
	ray->move_w = malloc(sizeof(t_move));
	if (!ray->move_w)
		malloc_err(ray, "Error alloc move_w");
	ray->move_w->key = 119;
	ray->move_w->yes = FALSE;
	ray->move_s = malloc(sizeof(t_move));
	if (!ray->move_s)
		malloc_err(ray, "Error alloc move_s");
	ray->move_s->key = 115;
	ray->move_s->yes = FALSE;
	ray->move_a = malloc(sizeof(t_move));
	if (!ray->move_a)
		malloc_err(ray, "Error alloc move_a");
	ray->move_a->key = 97;
	ray->move_a->yes = FALSE;
	ray->move_d = malloc(sizeof(t_move));
	if (!ray->move_d)
		malloc_err(ray, "Error alloc move_d");
	ray->move_d->key = 100;
	ray->move_d->yes = FALSE;
	init_malloc_move2(ray);
}

void	init_malloc_move2(t_ray *ray)
{
	ray->cam_left = malloc(sizeof(t_move));
	if (!ray->cam_left)
		malloc_err(ray, "Error alloc cam_left");
	ray->cam_left->key = 65363;
	ray->cam_left->yes = FALSE;
	ray->cam_right = malloc(sizeof(t_move));
	if (!ray->cam_right)
		malloc_err(ray, "Error alloc cam_right");
	ray->cam_right->key = 65361;
	ray->cam_right->yes = FALSE;
	ray->cam_mouse_right = 0;
	ray->cam_mouse_left = 0;
}

void	init_ray(t_ray *ray, t_mlx *game)
{
	ray->map = good_map(ray, game, game->map);
	ray->ceiling = game->ceiling;
	ray->floor = game->floor;
	ray->posx = start_pos(ray->map, 0) + 0.5;
	ray->posy = start_pos(ray->map, 1) + 0.5;
	ray->sno = ft_strdup(game->no);
	ray->sso = ft_strdup(game->so);
	ray->sea = ft_strdup(game->ea);
	ray->swe = ft_strdup(game->we);
	free_textures(game);
	ray->texture1 = NULL;
	ray->texture2 = NULL;
	ray->texture3 = NULL;
	ray->texture4 = NULL;
	ray->side = 0;
	ray->mouse_on = 0;
	init_dir(ray);
	init_malloc_move(ray);
}
