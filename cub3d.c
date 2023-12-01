/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:33:48 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/12/01 16:55:05 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **fix_map(char **map)
{
	char	**p;
	int		i;
	int		tmp;

	i = ((tmp = 0) ,0);
	if(!map)
		return NULL;
	while (map[i])
	{
		if (ft_strnstr(map[i], "111", ft_strlen(map[i])) != NULL && map[i][0] != 'C' && map[i][0] != 'F')
			break ;
		i++;
	}
	while (map[i + tmp])
		tmp++;
	p = (char **)malloc((sizeof(char *)) * (tmp + 1));
	tmp = ((i--), 0);
	while (map[++i])
		p[tmp++] = ft_substr(map[i],0 , ft_strlen(map[i]));
	p[tmp] = 0;
	tmp = 0;
	while (map[tmp])
		free(map[tmp++]);
	free(map);
	return (p);
	
}

void start_cub3d(t_map *map)
{
	int wight_big_value;
	map->Xwindows_width = 1200;
	map->Ywindows_height = 700;
	map->size_wall_y_x = 100;
	map->plr = malloc(sizeof(t_plr));
	if(!map->plr)
		exit(99);
	info_player(map->plr, map);
	wight_big_value = strlen_map_big_width_and_height(map->map_s, 'w');
	map->height_map = strlen_map_big_width_and_height(map->map_s, 'h');
	map->width_map = malloc(map->height_map * sizeof(int));
	strlen_wight_pointer(map);
	printf("w = %d, h = %d\n", wight_big_value, map->height_map);
	map->wall3d = malloc(sizeof(t_wall3d));
	map->wall3d->rays_angle = (double *)malloc(sizeof(double) * map->plr->num_arys);
	map->wall3d->small_distance = (double *)malloc(sizeof(double) * map->plr->num_arys);
	map->wall3d->x_vertical = malloc(sizeof(bool) * map->plr->num_arys);
	map->wall3d->a_f = malloc(sizeof(t_angle_facing));
	if(!map->wall3d->a_f)
		exit(33);
	map->mlx = mlx_init(map->Xwindows_width, map->Ywindows_height,"cub3d", true);
	map->img = mlx_new_image(map->mlx, map->Xwindows_width, map->Ywindows_height);
	if(!map->img || mlx_image_to_window(map->mlx, map->img, 0, 0) < 0)
		error_mlx();
	map->txt = malloc(sizeof(t_png));
	map->txt->South = mlx_load_png(map->SO);
	map->txt->East = mlx_load_png(map->EA);
	map->txt->West = mlx_load_png(map->WE);
	map->txt->North = mlx_load_png(map->NO);
	if(!map->txt->North || !map->txt->West || !map->txt->South || !map->txt->East)
		exit(2);
	init_mlx(map);
	mlx_loop_hook(map->mlx, update_key, map);
	mlx_loop(map->mlx);
	free_all(map);
}

void find_tab_change_it_to_sp(char **map)
{
	char *swap;
	int	x;
	int tmp;
	int y;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if(map[y][x] == '\t')
			{
				swap = malloc(ft_strlen(map[y]) + 4 + 1);
				x = -1;
				tmp = 0;
				while(map[y][++x] != '\t')
					swap[x] = map[y][x];
				while(x + tmp < x + 4)
					swap[x + tmp++] = ' ';
				tmp--;
				while(map[y][++x])
					swap[x + tmp] = map[y][x];
				swap[x + tmp] = 0;
				free(map[y]);
				map[y] = swap;
				x = -1;
			}
		}
	}
}

int main(int ac, char **av)
{
	t_map	*map;
	// int		i;
	
	if (ac < 2)
		return (printf("Error\n"));
	// if (ft_strncmp(av[1], ".cub", 4) != 0)
	// 	return (printf("Error\n"));
	map = read_map(av[1]);
	// if (map == NULL)
		// error_("Unkown error occured check your map file.", NULL);
	process_type_ids(map);
	if (process_map(map) != 1)
		return (1);
	find_tab_change_it_to_sp(map->map_s);
	map->map_s = fix_map(map->map_s);
	// i = 0;
	// while(map->map_s[i])
	// {
	// 	printf("%s\n", map->map_s[i]);
	// 	i++;
	// }
	// while(1);
	start_cub3d(map);
	// printf("map processed correctly (y). \n");
	// mlx_terminate(mlx);
	// Create and display the image.
	// printf("#################\n");
	// printf("NO=%s\n", map->NO);
	// printf("SO=%s\n", map->SO);
	// printf("WE=%s\n", map->WE);
	// printf("EA=%s\n", map->EA);
	// printf("F=%s\n", map->F);
	// printf("C=%s\n", map->C);
	// printf("y == %d", map->init_player_y);
	// printf("\n#################END\n");
	// while(1);
	return (0);
}