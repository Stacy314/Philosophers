/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/05 17:13:25 by anastasiia       ###   ########.fr       */
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
		pthread_detach(sim->philosophers[j].thread);
		j++;
	}
	cleanup_simulation(sim);
	//wrong function call
	exit(1);
}

void	start_simulation(t_simulation *sim)
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
		//if (i == 5) // valgrind --tool=helgrind ./philo 6 600 200 200 10 sometimes fails with valgrind
		//{
		//	tread = 11;
		//}
		//else {
		tread = pthread_create(&sim->philosophers[i].thread, NULL,
			philosopher_lifecycle, &sim->philosophers[i]);
			
		//}
		if (tread != 0)
			stop_simulation(sim, i);
		i++;
	}
	tread = pthread_create(&sim->monitor_thread, NULL, death_monitor, sim);
	//tread = 11; // also could cause a valgrind error 
	if (tread != 0)
	{
		stop_simulation(sim, i);
		pthread_detach(sim->monitor_thread);
	}
	join_threads(sim);
}
