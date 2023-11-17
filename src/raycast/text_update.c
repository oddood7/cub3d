/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:05:18 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/17 13:36:56 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	update_texture(t_ray *ray, int line_height)
{
	if (ray->side == 0)
		ray->wall_x = ray->posy + ray->dist_to_wall * ray->raydiry;
	else
		ray->wall_x = ray->posx + ray->dist_to_wall * ray->raydirx;
	ray->wall_x -= floor((ray->wall_x));
	ray->texx = (int)(ray->wall_x * 64);
	if (ray->side == 0 && ray->raydirx > 0)
		ray->texx = 64 - ray->texx - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		ray->texx = 64 - ray->texx - 1;
	ray->walk = 1.0 * 64 / line_height;
	ray->tex_pos = \
	(ray->draw_start - HEIGHT / 2 + line_height / 2) * ray->walk;
}

void	get_draw_point(t_ray *ray)
{
	if (ray->side == 0)
		ray->dist_to_wall = (ray->sidedistx - ray->deltadistx);
	else
		ray->dist_to_wall = (ray->sidedisty - ray->deltadisty);
	ray->lineheight = (int)(HEIGHT / ray->dist_to_wall);
	ray->draw_start = -ray->lineheight / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->lineheight / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT || ray->draw_end < 0)
		ray->draw_end = HEIGHT - 1;
}

void	draw_total_frame(t_ray *ray, int x, int y, int lineheight)
{
	while (y < ray->draw_start)
	{
		do_pixels(ray, x, y, get_rgb(ray, 1));
		y++;
	}
	update_texture(ray, lineheight);
	while (y <= ray->draw_end && y >= ray->draw_start)
	{
		ray->texy = (int)ray->tex_pos;
		ray->tex_pos += ray->walk;
		if (ray->side == 0 && ray->raydirx < 0)
			do_pixels(ray, x, y, get_color(ray, ray->texture1));
		else if (ray->side == 0 && ray->raydirx >= 0)
			do_pixels(ray, x, y, get_color(ray, ray->texture2));
		else if (ray->side == 1 && ray->raydiry < 0)
			do_pixels(ray, x, y, get_color(ray, ray->texture3));
		else if (ray->side == 1 && ray->raydiry >= 0)
			do_pixels(ray, x, y, get_color(ray, ray->texture4));
		y++;
	}
	while (y < HEIGHT)
	{
		do_pixels(ray, x, y, get_rgb(ray, 0));
		y++;
	}
}

void	minimap(t_ray *ray, int x, int y)
{
	int	i;
	int	yt;
	int	len;

	yt = 0;
	len = ft_strlen_tab(ray->map);
	while (yt < len)
	{
		i = 0;
		x = 0;
		while (i < ft_strlen(ray->map[yt]))
		{
			if (i == (int)ray->posy && yt == (int)ray->posx)
				do_pixel_mm(ray, x, y, 0xFF66F3);
			else if (ray->map[yt][i] && ray->map[yt][i] == '1')
				do_pixel_mm(ray, x, y, 0xFFFFF1);
			x += 6;
			i++;
		}
		y += 6;
		yt++;
	}
}
