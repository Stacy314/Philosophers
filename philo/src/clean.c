/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/04 18:32:07 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup_simulation(t_simulation *sim)
{
	if (sim->philosophers)
		free(sim->philosophers);
	if (sim->forks)
		free(sim->forks);
}

void	destroy_philo_mutex(t_simulation *sim, int i)
{
	while (--i >= 0)
	{
		pthread_mutex_destroy(&sim->forks[i].fork_mutex);
		pthread_mutex_destroy(&sim->philosophers[i].meal_mutex);
	}
}

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
