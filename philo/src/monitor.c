/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/04 18:42:46 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_meal_goal(t_simulation *sim)
{
	int	finished_philosophers;
	int	i;

	finished_philosophers = 0;
	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_lock(&sim->philosophers[i].meal_mutex);
		if (sim->meal_goal > 0 && sim->philosophers[i].meals_eaten
			>= sim->meal_goal)
			finished_philosophers++;
		pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);
		i++;
	}
	if (finished_philosophers == sim->num_philosophers)
	{
		pthread_mutex_lock(&sim->log_mutex);
		sim->simulation_running = 0;
		pthread_mutex_unlock(&sim->log_mutex);
		return (1);
	}
	//usleep(100);
	return (0);
}

int	check_philosopher_death(t_simulation *sim)
{
	int		i;
	long	time_since_last_meal;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_lock(&sim->philosophers[i].meal_mutex);
		time_since_last_meal = current_time()
			- sim->philosophers[i].last_meal_time;
		pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);
		if (time_since_last_meal > sim->time_to_die)
		{
			pthread_mutex_lock(&sim->log_mutex);
			sim->simulation_running = 0;
			printf("%ld %d died\n", elapsed_time(sim->start_time),
				sim->philosophers[i].id);
			pthread_mutex_unlock(&sim->log_mutex);
			return (1);
		}
		i++;
	}
	//usleep(100);
	return (0);
}

int	check_simulation_running(t_simulation *sim)
{
	int	running;

	pthread_mutex_lock(&sim->log_mutex);
	running = sim->simulation_running;
	pthread_mutex_unlock(&sim->log_mutex);
	return (running);
}

void	*death_monitor(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (1)
	{
		if (!check_simulation_running(sim))
			break ;
		if (check_philosopher_death(sim))
			return (NULL);
		if (check_meal_goal(sim))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

