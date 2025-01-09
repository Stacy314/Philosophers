/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/07 14:07:14 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Error: wrong number of arguments", 2);
		return (1);
	}
	init_sructure(&sim);
	if (!parse_arguments(&sim, argc, argv))
	{
		ft_putendl_fd("Error: Invalid arguments", 2);
		return (1);
	}
	if (!init_simulation(&sim))
	{
		ft_putendl_fd("Error: Initialization failed", 2);
		return (1);
	}
	if (start_simulation(&sim))
	{
		destroy_all_mutexes(&sim);
		cleanup_simulation(&sim);
	}
	return (0);
}
