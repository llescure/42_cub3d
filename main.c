/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:25:59 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:26:02 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/struct_cub3d.h"
#include "include/cub3d.h"

int		main(int argc, char **argv)
{
	t_data	data;

	data.param = initialize(argc, argv);
	if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
		return (create_image(&data));
	init_music(&data);
	if (create_window(&data) == -1)
		return (-1);
	initialize_mlx(&data);
	return (0);
}
