/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:03:32 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/15 23:15:23 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

float	ft_floatabs(float i)
{
	if (i < 0)
		return (i *= -1);
	return (i);
}

void	init_delta(t_ray *ray, int x)
{
	ray->camerax = 2 * x / (double)WIDTH - 1;
	ray->raydirx = ray->dirx + ray->planex * ray->camerax;
	ray->raydiry = ray->diry + ray->planey * ray->camerax;
	if (ray->raydirx != 0)
		ray->deltadistx = ft_floatabs(1 / ray->raydirx);
	else
		ray->deltadistx = 1e30;		
	if (ray->raydiry != 0)
		ray->deltadisty = ft_floatabs(1 / ray->raydiry);
	else
		ray->deltadisty = 1e30;
}

void	init_sidedist(t_ray *ray)
{
	ray->mapx = (int)ray->posx;
	ray->mapy = (int)ray->posy;
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (ray->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1 - ray->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (ray->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1 - ray->posy) * ray->deltadisty;
	}
}

void	throw_rays(t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (ray->map[ray->mapx][ray->mapy] == '1')
			ray->hit = 1;
	}
	return ;
}
