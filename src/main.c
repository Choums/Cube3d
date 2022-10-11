/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:32:44 by aptive            #+#    #+#             */
/*   Updated: 2022/10/11 14:51:56 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*	DEBUG
void	debug(t_data *data)
{
	// printf("NO %s\nSO %s\nWE %s\nEA %s\n",
	data->tex_no->path,data->tex_so->path,data->tex_WE->path,data->tex_EA->path);
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
*/

t_data	*init_all(t_data *data, int argc, char **argv)
{
	if (verif_arg(argc, argv))
		exit(EXIT_FAILURE);
	data = init_data(data, argv[1]);
	if (!parsing_map(data))
		exit(EXIT_FAILURE);
	if (!check_map(data) || !solver_x(data) || !solver_y(data))
		exit(free_struct_config(data) + 1);
	init_player(data);
	return (data);
}

void	init_mlx(t_data *data)
{
	data->mlx_3d = mlx_init();
	mlx_get_screen_size(data->mlx_3d, &data->screen_w, &data->screen_h);
	data->screen_w = 1080;
	data->screen_h = 960;
	data->img_3d = mlx_new_image(data->mlx_3d, data->screen_w, data->screen_h);
	data->addr3d = mlx_get_data_addr(data->img_3d, &data->bpp,
			&data->length, &data->endian_3d);
	data->mlx_win_3d = mlx_new_window(data->mlx_3d, data->screen_w,
			data->screen_h, "Cub3D");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	data = init_all(data, argc, argv);
	init_mlx(data);
	if (!check_texture_path(data))
	{
		config_err();
		return (free_struct(data));
	}
	init_constante(data);
	ft_affiche_map(data);
	mlx_hook(data->mlx_win_3d, 33, 1L << 0, ft_close, data);
	mlx_hook(data->mlx_win_3d, 2, 1L << 0, ft_press, data);
	mlx_loop_hook(data->mlx_3d, key_hook, data);
	mlx_hook(data->mlx_win_3d, 3, 1L << 1, ft_release, data);
	mlx_loop(data->mlx_3d);
}
