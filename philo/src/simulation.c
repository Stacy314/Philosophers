/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/07 14:13:53 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	join_threads(t_simulation *sim)
{
	int	i;
	int	tread;

	i = 0;
	while (i < sim->num_philosophers)
	{
		tread = pthread_join(sim->philosophers[i].thread, NULL);
		if (tread != 0)
		{
			ft_putendl_fd("Error: pthread_join failed ", 2);
		}
		i++;
	}
	tread = pthread_join(sim->monitor_thread, NULL);
	if (tread != 0)
	{
		ft_putendl_fd("Error: pthread_join failed ", 2);
	}
}

void	stop_simulation(t_simulation *sim, int i)
{
	int	j;

	pthread_mutex_lock(&sim->log_mutex);
	sim->simulation_running = STOPPED;
	pthread_mutex_unlock(&sim->log_mutex);
	ft_putendl_fd("Error: pthread_create failed", 2);
	j = 0;
	while (j < i)
	{
		pthread_join(sim->philosophers[j].thread, NULL);
		j++;
	}
	cleanup_simulation(sim);
}

int	start_simulation(t_simulation *sim)
{
	int			i;
	int			tread;

	pthread_mutex_lock(&sim->log_mutex);
	sim->simulation_running = RUNNING;
	pthread_mutex_unlock(&sim->log_mutex);
	sim->start_time = current_time();
	i = 0;
	while (i < sim->num_philosophers)
	{
		tread = pthread_create(&sim->philosophers[i].thread, NULL,
				philosopher_lifecycle, &sim->philosophers[i]);
		if (tread != 0)
		{
			stop_simulation(sim, i + 1);
			return (0);
		}
		i++;
	}
	tread = pthread_create(&sim->monitor_thread, NULL, death_monitor, sim);
	if (tread != 0)
		return (stop_simulation(sim, i), 0);
	join_threads(sim);
	return (1);
}
