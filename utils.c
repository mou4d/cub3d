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

void	put_px(t_map *map, mlx_image_t *img, int x, int y, int how_many)
{
	int tmp = 0;
	int tx, ty;
	tx = x;
	ty = y;
	while(tmp < how_many)
	{
		while(ty < y + 32)
		{
			tx = x;
			while(tx < x + 32)
			{
				mlx_put_pixel(img, ty, tx, 0xFF0000FF);
				tx++;
			}
			ty++;
		}
	}
}
void	drow_map(t_map *map, mlx_image_t *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (map->map_s[y])
	{
		while(map->map_s[y][x])
		{
			if(map->map_s[y][x] == '\t')
				 put_px(map, img, x, y, 4);
			if(map->map_s[y][x] == ' ')
				put_px(map, img, x, y, 1);
			if(map->map_s[y][x] == '0')
				 put_px(map, img, x, y, 4);
		
		}
	}
}

mlx_t	*init_mlx(t_map *map)
{
	mlx_t	*mlx;
	mlx_image_t *img;

	printf("w = %d, h = %d\n", map->width_map, map->height_map);
	mlx = mlx_init(map->width_map * 32, map->height_map * 32,"cub3d", true);
	img = mlx_new_image(mlx, map->width_map * 32, map->height_map * 32);
	if(!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		error_mlx();
	put_pix(map, img);
	return (mlx);
}