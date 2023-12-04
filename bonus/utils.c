/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:33:41 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/12/04 23:22:44 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	make_angle_postive(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	angle_facing(t_angle_facing *mongol, double rayangle)
{
	if (rayangle > 0 && rayangle < M_PI)
	{
		mongol->r_anglefacingdown = true;
		mongol->r_anglefacingup = false;
	}
	else
	{
		mongol->r_anglefacingup = true;
		mongol->r_anglefacingdown = false;
	}
	if (rayangle < (1.5 * M_PI) && rayangle > M_PI_2)
	{
		mongol->r_anglefacingleft = true;
		mongol->r_anglefacingright = false;
	}
	else
	{
		mongol->r_anglefacingright = true;
		mongol->r_anglefacingleft = false;
	}
}

void	clear_windows(t_map *map)
{
	int			x;
	int			y;
	uint32_t	color;
	uint32_t	color1;
	uint32_t	color2;

	x = -1;
	color1 = (ft_atoi(map->c) << 24
			| (ft_atoi(ft_strchr(map->c, ',') + 1) << 16)
			| (ft_atoi(1 + ft_strrchr((1 + ft_strchr(map->c, ',')), ',')) << 8)
			| (255));
	color2 = ((ft_atoi(map->f) << 24)
			| (ft_atoi(ft_strchr(map->f, ',') + 1) << 16)
			| ft_atoi(1 + ft_strrchr((1 + ft_strchr(map->f, ',')), ',')) << 8
			| (255));
	while (++x < map->xwindows_width)
	{
		color = ((y = -1), color1);
		while (++y < map->ywindows_height)
		{
			if (y > map->ywindows_height / 2)
				color = color2;
			mlx_put_pixel(map->img, x, y, color);
		}
	}
}

void	init_mlx(t_map *map)
{
	int	i;

	i = 0;
	cast_rays(map);
	clear_windows(map);
	rendering_wall_3d(map);
	draw_mini_map(map);
	draw_player(map, map->img);
	while (i < map->plr->num_arys)
	{
		draw_line_direction(map, map->wall3d->rays_angle[i],
			map->wall3d->small_distance[i]);
		i++;
	}
}
