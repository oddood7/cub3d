/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:29:53 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 13:28:51 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	do_pixels(t_ray *ray, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || y < 0 || y > HEIGHT - 1 || x > WIDTH - 1)
		return ;
	dest = ray->img->addr + (y * ray->img->line_len) + x * (ray->img->bpp \
	/ 8);
	*(int *)dest = color;
}

void	do_pixel_mm(t_ray *ray, int x, int y, int color)
{
	int	tmpx;
	int	tmpy;

	tmpx = x;
	tmpy = y;
	while (y < (tmpy + 6))
	{
		x = tmpx;
		while (x < (tmpx + 6))
		{
			do_pixels(ray, x, y, color);
			x++;
		}
		y++;
	}
}

int	get_rgb(t_ray *ray, int ok)
{
	int	color;

	if (ok)
		color = ((ray->ceiling.red & 0x0ff) << 16) \
		|((ray->ceiling.green & 0x0ff) << 8) \
		|(ray->ceiling.blue & 0x0ff);
	else
		color = ((ray->floor.red & 0x0ff) << 16) \
		|((ray->floor.green & 0x0ff) << 8) \
		|(ray->floor.blue & 0x0ff);
	return (color);
}
