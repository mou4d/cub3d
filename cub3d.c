/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:33:48 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/17 19:49:18 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **fix_map(char **map)
{
	char	**p;
	int		i;
	int		tmp;

	i = ((tmp = 0) ,0);
	while (map[i])
	{
		if (ft_strnstr(map[i], "111", ft_strlen(map[i])) != NULL)
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

int	strlen_map_width_and_height(char **p, char c)
{
	int	i;
	int	big_value;

	i = 0;
	big_value = 0;
	while (p && p[i])
	{
		if(ft_strlen(p[i]) >= big_value)
			big_value = ft_strlen(p[i]);
		i++;	
	}
	if(c == 'h')
		return i;
	return (big_value);
}

void start_cub3d(t_map *map)
{
	mlx_t	*mlx;
	
	map->width_map = strlen_map_width_and_height(map->map_s, 'w');
	map->height_map = strlen_map_width_and_height(map->map_s, 'h');
	mlx = init_mlx(map);
	mlx_loop(mlx);
}

int main(int ac, char **av)
{
	t_map	*map;
	int		i;

	if (ac < 2)
		return (printf("Error\n"));
	// if (ft_strncmp(av[1], ".cub", 4) != 0)
	// 	return (printf("Error\n"));
	map = read_map(av[1]);
	if (map == NULL)
		return (printf("Error\n"));
	// i = 0;
	// while(map->map_s[i])
	// {
	// 	printf("%s\n", map->map_s[i]);
	// 	i++;
	// }
	if (process_type_ids(map) != 6)
		return (1);
	
	if (process_map(map) != 1)
		return (1);
	map->map_s = fix_map(map->map_s);
	// i = 0;
	// while(map->map_s[i])
	// {
	// 	printf("%s\n", map->map_s[i]);
	// 	i++;
	// }
	start_cub3d(map);
	// mlx_terminate(mlx);
	// Create and display the image.
	// printf("#################\n");
	// printf("NO=%d\n", map->map_fd);
	// printf("SO=%s\n", map->SO);
	// printf("WE=%s\n", map->WE);
	// printf("EA=%s\n", map->EA);
	// printf("F=%s\n", map->F);
	// printf("C=%s\n", map->C);
	// printf("\n#################END\n");
	return (0);
}