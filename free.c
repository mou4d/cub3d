/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 05:11:17 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/01 19:01:55 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(t_map *map)
{
	int	i;

	i = ((free(map->EA)), (free(map->C)), (free(map->F)), -1);
	mlx_terminate(map->mlx);
	mlx_close_hook(map->mlx, update_key, map);
	mlx_delete_image(map->mlx, map->img);
	mlx_delete_texture(map->txt->East);
	mlx_delete_texture(map->txt->West);
	mlx_delete_texture(map->txt->North);
	mlx_delete_texture(map->txt->South);
	free(map->txt);
	free(map->plr);
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
