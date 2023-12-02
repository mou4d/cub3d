/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 04:09:51 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/02 07:01:01 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	hm_px_bw_pyr_and_wall(t_map *map,double rayangle, int i)
{
	float	xdistance;
	float	ydistance;

	angle_facing(map->wall3d->a_f, rayangle);
	ydistance = find_y_horztouch(map, rayangle, map->wall3d->a_f);
	xdistance = find_x_verticletouch(map, rayangle, map->wall3d->a_f);
	if (ydistance < xdistance + 0.9)
	{
		return (ydistance);
	}
	map->wall3d->x_vertical[i] = true;
	return (xdistance);
}

void	cast_rays(t_map *map)
{
	double	rayangle;
	int		i;

	rayangle = make_angle_postive(map->plr->retactionangle
			- (map->plr->fovue_angle / 2));
	i = 0;
	while (i < map->plr->num_arys)
	{
		map->wall3d->rays_angle[i] = rayangle;
		map->wall3d->x_vertical[i] = false;
		map->wall3d->small_distance[i] = hm_px_bw_pyr_and_wall(map,
				rayangle, i);
		rayangle = make_angle_postive(rayangle + (map->plr->fovue_angle
					/ map->plr->num_arys));
		i++;
	}
}
