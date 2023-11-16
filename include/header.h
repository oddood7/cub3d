/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:28:33 by apayen            #+#    #+#             */
/*   Updated: 2023/11/16 18:58:45 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_firstmap
{
	char	**fmap;
	int		fd;
	int		height;
	int		width;
	char	**map;
}			t_firstmap;

typedef struct s_move
{
	int	yes;
	int	key;
}				t_move;

typedef struct s_img
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_color
{
	int		red;
	int		green;
	int		blue;
}			t_color;

typedef struct s_mlx
{
	t_firstmap		*firstmap;
	char			**map;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	struct s_color	floor;
	struct s_color	ceiling;
}					t_mlx;

typedef struct s_ray
{
	char		**map;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		dist_to_wall;
	int			lineheight;
	int			draw_start;
	int			draw_end;
	double		camerax;
	double		wall_x;
	int			texx;
	int			texy;
	double		tex_pos;
	double		walk;
	int			mouse_x;
	int			mouse_on;
	int			cam_mouse_right;
	int			cam_mouse_left;
	t_color		ceiling;
	t_color		floor;
	t_img		*img;
	t_img		*texture1;
	t_img		*texture2;
	t_img		*texture3;
	t_img		*texture4;
	char		*sno;
	char		*sso;
	char		*swe;
	char		*sea;
	t_mlx		*game;
	t_move		*move;
	t_move		*move_w;
	t_move		*move_s;
	t_move		*move_a;
	t_move		*move_d;
	t_move		*cam_right;
	t_move		*cam_left;
}				t_ray;

// parsing/colors.c
int					get_color(t_ray *ray, t_img *texture);
int					floor_ceiling_color(t_mlx *game, char *str);
void				do_colors(t_mlx *game, char **tab, char c, char *str);
void				check_color_syn(t_mlx *game, char **tab);
void				check_colors(t_mlx *game, t_color colors, char **tab);
// parsing/drawing.c
int					texture_files(t_mlx *game);
int					init_drawings(t_mlx *game, char **map);
int					do_drawings2(t_mlx *game, char *str, int i);
int					do_drawings(t_mlx *game, char *str);
// parsing/graphic_utils.c
void				do_pixels(t_ray *ray, int x, int y, int color);
int					get_rgb(t_ray *ray, int ok);
// parsing/parsing_utils.c
void				put_space(char *str, int size);
char				**maplistotab(int fd);
size_t				ft_strlen_tab(char **tab);
char				**map_malloc(char **map);
double				start_pos(char **tab, int yes);
// parsing/parsing.c
void				init(t_ray *ray, t_mlx *game);
int					cub_check(char *s);
int					args_errors(int argc, char *av[]);
int					init_game(t_ray *ray, t_mlx *game, char *name);
int					parsing(t_ray *ray, t_mlx *game, int argc, char **argv);
// parsing/parsingmap.c
int					map_start(char *str);
int					map_syntax_check(char *str);
int					checkclosedrule(char **map, int x, int y);
int					go_through_map(char **map);
int					init_map(t_firstmap *firstmap, char *name);
// raycast/all.c
int					game_loop(t_ray *ray);
void				assign_mlx_text(t_ray *ray);
void				assign_mlx_text2(t_ray *ray, int h, int w);
int					do_mlx(t_ray *ray);
void				do_raycasting(t_mlx *mlx);
// raycast/end.c
void				free_img(t_ray *ray, t_img *image);
void				free_ray_value(t_ray *ray);
int					close_game(t_ray *ray);
// raycast/init_rc.c
void				init_dir(t_ray *ray);
void				init_dir2(t_ray *ray);
void				init_malloc_move(t_ray *ray);
void				init_malloc_move2(t_ray *ray);
void				init_ray(t_ray *ray, t_mlx *game);
// raycast/keypress.c
int					mouse_move(int x, int y, t_ray *ray);
int					key_hit(int key, t_ray *ray);
int					key_release(int key, t_ray *ray);
void				key_usage(t_ray *ray);
// raycast/movement.c
void				side_movement(t_ray *ray, int key, double m);
void				movement(t_ray *ray, int key);
void				cam_movement(t_ray *ray, int key, double rt);
// raycast/raycast.c
float				ft_floatabs(float i);
void				init_delta(t_ray *ray, int x);
void				init_sidedist(t_ray *ray);
void				throw_rays(t_ray *ray);
// raycast/text_update.c
void				update_texture(t_ray *ray, int line_height);
void				get_draw_point(t_ray *ray);
void				draw_total_frame(t_ray *ray, int x, int y, int lineheight);
// utils/ft_lib.c
char				**free_all(char **tab);
char				**ft_split(char const *s, char c);
char				*ft_strjoinlib(char *s1, char *s2);
// utils/ft_lib2.c
char				*ft_strdup(const char *s);
char				*ft_strtrim(const char *s1, const char *set);

// utils/get_next_line_utils.c
int					ft_checknl(char *str);
int					ft_strlen(const char *s);
char				*ft_strjoin(char *s1, char *s2, int b, char *buffer);
char				*ft_substr(char *s, int start, int len);
// utils/get_next_line.c
char				*ft_checkread(int fd, char *buffer, char *line, int *b);
void				ft_cleanbuffer(char *buffer);
char				*get_next_line(int fd);
// utils/utils.c
int					ft_strncmp(char *s1, char *s2, int n);
int					ft_atoi(char *nptr);
void				malloc_err(t_ray *ray, char *str);
void				errorsimp(char *str);
int					errorkey(char *str, int key);
// utils/utils2.c
void				free_tab(char **tab);
int					is_not_valid_char(char c);
void				free_textures(t_mlx *game);
int					longest_len(char **map);
char				**good_map(t_ray *ray, t_mlx *game, char **old);
// utils/utils3.c
void				check_str(t_mlx *game, char *str, char **tab);
int					too_many_infos(char *str);
void				init_texture_security(t_ray *ray, t_mlx *game);

#endif
