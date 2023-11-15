/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:57:33 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/11 12:48:38 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	side_movement(t_ray *ray, int key, double m)
{
	if (key == ray->move_d->key)
	{
		if (ray->map[(int)(ray->posx + ray->planex * m)] \
		[(int)(ray->posy)] != '1')
			ray->posx += ray->planex * m;
		if (ray->map[(int)(ray->posx)] \
		[(int)(ray->posy + ray->planey * m)] != '1')
			ray->posy += ray->planey * m;
	}
	else if (key == ray->move_a->key)
	{
		if (ray->map[(int)(ray->posx - ray->planex * m)] \
		[(int)(ray->posy)] != '1')
			ray->posx -= ray->planex * m;
		if (ray->map[(int)(ray->posx)] \
		[(int)(ray->posy - ray->planey * m)] != '1')
			ray->posy -= ray->planey * m;
	}
}

void	movement(t_ray *ray, int key)
{
	double	m;

	m = 0.025;
	if (key == ray->move_w->key)
	{
		if (ray->map[(int)(ray->posx + ray->dirx * m)][(int)(ray->posy)] != '1')
			ray->posx += ray->dirx * m;
		if (ray->map[(int)(ray->posx)][(int)(ray->posy + ray->diry * m)] != '1')
			ray->posy += ray->diry * m;
	}
	else if (key == ray->move_s->key)
	{
		if (ray->map[(int)(ray->posx - ray->dirx * m)][(int)(ray->posy)] != '1')
			ray->posx -= ray->dirx * m;
		if (ray->map[(int)(ray->posx)][(int)(ray->posy - ray->diry * m)] != '1')
			ray->posy -= ray->diry * m;
	}
	else if (key == ray->move_a->key || key == ray->move_d->key)
		side_movement(ray, key, m);
}

void	cam_movement(t_ray *ray, int key, double rt)
{
	double	oldir;
	double	oldplane;

	if (key == ray->cam_left->key)
	{
		oldir = ray->dirx;
		ray->dirx = ray->dirx * cos(-rt) - ray->diry * sin(-rt);
		ray->diry = oldir * sin(-rt) + ray->diry * cos(-rt);
		oldplane = ray->planex;
		ray->planex = ray->planex * cos(-rt) - ray->planey * sin(-rt);
		ray->planey = oldplane * sin(-rt) + ray->planey * cos(-rt);
	}
	else if (key == ray->cam_right->key)
	{
		oldir = ray->dirx;
		ray->dirx = ray->dirx * cos(rt) - ray->diry * sin(rt);
		ray->diry = oldir * sin(rt) + ray->diry * cos(rt);
		oldplane = ray->planex;
		ray->planex = ray->planex * cos(rt) - ray->planey * sin(rt);
		ray->planey = oldplane * sin(rt) + ray->planey * cos(rt);
	}
}
