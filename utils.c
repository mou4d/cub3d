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

void	drow_map(t_map *map, mlx_image_t *img)
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
			if(map->map_s[y][x] == '1')
				put_px(map, img, (x * 32) + size, y * 32, color);
		}
		y++;
	}
}

mlx_t	*init_mlx(t_map *map)
{
	mlx_t	*mlx;
	mlx_image_t *img;

	printf("w = %d, h = %d\n", map->width_map, map->height_map);
	mlx = mlx_init(map->width_map * 40, map->height_map * 40,"cub3d", true);
	img = mlx_new_image(mlx, map->width_map * 40, map->height_map * 40);
	if(!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		error_mlx();
	drow_map(map, img);
	return (mlx);
}