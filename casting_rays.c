/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 04:09:51 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/01 04:52:00 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double  find_y_horztouch(t_map *map, double rayangle, t_angle_facing *a_f)
{
	int x, y;
	double x_wallhit = 0;
	double y_wallhit = 0;
	double xintercept, yintercept;
	double xstep, ystep;
	yintercept = floor(map->plr->y / map->size_wall_y_x) * map->size_wall_y_x;
	if (a_f->r_anglefacingdown == true)
	    yintercept += map->size_wall_y_x;
	xintercept = map->plr->x + (((yintercept - map->plr->y) )/ tan(rayangle));
	ystep = map->size_wall_y_x;
	if (a_f->r_anglefacingup == true)
	    ystep *= -1;

	xstep = map->size_wall_y_x / tan(rayangle);
	if(a_f->r_anglefacingleft && xstep > 0)
		xstep *= -1;
	if(a_f->r_anglefacingright && xstep < 0)
		xstep *= -1;
	if ((a_f->r_anglefacingleft == true && xstep > 0) || (a_f->r_anglefacingright == true && xstep < 0))
	    xstep *= -1;

	x_wallhit = xintercept;
	y_wallhit = yintercept;

	if(a_f->r_anglefacingup)
		y_wallhit--;
	x = x_wallhit / map->size_wall_y_x;
	y = y_wallhit / map->size_wall_y_x;
	while (x >= 0 && y >= 0 && y < map->height_map &&  x <= map->width_map[y] && y_wallhit >= 0)
	{
	    if (map->map_s[y][x] == '1')
	        break;
		else
		{
	        x_wallhit += xstep;
	        y_wallhit += ystep;
	        x = x_wallhit / map->size_wall_y_x;
	    	y = y_wallhit / map->size_wall_y_x;
	    }
	}
	return calculate_distance(map->plr->x, map->plr->y, x_wallhit, y_wallhit);
}

double find_x_verticletouch(t_map *map, double rayangle, t_angle_facing *a_f)
{
	int x, y;
	double x_wallhit = 0;
	double y_wallhit = 0;
	double xintercept, yintercept;
	double xstep, ystep;

	xintercept = floor(map->plr->x / map->size_wall_y_x) * map->size_wall_y_x;
	if (a_f->r_anglefacingright == true)
	    xintercept += map->size_wall_y_x;
	yintercept = map->plr->y + ((xintercept - map->plr->x)  * tan(rayangle));
	xstep = map->size_wall_y_x;
	if (a_f->r_anglefacingleft  == true)
	    xstep *= -1;

	ystep = map->size_wall_y_x * tan(rayangle);
	if(a_f->r_anglefacingup && ystep > 0)
		ystep *= -1;
	if(a_f->r_anglefacingdown && ystep < 0)
		ystep *= -1;

	x_wallhit = xintercept;
	y_wallhit = yintercept;

	if(a_f->r_anglefacingleft)
		x_wallhit--;
	x = x_wallhit / map->size_wall_y_x;
	y = y_wallhit / map->size_wall_y_x;
	while (x >= 0 && y >= 0 && y < map->height_map &&  x <= map->width_map[y] && y_wallhit >= 0)
	{
	    if (map->map_s[y][x] == '1') {
	        break;
	    }
		else
		{
	        x_wallhit += xstep;
	        y_wallhit += ystep;
	        x = x_wallhit / map->size_wall_y_x;
	    	y = y_wallhit / map->size_wall_y_x;
	    }
	}
	return calculate_distance(map->plr->x, map->plr->y, x_wallhit, y_wallhit);
}


double	hm_px_bw_pyr_and_wall(t_map *map,double rayangle, int i)
{
	double xdistance;
	double ydistance;

	angle_facing(map->wall3d->a_f, rayangle);
	ydistance = find_y_horztouch(map, rayangle, map->wall3d->a_f);
	xdistance = find_x_verticletouch(map, rayangle, map->wall3d->a_f);
	if(ydistance < xdistance)
	{
		return ydistance;
	}
	map->wall3d->x_vertical[i] = true;
	return xdistance;
}

void	cast_rays(t_map *map)
{
	double rayangle;
	rayangle = make_angle_postive(map->plr->retactionangle - (map->plr->fovue_angle / 2));

	int i = 0;
	while(i < map->plr->num_arys)
	{
		map->wall3d->rays_angle[i] = rayangle;
		map->wall3d->x_vertical[i] = false;
		map->wall3d->small_distance[i] = hm_px_bw_pyr_and_wall(map, rayangle, i);
		rayangle = make_angle_postive(rayangle + (map->plr->fovue_angle / map->plr->num_arys));
		i++;
	} 
}
