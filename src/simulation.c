/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/11/04 19:59:13 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int parse_arguments(t_simulation *sim, int argc, char **argv)
{
	sim->num_philosophers = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->meal_goal = ft_atoi(argv[5]);
	else
		sim->meal_goal = -1;
	sim->simulation_running = 1;
    return (0);
}

int	initialize_simulation(t_simulation *sim, int argc, char **argv)
{
	int	i;

	parse_arguments(sim, argc, argv);
	sim->philosophers = ft_calloc(sizeof(t_philosopher) * sim->num_philosophers,
			1);
	sim->forks = ft_calloc(sizeof(t_fork) * sim->num_philosophers, 1);
	if (!sim->philosophers || !sim->forks)
		return (-1);
	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].last_meal_time = current_time();
		sim->philosophers[i].sim = sim;
		pthread_mutex_init(&sim->forks[i].mutex, NULL);
		sim->philosophers[i].left_fork = &sim->forks[i];
		sim->philosophers[i].right_fork = &sim->forks[(i + 1)
			% sim->num_philosophers];
		i++;
	}
	return (0);
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex);
		i++;
	}
	free(sim->forks);
	free(sim->philosophers);
}
