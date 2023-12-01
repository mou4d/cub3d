/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 04:10:05 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/01 04:47:32 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t get_color(t_map *map, int i, int y)
{
	int x;
	double xwallhit;
	double ywallhit;

	angle_facing(map->wall3d->a_f, map->wall3d->rays_angle[i]);
	xwallhit = map->plr->x + (map->wall3d->small_distance[i] * cos(map->wall3d->rays_angle[i]));
	ywallhit = map->plr->y + (map->wall3d->small_distance[i] * sin(map->wall3d->rays_angle[i]));
	if(map->wall3d->x_vertical[i] == true)
	{
		x = (int)ywallhit % map->size_wall_y_x;
		if(map->wall3d->a_f->r_anglefacingright == true)
			return get_south_pixel_color(map, x, y);
		else
			return get_North_pixel_color(map, x, y);
	}
	else
	{
		x = (int)xwallhit % map->size_wall_y_x;
		if(map->wall3d->a_f->r_anglefacingup == true)	
			return get_East_pixel_color(map, x, y);
		else
			return get_West_pixel_color(map, x, y);
	}
	return 0;
}

void rendering_wall_3d(t_map *map)
{
	int i = 0;
	int x = 0;
	int y = 0;
	int endx = 0;
	int endy = 0;
	double correct_distance;
	double wall_height;
	while(i < map->plr->num_arys)
	{
		double distance_proje_plan = (map->Xwindows_width / 2) / tan(map->plr->fovue_angle / 2);
		correct_distance = map->wall3d->small_distance[i] * cos(map->wall3d->rays_angle[i] - map->plr->retactionangle);
		wall_height = (map->size_wall_y_x / correct_distance) * (distance_proje_plan);
		//printf("dis %f\n", map->wall3d->small_distance[i]);
		y = (map->Ywindows_height / 2) - (wall_height / 2);
		x = i;
		if (y < 0)
			y = 0;
		endx = 1 + i;
		if(endx > map->Xwindows_width)
			endx = map->Xwindows_width;
		endy = (map->Ywindows_height / 2) + (wall_height / 2);
		if(endy > map->Ywindows_height)
			endy = map->Ywindows_height;
		draw_wall_3d(map, x, y, endx, endy, wall_height);
		i++;
	}
}
