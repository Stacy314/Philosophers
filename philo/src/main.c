/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/12/25 14:39:43 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <threads.h>

void	destroy_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex);
		pthread_mutex_destroy(&sim->philosophers[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->log_mutex);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	init_sructure(&sim);
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (!parse_arguments(&sim, argc, argv))
		return (0);
	if (!init_simulation(&sim))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	start_simulation(&sim);
	destroy_mutexes(&sim);
	cleanup_simulation(&sim);
	return (0);
}
