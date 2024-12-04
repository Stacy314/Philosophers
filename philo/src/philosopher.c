/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/12/03 23:14:31 by anastasiia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	handle_philosopher(t_philosopher *philo) //i need change name
{
	log_action(philo->sim, philo->id, "is thinking");
	pthread_mutex_lock(&philo->left_fork->mutex);
	log_action(philo->sim, philo->id, "has taken a fork");
	usleep(philo->sim->time_to_die * 1000);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	*philosopher_lifecycle(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sim;

	philo = (t_philosopher *)arg;
	sim = philo->sim;
	if (sim->num_philosophers == 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		log_action(sim, philo->id, "has taken a fork");
		while (1)
		{
			pthread_mutex_lock(&sim->log_mutex);
			if (!sim->simulation_running)
			{
				pthread_mutex_unlock(&sim->log_mutex);
				pthread_mutex_unlock(&philo->left_fork->mutex);
				break ;
			}
			pthread_mutex_unlock(&sim->log_mutex);
			usleep(1000);
		}
		return (NULL);
	}
	else
	{
		while (1)
		{
			pthread_mutex_lock(&sim->log_mutex);
			if (!sim->simulation_running)
			{
				pthread_mutex_unlock(&sim->log_mutex);
				break ;
			}
			pthread_mutex_unlock(&sim->log_mutex);
			take_forks(philo);
			pthread_mutex_lock(&sim->log_mutex);
			if (!sim->simulation_running)
			{
				pthread_mutex_unlock(&sim->log_mutex);
				release_forks(philo);
				break ;
			}
			pthread_mutex_unlock(&sim->log_mutex);
			eat(philo);
			release_forks(philo);
			pthread_mutex_lock(&sim->log_mutex);
			if (!sim->simulation_running)
			{
				pthread_mutex_unlock(&sim->log_mutex);
				break ;
			}
			pthread_mutex_unlock(&sim->log_mutex);
			sleep_and_log(philo);
			pthread_mutex_lock(&sim->log_mutex);
			if (!sim->simulation_running)
			{
				pthread_mutex_unlock(&sim->log_mutex);
				break ;
			}
			pthread_mutex_unlock(&sim->log_mutex);
			think(philo);
		}
		return (NULL);
	}
}

void	*death_monitor(void *arg)
{
	t_simulation	*sim;
	int				i;
	long			time_since_last_meal;
	int				finished_philosophers;

	sim = (t_simulation *)arg;
	while (sim->simulation_running != 0)
	{
		pthread_mutex_lock(&sim->log_mutex);
		if (!sim->initialized)
		{
			pthread_mutex_unlock(&sim->log_mutex);
			usleep(1000);
			continue ;//i cannot use 
		}
		pthread_mutex_unlock(&sim->log_mutex);
		i = 0;
		while (i < sim->num_philosophers)
		{
			pthread_mutex_lock(&sim->philosophers[i].meal_mutex);
			time_since_last_meal = current_time()
				- sim->philosophers[i].last_meal_time;
			pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);
			if (time_since_last_meal >= sim->time_to_die)
			{
				pthread_mutex_lock(&sim->log_mutex);
				sim->simulation_running = 0;
				printf("%ld %d died\n",
					elapsed_time(sim->start_time), sim->philosophers[i].id);
				pthread_mutex_unlock(&sim->log_mutex);
				return (NULL);
			}
			i++;
		}
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
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	start_simulation(t_simulation *sim)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	sim->start_time = current_time();
	while (i < sim->num_philosophers)
	{
		pthread_create(&sim->philosophers[i].thread, NULL,
			philosopher_lifecycle, &sim->philosophers[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, death_monitor, sim);
	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_join(sim->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

void	log_action(t_simulation *sim, int id, const char *status)
{
	pthread_mutex_lock(&sim->log_mutex); // why is it here? 
	printf("%ld %d %s\n", elapsed_time(sim->start_time), id, status);
	pthread_mutex_unlock(&sim->log_mutex);
}
