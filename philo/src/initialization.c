/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/04 20:21:27 by anastasiia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
void	init_philosopher(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].left_fork = &sim->forks[i];
		sim->philosophers[i].right_fork = &sim->forks[(i + 1)
			% sim->num_philosophers];
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].last_meal_time = current_time();
		sim->philosophers[i].sim = sim;
		i++;
	}
}

int	init_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		init_philosopher(sim);
		if (pthread_mutex_init(&sim->forks[i].fork_mutex, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&sim->philosophers[i].meal_mutex, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&sim->log_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	init_simulation(t_simulation *sim)
{
	sim->philosophers = ft_calloc(sim->num_philosophers
			* sizeof(t_philosopher), 1);
	if (!sim->philosophers)
	{
		if (sim->philosophers)
			free(sim->philosophers);
		return (0);
	}
	sim->forks = ft_calloc(sim->num_philosophers * sizeof(t_fork), 1);
	if (!sim->forks)
	{
		cleanup_simulation(sim);
		return (0);
	}
	if (!init_mutexes(sim))
	{
		cleanup_simulation(sim);
		return (0);
	}
	return (1);
}