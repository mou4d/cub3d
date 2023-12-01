/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:56:50 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/01 04:29:36 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_px(t_map *map, mlx_image_t *img, int x, int y, uint32_t color)
{
	int tx, ty;
	tx = x;
	ty = y;
	while(ty < y + map->size_wall_y_x)
	{
		tx = x;
		while(tx < x + map->size_wall_y_x)
		{
			mlx_put_pixel(img, 0.09 * tx, 0.09 * ty, color);
			tx++;
		}
		ty++;
	}
}

void	draw_mini_map(t_map *map, mlx_image_t *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (map->map_s[y])
	{
		x = -1;
		while(map->map_s[y][++x])
		{
			if(map->map_s[y][x] == '1')
				put_px(map, img, (x * map->size_wall_y_x), y * map->size_wall_y_x, 0xFF0000FF);
			else
				put_px(map, img, (x * map->size_wall_y_x), y * map->size_wall_y_x, 0x0);
		}
		y++;
	}
}

void	draw_line_direction(t_map *map, double ray_angle, double line_px)
{
	double x;
	x = 0;
	while(x < line_px)
	{
		mlx_put_pixel(
				map->img,
				0.09 * (map->plr->x + x * cos(ray_angle)),
				0.09 * (map->plr->y + x * sin(ray_angle)),
				0xa54848
			);
		x++;
	}
}
void	draw_player(t_map *map, mlx_image_t *img)
{
	int x;
	int y;
	t_plr *ply;

	ply = map->plr;
	x = ply->x  - ply->radius;
	while (x <= ply->x + ply->radius)
	{
		y = ply->y - ply->radius;
		while(y <= ply->y + ply->radius)
		{
			if(((x - ply->x) * (x - ply->x)) + ((y - ply->y) * ((y - ply->y))) <= (ply->radius * ply->radius))
				mlx_put_pixel(img, 0.09 * x, 0.09 * y, 0x007258);
			y++;
		}
		x++;
	}
}
void	draw_wall_3d(t_map *map, int startx, int starty, int endx, int endy,double wall_height)
{
	int tmp;
	int color;
	int correctdis;
	while(startx < endx)
	{
		tmp = starty;
		while(tmp < endy)
		{
			correctdis = tmp + (wall_height / 2) - (map->Ywindows_height / 2);
			color = get_color(map, startx , correctdis * (map->txt->North->height / wall_height));
			mlx_put_pixel(map->img, startx, tmp, color);
			tmp++;
		}
		startx++;
	}
}
