/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 23:19:34 by lde-mais          #+#    #+#             */
/*   Updated: 2023/11/17 13:27:30 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

int	game_loop(t_ray *ray)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_delta(ray, x);
		init_sidedist(ray);
		throw_rays(ray);
		get_draw_point(ray);
		draw_total_frame(ray, x, 0, ray->lineheight);
		x++;
	}
	if (ray->mouse_on == 0)
		mlx_mouse_move(ray->img->mlx, ray->img->win, WIDTH / 2, HEIGHT / 2);
	minimap(ray, 0, 0);
	mlx_put_image_to_window(ray->img->mlx, ray->img->win, ray->img->img, 0, 0);
	key_usage(ray);
	return (0);
}

void	assign_mlx_text2(t_ray *ray, int h, int w)
{
	ray->texture3 = ft_calloc(1, sizeof(t_img));
	if (!ray->texture3)
		malloc_err(ray, "Error alloc texture3");
	ray->texture3->img = mlx_xpm_file_to_image(ray->img->mlx, ray->swe, &w, &h);
	if (!ray->texture3->img)
		return (errorsimp("Error texture3->img"));
	ray->texture3->addr = mlx_get_data_addr(ray->texture3->img, \
	&(ray->texture3->bpp), &(ray->texture3->line_len), \
	&(ray->texture3->endian));
	ray->texture4 = ft_calloc(1, sizeof(t_img));
	if (!ray->texture4)
		malloc_err(ray, "Error alloc texture4");
	ray->texture4->img = mlx_xpm_file_to_image(ray->img->mlx, ray->sea, &w, &h);
	if (!ray->texture4->img)
		return (errorsimp("Error texture4->img"));
	ray->texture4->addr = mlx_get_data_addr(ray->texture4->img, \
	&(ray->texture4->bpp), &(ray->texture4->line_len), \
	&(ray->texture4->endian));
}

void	assign_mlx_text(t_ray *ray)
{
	int	h;
	int	w;

	ray->texture1 = ft_calloc(1, sizeof(t_img));
	if (!ray->texture1)
		malloc_err(ray, "Error alloc texture1");
	ray->texture1->img = mlx_xpm_file_to_image(ray->img->mlx, ray->sno, &w, &h);
	if (!ray->texture1->img)
		return (errorsimp("Error texture1->img"));
	ray->texture1->addr = mlx_get_data_addr(ray->texture1->img, \
	&(ray->texture1->bpp), &(ray->texture1->line_len), \
	&(ray->texture1->endian));
	ray->texture2 = ft_calloc(1, sizeof(t_img));
	if (!ray->texture2)
		malloc_err(ray, "Error alloc texture2");
	ray->texture2->img = mlx_xpm_file_to_image(ray->img->mlx, ray->sso, &w, &h);
	if (!ray->texture2->img)
		return (errorsimp("Error texture2->img"));
	ray->texture2->addr = mlx_get_data_addr(ray->texture2->img, \
	&(ray->texture2->bpp), &(ray->texture2->line_len), \
	&(ray->texture2->endian));
	assign_mlx_text2(ray, h, w);
}

int	do_mlx(t_ray *ray)
{
	ray->img = ft_calloc(1, sizeof(t_img));
	if (!ray->img)
		malloc_err(ray, "Error alloc ray->img");
	ray->img->mlx = mlx_init();
	if (!ray->img->mlx)
		return (errorkey("Error mlx_init", 1));
	ray->img->win = mlx_new_window(ray->img->mlx, WIDTH, HEIGHT, "ray3D");
	if (!ray->img->win)
		return (errorkey("Error mlx_win", 1));
	ray->img->img = mlx_new_image(ray->img->mlx, WIDTH, HEIGHT);
	ray->img->addr = mlx_get_data_addr(ray->img->img, &(ray->img->bpp), \
	&(ray->img->line_len), &(ray->img->endian));
	return (0);
}

void	do_raycasting(t_mlx *mlx)
{
	t_ray	ray;

	init_ray(&ray, mlx);
	if (do_mlx(&ray))
		return ;
	assign_mlx_text(&ray);
	mlx_hook(ray.img->win, KeyPress, KeyPressMask, &key_hit, &ray);
	mlx_hook(ray.img->win, MotionNotify, PointerMotionMask, &mouse_move, &ray);
	mlx_hook(ray.img->win, KeyRelease, KeyReleaseMask, &key_release, &ray);
	mlx_hook(ray.img->win, DestroyNotify, 0, &close_game, &ray);
	if (ray.mouse_on == 0)
		mlx_mouse_hide(ray.img->mlx, ray.img->win);
	mlx_loop_hook(ray.img->mlx, &game_loop, &ray);
	mlx_loop(ray.img->mlx);
}
