/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 04:10:05 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/02 23:50:34 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	get_color(t_map *map, int i, int y)
{
	double	xwallhit;
	double	ywallhit;

	angle_facing(map->wall3d->a_f, map->wall3d->rays_angle[i]);
	xwallhit = map->plr->x + (map->wall3d->small_distance[i]
			* cos(map->wall3d->rays_angle[i]));
	ywallhit = map->plr->y + (map->wall3d->small_distance[i]
			* sin(map->wall3d->rays_angle[i]));
	if (map->wall3d->x_vertical[i] == true)
	{
		i = (int)ywallhit % map->size_wall_y_x;
		if (map->wall3d->a_f->r_anglefacingright == true)
			return (get_south_pixel_color(map, i, y));
		else
			return (get_north_pixel_color(map, i, y));
	}
	else
	{
		i = (int)xwallhit % map->size_wall_y_x;
		if (map->wall3d->a_f->r_anglefacingup == true)
			return (get_east_pixel_color(map, i, y));
		else
			return (get_west_pixel_color(map, i, y));
	}
	return (0);
}

void	rendering_wall_3d(t_map *map)
{
	int		i;
	int		x;
	double	correct_distance_or_y;
	double	wall_height;
	double	distance_proje_plan;

	i = ((x = 0), 0);
	distance_proje_plan = (map->xwindows_width / 2)
		/ tan(map->plr->fovue_angle / 2);
	while (i < map->plr->num_arys)
	{
		correct_distance_or_y = map->wall3d->small_distance[i]
			* cos(map->wall3d->rays_angle[i] - map->plr->retactionangle);
		wall_height = (map->size_wall_y_x / correct_distance_or_y)
			* (distance_proje_plan);
		correct_distance_or_y = (map->ywindows_height / 2) - (wall_height / 2);
		x = i;
		if (correct_distance_or_y < 0)
			correct_distance_or_y = 0;
		draw_wall_3d(map, x, correct_distance_or_y, wall_height);
		i++;
	}
}
