/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:33:41 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/17 22:58:58 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_mlx(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	put_px(t_map *map, mlx_image_t *img, int x, int y, uint32_t color)
{
	int tmp = 0;
	int tx, ty;
	tx = x;
	ty = y;
	while(ty < y + 31)
	{
		tx = x;
		while(tx < x + 31)
		{
			mlx_put_pixel(img, tx, ty, color);
			tx++;
		}
		ty++;
	}
}

void	draw_map(t_map *map, mlx_image_t *img)
{
	int x;
	int y;
	int size;
	uint32_t color;

	x = 0;
	y = 0;
	while (map->map_s[y])
	{
		x = -1;
		size = 0;
		while(map->map_s[y][++x])
		{
			color = 0xFF0000FF;
			if(map->map_s[y][x] == '\t')
				size = size +  (32 * 3);
			if(map->map_s[y][x] == 'N')
				printf("xyyyy = %d and yyyyy = %d\n", x * 32, y * 32);
			if(map->map_s[y][x] == '1')
				put_px(map, img, (x * 32) + size, y * 32, color);
		}
		y++;
	}
}
void	draw_player(t_plr *ply, mlx_image_t *img)
{
	int i;
	int j;

	i = 0;
	while(i < 360)
	{
		j = 0;
		while(j < ply->radius)
		{
			mlx_put_pixel(img, ply->x + j * cos(i * M_PI / 180), ply->y + j * sin(i * M_PI / 180), 0xFF0000FF);
			j++;
		}
		i++;
	}
}

void	info_player(t_plr *p, t_map *m)
{
	int x;
	int y;
	
	y = -1;
	while(m->map_s[++y])
	{
		x = -1;
		while(m->map_s[y][++x])
		{
			if(m->map_s[y][x] == 'N')
			{
				p->x = (x * 32.0);
				p->y = y * 32.0;
			}
		}
	}
	p->direction = 0;
	p->move = 0;
	p->radius = 20.0;
	p->speedmv = 2.0; //pix
	p->retactionspS = 2.0 * (M_PI / 180);
}
mlx_t	*init_mlx(t_map *map)
{
	mlx_t	*mlx;
	mlx_image_t *img;
	t_plr		*plr;

	plr = malloc(sizeof(t_plr) + 1);
	if(!plr)
		exit(99);
	info_player(plr, map);
	printf("w = %d, h = %d\n", map->width_map, map->height_map);
	mlx = mlx_init(map->width_map * 40, map->height_map * 40,"cub3d", true);
	img = mlx_new_image(mlx, map->width_map * 40, map->height_map * 40);
	if(!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		error_mlx();
	draw_map(map, img);
	draw_player(plr, img);
	return (mlx);
}