/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/04 18:10:09 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	init_sructure(&sim);
	if (!parse_arguments(&sim, argc, argv))
		return (0);
	if (!init_simulation(&sim))
	{
		printf("Error: Initialization failed\n");
		return (1);
	}
	start_simulation(&sim);
	destroy_mutexes(&sim);
	cleanup_simulation(&sim);
	return (0);
}
