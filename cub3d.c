/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:33:48 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/09/10 21:20:32 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*read_map(char *file)
{
	int		fd;
	int		r_count;
	char	buff[BUFSIZ];
	t_map	*ret;

	fd = open(file, O_RDONLY);
	if (fd < 3)
		return (NULL);
	r_count = read(fd, buff, BUFSIZ);
	if (r_count <= 0)
		return (NULL);
	ret = malloc(sizeof(t_map));
	ret->map_fd = fd;
	ret->map_s = ft_split(buff, '\n');
	return (ret);
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
	printf("#################\n");
	process_type_ids(map);
	printf("\n################# END\n");
	printf("NO=%s\n", map->NO);
	printf("SO=%s\n", map->SO);
	printf("WE=%s\n", map->WE);
	printf("EA=%s\n", map->EA);
	printf("F=%s\n", map->F);
	printf("C=%s\n", map->C);
	return (0);
}