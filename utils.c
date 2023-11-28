/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:33:41 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/28 19:12:31 by wzakkabi         ###   ########.fr       */
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

double	make_angle_postive(double angle)
{
	angle =  fmod(angle , (2 * M_PI));
	if(angle < 0)
		angle = (2 * M_PI) + angle;
	return angle;
}

double calculate_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void	angle_facing(t_angle_facing *mongol, double rayangle)
{
	if (rayangle > 0 && rayangle < M_PI) {
	    mongol->r_anglefacingdown = true;
	    mongol->r_anglefacingup = false;
	}
	else
	{
	    mongol->r_anglefacingup = true;
	    mongol->r_anglefacingdown = false;
	}

	if (rayangle < (1.5 * M_PI) && rayangle > M_PI_2) {
	    mongol->r_anglefacingleft = true;
	    mongol->r_anglefacingright = false;
	}
	else
	{
	    mongol->r_anglefacingright = true;
	    mongol->r_anglefacingleft = false;
	}
}

double  find_y_horztouch(t_map *map, double rayangle, t_angle_facing *a_f)
{
	int x, y;
	double x_wallhit = 0;
	double y_wallhit = 0;
	double distance = 0;
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
	double distance = 0;
	double xintercept, yintercept;
	double xstep, ystep;
	bool hit_or_not;

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
	hit_or_not = false;
	while (x >= 0 && y >= 0 && y < map->height_map &&  x <= map->width_map[y] && y_wallhit >= 0)
	{
	    if (map->map_s[y][x] == '1') {
			hit_or_not = true;
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

double	hm_px_bw_pyr_and_wall(t_map *map,double rayangle)
{
	int x, y;
	double xdistance;
	double ydistance;
	t_angle_facing  *a_f;
	a_f = malloc(sizeof(t_angle_facing));
	if(!a_f)
		exit(33);
	angle_facing(a_f, rayangle);
	ydistance = find_y_horztouch(map, rayangle, a_f);
	xdistance = find_x_verticletouch(map, rayangle, a_f);
	if(ydistance < xdistance)
		return ydistance;
	else
		return xdistance;
}

void	cast_rays(t_map *map)
{
	double rayangle;
	int px_line;
	rayangle = make_angle_postive(map->plr->retactionangle - (map->plr->fovue_angle / 2));

	int i = 0;
	while(i < map->plr->num_arys)
	{
		map->wall3d->rays_angle[i] = rayangle;
		map->wall3d->small_distance[i] = hm_px_bw_pyr_and_wall(map, rayangle);
		rayangle = make_angle_postive(rayangle + (map->plr->fovue_angle / map->plr->num_arys));
		i++;
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

void	clear_windows(t_map *map)
{
	int x;
	int y;
	x = 0;
	while(x < map->Xwindows_width)
	{
		y = 0;
		while (y < map->Ywindows_height)
		{
			mlx_put_pixel(map->img, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

void	draw_wall_3d(t_map *map, int startx, int starty, int endx, int endy)
{
	int tmp;
	while(startx < endx)
	{
		tmp = starty;
		while(tmp < endy)
		{
			mlx_put_pixel(map->img, startx, tmp, 0x007258);
			tmp++;
		}
		startx++;
	}
}

void wall_3d(t_map *map)
{
	int i = 0;
	int x = 0;
	int y = 0;
	int endx = 0;
	int endy = 0;
	double wall_height;
	while(i < map->plr->num_arys)
	{
		double distance_proje_plan = (map->Xwindows_width / 2) / tan(map->plr->fovue_angle / 2);
		wall_height = (map->size_wall_y_x / map->wall3d->small_distance[i]) * (distance_proje_plan);
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
		// printf("angle == %f, wall_ == %f\n", map->wall3d->small_distance[i], wall_height);
		draw_wall_3d(map, x, y, endx, endy);
		i++;
	}
}

void	init_mlx(t_map *map)
{
	int i = 0;
	cast_rays(map);
	clear_windows(map);
	wall_3d(map);
	draw_mini_map(map, map->img);
	draw_player(map, map->img);
	while(i < map->plr->num_arys)
	{
		draw_line_direction(map, map->wall3d->rays_angle[i], map->wall3d->small_distance[i]);
		i++;
	}
}