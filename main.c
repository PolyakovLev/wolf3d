/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 19:51:12 by ramory-l          #+#    #+#             */
/*   Updated: 2019/02/13 19:53:54 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int argc, char **argv)
{
	t_app		app;
	t_player	player;
	t_camera	camera;

	if (argc == 2)
	{
		app.map = ft_create_map(argv[1], app.map_size);
		if (!app.map)
		{
			ft_putstr("wrong map");
			return (1);
		}
		if (init(&app, &player, &camera))
		{
			clean_up(&app);
			return (1);
		}
		while (!player.close_request)
			start_game(&app, &player, &camera);
		clean_up(&app);
	}
	return (0);
}
