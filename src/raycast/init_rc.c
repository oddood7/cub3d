/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:20:43 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/17 18:46:48 by lde-mais         ###   ########.fr       */
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

t_move	*create_move(t_ray *ray, int key)
{
	t_move	*move;

	move = malloc(sizeof(t_move));
	if (!move)
	{
		malloc_err(ray, "Error in malloc");
		return (NULL);
	}
	move->key = key;
	move->yes = FALSE;
	return (move);
}

void	init_malloc_move(t_ray *ray)
{
	ray->move_w = create_move(ray, 119);
	if (!ray->move_w)
		return ;
	ray->move_s = create_move(ray, 115);
	if (!ray->move_s)
		return ;
	ray->move_a = create_move(ray, 97);
	if (!ray->move_a)
		return ;
	ray->move_d = create_move(ray, 100);
	if (!ray->move_d)
		return ;
	ray->cam_left = create_move(ray, 65363);
	if (!ray->cam_left)
		return ;
	ray->cam_right = create_move(ray, 65361);
	if (!ray->cam_right)
		return ;
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
	init_texture_security(ray, game);
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
