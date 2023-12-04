/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 05:11:17 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/04 15:37:39 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_map *map)
{
	int	i;

	i = ((free(map->EA)), (free(map->C)), (free(map->F)), -1);
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
	free(map->NO);
	free(map->SO);
	free(map->WE);
	while (map->map_s[++i])
		free(map->map_s[i]);
	free(map->map_s);
	free(map);
}
