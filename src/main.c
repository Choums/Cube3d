/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:32:44 by aptive            #+#    #+#             */
/*   Updated: 2022/10/07 20:13:18 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*	DEBUG */
void affichage_data(t_data	*data)
{
	// printf("data->path->path_NO : %s\n", data->path->path_NO);
	// printf("ICI\n");
	// printf("data->path->path_SO : %s\n", data->path->path_SO);
	// printf("data->path->path_WE : %s\n", data->path->path_WE);
	// printf("data->path->path_EA : %s\n", data->path->path_EA);
	printf("Floor RGB\n");
	for (int i = 0; data->floor_rgb[i]; i++)
		printf ("ln %i	: %s\n", i, data->floor_rgb[i]);
	printf("Ceeling RGB\n");
	for (int i = 0; data->ceiling_rgb[i]; i++)
		printf ("ln %i	: %s\n", i, data->ceiling_rgb[i]);
	for (int i = 0; data->map[i]; i++)
		printf ("ln %i	: %s\n", i, data->map[i]);

	printf("map height : %i\n", data->map_h);
	printf("map weight : %i\n", data->map_w);

	printf("data->player->direction : %f\n", data->player->direction);
	printf("data->player->x : %i\n", data->player->x);
	printf("data->player->y : %i\n", data->player->y);


}

/*	DEBUG */
void	debug(t_data *data)
{
	// printf("NO %s\nSO %s\nWE %s\nEA %s\n", data->tex_no->path,data->tex_so->path,data->tex_WE->path,data->tex_EA->path);
	printf("F ");
	for (int i = 0; data->floor_rgb[i]; i++)
		printf("%s,", data->floor_rgb[i]);
	printf("\n");
	printf("C ");
	for (int i = 0; data->ceiling_rgb[i]; i++)
		printf("%s,", data->ceiling_rgb[i]);
	printf("\n\n");
	for (int i = 0; data->map[i]; i++)
		printf("|%s|\n", data->map[i]);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (verif_arg(argc, argv))
		return (1);
	data = init_data(data, argv[1]);
	if (!parsing_map(data))
		exit(EXIT_FAILURE);
	if (!check_map(data) || !solver_x(data) || !solver_y(data))
		exit(free_struct_config(data) + 1);
	init_player(data);

	// debug(data);
	// exit(0);


	data->mlx = mlx_init();
	data->img = mlx_new_image(data->mlx, data->map_w * SQUARE,
			data->map_h * SQUARE);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);


	data->mlx_3d = mlx_init();
	mlx_get_screen_size(data->mlx_3d, &data->screen_w, &data->screen_h);

	data->screen_w = 1080;
	data->screen_h = 960;


	data->img_3d = mlx_new_image(data->mlx_3d, data->screen_w, data->screen_h);
	data->addr3d = mlx_get_data_addr(data->img_3d, &data->bpp,
			&data->length, &data->endian_3d);
	data->mlx_win_3d = mlx_new_window(data->mlx_3d, data->screen_w,
			data->screen_h, "Cub3D");
	if (!check_texture_path(data))
	{
		config_err();
		return (free_struct(data));
	}

	// affichage_data(data);

	init_constante(data);

	ft_affiche_map(data);
	mlx_hook(data->mlx_win_3d, 33, 1L << 0, ft_close, data);
	mlx_hook(data->mlx_win_3d, 2, 1L << 0, ft_press, data);
	mlx_loop_hook(data->mlx_3d, key_hook, data);
	mlx_hook(data->mlx_win_3d, 3, 1L << 1, ft_release, data);
	mlx_loop(data->mlx_3d);
}
