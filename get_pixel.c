/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 02:52:18 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/02 22:21:15 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (x >= 0 && x <= (int)map->txt->East->width && y >= 0
		&& y <= (int)map->txt->East->height)
	{
		pix = ((y * map->txt->East->bytes_per_pixel) * map->txt->East->width
				+ (x * map->txt->East->bytes_per_pixel));
		r = map->txt->East->pixels[pix++];
		g = map->txt->East->pixels[pix++];
		b = map->txt->East->pixels[pix++];
		a = map->txt->East->pixels[pix];
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
	if (x >= 0 && x <= (int)map->txt->West->width
		&& y >= 0 && y <= (int)map->txt->West->height)
	{
		pix = ((y * map->txt->West->bytes_per_pixel) * map->txt->West->width
				+ (x * map->txt->West->bytes_per_pixel));
		r = map->txt->West->pixels[pix++];
		g = map->txt->West->pixels[pix++];
		b = map->txt->West->pixels[pix++];
		a = map->txt->West->pixels[pix];
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
	if (x >= 0 && x <= (int)map->txt->South->width
		&& y >= 0 && y <= (int)map->txt->South->height)
	{
		pix = ((y * map->txt->South->bytes_per_pixel) * map->txt->South->width
				+ (x * map->txt->South->bytes_per_pixel));
		r = map->txt->South->pixels[pix++];
		g = map->txt->South->pixels[pix++];
		b = map->txt->South->pixels[pix++];
		a = map->txt->South->pixels[pix];
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
	if (x >= 0 && x <= (int)map->txt->North->width
		&& y >= 0 && y <= (int)map->txt->North->height)
	{
		pix = ((y * map->txt->North->bytes_per_pixel) * map->txt->North->width
				+ (x * map->txt->North->bytes_per_pixel));
		r = map->txt->North->pixels[pix++];
		g = map->txt->North->pixels[pix++];
		b = map->txt->North->pixels[pix++];
		a = map->txt->North->pixels[pix];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0);
}
