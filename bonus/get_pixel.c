/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 02:52:18 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/04 23:46:16 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

uint32_t	get_east_pixel_color(t_map *map, int x, int y)
{
	int	pix;
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0;
	g = 0;
	b = 0;
	a = 0;
	if (x >= 0 && x <= (int)map->txt->east->width && y >= 0
		&& y <= (int)map->txt->east->height)
	{
		pix = ((y * map->txt->east->bytes_per_pixel) * map->txt->east->width
				+ (x * map->txt->east->bytes_per_pixel));
		r = map->txt->east->pixels[pix++];
		g = map->txt->east->pixels[pix++];
		b = map->txt->east->pixels[pix++];
		a = map->txt->east->pixels[pix];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0);
}

uint32_t	get_west_pixel_color(t_map *map, int x, int y)
{
	int	pix;
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0;
	g = 0;
	b = 0;
	a = 0;
	if (x >= 0 && x <= (int)map->txt->west->width
		&& y >= 0 && y <= (int)map->txt->west->height)
	{
		pix = ((y * map->txt->west->bytes_per_pixel) * map->txt->west->width
				+ (x * map->txt->west->bytes_per_pixel));
		r = map->txt->west->pixels[pix++];
		g = map->txt->west->pixels[pix++];
		b = map->txt->west->pixels[pix++];
		a = map->txt->west->pixels[pix];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0);
}

uint32_t	get_south_pixel_color(t_map *map, int x, int y)
{
	int	pix;
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0;
	g = 0;
	b = 0;
	a = 0;
	if (x >= 0 && x <= (int)map->txt->south->width
		&& y >= 0 && y <= (int)map->txt->south->height)
	{
		pix = ((y * map->txt->south->bytes_per_pixel) * map->txt->south->width
				+ (x * map->txt->south->bytes_per_pixel));
		r = map->txt->south->pixels[pix++];
		g = map->txt->south->pixels[pix++];
		b = map->txt->south->pixels[pix++];
		a = map->txt->south->pixels[pix];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0);
}

uint32_t	get_north_pixel_color(t_map *map, int x, int y)
{
	int	pix;
	int	r;
	int	g;
	int	b;
	int	a;

	r = 0;
	g = 0;
	b = 0;
	a = 0;
	if (x >= 0 && x <= (int)map->txt->north->width
		&& y >= 0 && y <= (int)map->txt->north->height)
	{
		pix = ((y * map->txt->north->bytes_per_pixel) * map->txt->north->width
				+ (x * map->txt->north->bytes_per_pixel));
		r = map->txt->north->pixels[pix++];
		g = map->txt->north->pixels[pix++];
		b = map->txt->north->pixels[pix++];
		a = map->txt->north->pixels[pix];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0);
}
