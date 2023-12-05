/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 05:11:17 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/06 00:54:06 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_all(t_map *map)
{
	int	i;

	i = ((free(map->ea)), (free(map->c)), (free(map->f)), -1);
	mlx_close_window(map->mlx);
	mlx_close_hook(map->mlx, update_key, map);
	mlx_delete_image(map->mlx, map->img);
	mlx_delete_texture(map->txt->east);
	mlx_delete_texture(map->txt->west);
	mlx_delete_texture(map->txt->north);
	mlx_delete_texture(map->txt->south);
	mlx_terminate(map->mlx);
	(free(map->txt), free(map->plr));
	free(map->wall3d->a_f);
	free(map->wall3d->rays_angle);
	free(map->wall3d->small_distance);
	free(map->wall3d->x_vertical);
	free(map->wall3d);
	free(map->width_map);
	free(map->no);
	free(map->so);
	free(map->we);
	while (map->map_s[++i])
		free(map->map_s[i]);
	free(map->map_s);
	free(map);
}

void	count_and_check(char *types, char l, int *ret)
{
	int	i;

	i = -1;
	while (types[++i] != '\0')
	{
		if (types[i] == l)
		{
			*ret = 0;
			return ;
		}
	}
	if (i != -1)
	{
		types[*ret] = l;
		*ret += 1;
	}
}

int	get_map_index(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		while (map[i] && (map[i] == '\n' | map[i] == '\t' || map[i] == ' '))
			i++;
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W'
			|| map[i] == 'E' || map[i] == 'F' || map[i] == 'C')
		{
			while (map[i] && map[i] != '\n')
				i++;
		}
		else
		{
			while (map[i] && map[i] != '1')
				i++;
			if (map[i] == '1')
				return (i);
		}
		if (map[i])
			i++;
	}
	return (0);
}

void	check_map_newlines(char *map)
{
	int	i;

	i = get_map_index(map);
	while (map[i])
	{
		if (map[i] == '\n')
		{
			i += 1;
			while (map[i] && map[i] == ' ')
				i++;
			if (map[i] == '\n')
				error_("Multiple new lines in a map", NULL);
		}
		i++;
	}
}
