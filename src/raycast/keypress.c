/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:19:53 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/15 23:19:56 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	mouse_move(int x, int y, t_ray *ray)
{
	int	old_x;

	(void)y;
	ray->mouse_x = WIDTH / 2;
	old_x = ray->mouse_x;
	ray->mouse_x = x;
	if (ray->mouse_x > old_x)
		ray->cam_mouse_right = TRUE;
	else if (ray->mouse_x < old_x)
		ray->cam_mouse_left = TRUE;
	else
	{
		ray->cam_mouse_left = FALSE;
		ray->cam_mouse_right = FALSE;
	}
	return (0);
}

int	key_hit(int key, t_ray *ray)
{
	if (key == XK_Escape)
		close_game(ray);
	if (key == 119)
		ray->move_w->yes = TRUE;
	if (key == 115)
		ray->move_s->yes = TRUE;
	if (key == 97)
		ray->move_a->yes = TRUE;
	if (key == 100)
		ray->move_d->yes = TRUE;
	if (key == 65363)
		ray->cam_left->yes = TRUE;
	if (key == 65361)
		ray->cam_right->yes = TRUE;
	if (key == XK_c)
		ray->mouse_on = 1;
	if (key == XK_v)
		ray->mouse_on = 0;
	return (0);
}

int	key_release(int key, t_ray *ray)
{
	if (key == 119)
		ray->move_w->yes = FALSE;
	if (key == 115)
		ray->move_s->yes = FALSE;
	if (key == 97)
		ray->move_a->yes = FALSE;
	if (key == 100)
		ray->move_d->yes = FALSE;
	if (key == 65363)
		ray->cam_left->yes = FALSE;
	if (key == 65361)
		ray->cam_right->yes = FALSE;
	return (0);
}

void	key_usage(t_ray *ray)
{
	if (ray->move_w->yes == TRUE)
		movement(ray, 119);
	if (ray->move_s->yes == TRUE)
		movement(ray, 115);
	if (ray->move_a->yes == TRUE)
		movement(ray, 97);
	if (ray->move_d->yes == TRUE)
		movement(ray, 100);
	if (ray->cam_left->yes == TRUE)
		cam_movement(ray, 65363, 0.02);
	if (ray->cam_right->yes == TRUE)
		cam_movement(ray, 65361, 0.02);
	if (ray->cam_mouse_left == TRUE && ray->mouse_on == 0)
		cam_movement(ray, 65361, 0.02);
	if (ray->cam_mouse_right == TRUE && ray->mouse_on == 0)
		cam_movement(ray, 65363, 0.02);
	return ;
}
