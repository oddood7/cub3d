/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apayen <apayen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:19:45 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/16 12:06:44 by apayen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	free_img(t_ray *ray, t_img *image)
{
	if (image->img)
		mlx_destroy_image(ray->img->mlx, image->img);
	if (image)
		free(image);
}

void	free_ray_value(t_ray *ray)
{
	if (ray->sno)
		free(ray->sno);
	if (ray->sso)
		free(ray->sso);
	if (ray->swe)
		free(ray->swe);
	if (ray->sea)
		free(ray->sea);
	if (ray->move_w)
		free(ray->move_w);
	if (ray->move_s)
		free(ray->move_s);
	if (ray->move_a)
		free(ray->move_a);
	if (ray->move_d)
		free(ray->move_d);
	if (ray->cam_left)
		free(ray->cam_left);
	if (ray->cam_right)
		free(ray->cam_right);
}

int	close_game(t_ray *ray)
{
	printf("GAME OVER\n");
	if (ray->texture1)
		free_img(ray, ray->texture1);
	if (ray->texture2)
		free_img(ray, ray->texture2);
	if (ray->texture3)
		free_img(ray, ray->texture3);
	if (ray->texture4)
		free_img(ray, ray->texture4);
	if (ray->img)
	{
		if (ray->img->img)
			mlx_destroy_image(ray->img->mlx, ray->img->img);
		mlx_destroy_window(ray->img->mlx, ray->img->win);
		mlx_destroy_display(ray->img->mlx);
		if (ray->img->mlx)
			free(ray->img->mlx);
		free(ray->img);
	}
	free_ray_value(ray);
	free_tab(ray->map);
	exit (0);
}
