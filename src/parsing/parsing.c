/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mais <lde-mais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:01:14 by apayen            #+#    #+#             */
/*   Updated: 2023/11/15 23:16:20 by lde-mais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header.h"

void	init(struct s_mlx *game)
{
	game->map = NULL;
	game->firstmap = malloc(sizeof(t_firstmap));
	game->firstmap->fmap = NULL;
	game->firstmap->height = 0;
	game->firstmap->width = 0;
	game->no = NULL;
	game->so = NULL;
	game->ea = NULL;
	game->we = NULL;
}

int	cub_check(char *s)
{
	int		len;
	int		i;
	char	*cub;

	cub = ".cub";
	len = ft_strlen(s) - 1;
	i = 3;
	while (i >= 0)
	{
		if (cub[i] != s[len])
			return (0);
		i--;
		len--;
	}
	return (1);
}

int	args_errors(int argc, char *av[])
{
	int	fd;

	if (argc == 1 || argc > 2)
		return (printf("Error\nInvalid number of arguments\n"));
	if (!cub_check(av[1]))
		return (printf("Error\n%s isn't a .cub file\n", av[1]));
	fd = open(av[1], O_DIRECTORY);
	if (fd != -1)
		return (printf("Error\n%s is a directory\n", av[1]));
	fd = open(av[1], O_RDONLY);
	if ((fd < 0))
	{
		perror(av[1]);
		return (-1);
	}
	close(fd);
	return (0);
}

int	init_game(t_mlx *game, char *name)
{
	init(game);
	if (init_map(game->firstmap, name) == -1)
	{
		free_tab(game->firstmap->fmap);
		free(game->firstmap);
		return (-1);
	}
	game->map = game->firstmap->map;
	if (!init_drawings(game, game->firstmap->fmap))
	{
		free_textures(game);
		free_tab(game->firstmap->fmap);
		free(game->firstmap);
		return (-1);
	}
	return (0);
}

int	parsing(struct s_mlx *game, int argc, char **argv)
{
	if (args_errors(argc, argv) != 0)
		return (-1);
	if (init_game(game, argv[1]) == -1)
		return (-1);
	if (texture_files(game) == -1)
	{
		free_textures(game);
		free_tab(game->firstmap->fmap);
		free(game->firstmap);
		return (-1);
	}
	return (0);
}
