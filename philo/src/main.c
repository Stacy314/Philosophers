/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/12/30 17:51:51 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_destroy(&sim->forks[i].fork_mutex);
		pthread_mutex_destroy(&sim->philosophers[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->log_mutex);
}

void	init_sructure(t_simulation *sim)
{
	sim->str = NULL;
	sim->num_philosophers = 0;
	sim->time_to_die = 0;
	sim->time_to_eat = 0;
	sim->time_to_sleep = 0;
	sim->meal_goal = 0;
	sim->start_time = 0;
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
