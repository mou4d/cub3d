/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 05:11:17 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/04 23:22:02 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
