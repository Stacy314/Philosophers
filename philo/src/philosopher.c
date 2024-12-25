/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/12/25 14:42:54 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	one_philosopher(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	log_action(philo->sim, philo->id, "has taken a fork");
	usleep(philo->sim->time_to_die * 1000);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

int	check_simulation_running(t_simulation *sim)
{
	int	running;

	pthread_mutex_lock(&sim->log_mutex);
	running = sim->simulation_running;
	pthread_mutex_unlock(&sim->log_mutex);
	return (running);
}

void	*philosopher_lifecycle(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->sim->num_philosophers == 1)
		return (one_philosopher(philo), NULL);
	while (1)
	{
		if (!check_simulation_running(philo->sim))
			break ;
		take_forks(philo);
		if (!check_simulation_running(philo->sim))
		{
			release_forks(philo);
			break ;
		}
		eat(philo);
		release_forks(philo);
		if (!check_simulation_running(philo->sim))
			break ;
		sleep_and_log(philo);
		if (!check_simulation_running(philo->sim))
			break ;
		think(philo);
	}
	return (NULL);
}

void	join_treads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		if (pthread_join(sim->philosophers[i].thread, NULL))
			printf("Error: Failed to join thread %d\n", i + 1);
		i++;
	}
}

void	start_simulation(t_simulation *sim)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	sim->start_time = current_time();
	while (i < sim->num_philosophers)
	{
		if (pthread_create(&sim->philosophers[i].thread, NULL,
				philosopher_lifecycle, &sim->philosophers[i]))
		{
			sim->simulation_running = 0;
			join_treads(sim);
			return ;
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, death_monitor, sim))
	{
		sim->simulation_running = 0;
		join_treads(sim);
		return ;
	}
	join_treads(sim);
	pthread_join(monitor_thread, NULL);
}
