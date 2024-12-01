/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/11/29 18:52:03 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void handle_single_philosopher(t_philosopher *philo)
{
    log_action(philo->sim, philo->id, "is thinking");
    pthread_mutex_lock(&philo->left_fork->mutex);
    log_action(philo->sim, philo->id, "has taken a fork");
    usleep(philo->sim->time_to_die * 1000);
    pthread_mutex_unlock(&philo->left_fork->mutex);
}

void *philosopher_lifecycle(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_simulation *sim = philo->sim;

    if (sim->num_philosophers == 1)
    {
        handle_single_philosopher(philo);
        return (NULL);
    }

    while (sim->simulation_running)
    {
        take_forks(philo);
        eat(philo);
        if (sim->meal_goal > 0 && philo->meals_eaten >= sim->meal_goal)
        {
            release_forks(philo);
            break;
        }

        release_forks(philo);
        sleep_and_log(philo);
        think(philo);
    }
    return (NULL);
}

void *death_monitor(void *arg)
{
    t_simulation *sim = (t_simulation *)arg;
    int finished_philosophers = 0;

    while (sim->simulation_running)
    {
        finished_philosophers = 0;
        for (int i = 0; i < sim->num_philosophers; i++)
        {
            pthread_mutex_lock(&sim->log_mutex);
            long time_since_last_meal = current_time() - sim->philosophers[i].last_meal_time;
            if (time_since_last_meal >= sim->time_to_die)
            {
                sim->simulation_running = 0;
                printf("%ld %d died\n", elapsed_time(sim->start_time), sim->philosophers[i].id);
                pthread_mutex_unlock(&sim->log_mutex);
				cleanup_simulation(sim);
                exit(1);
            }
            if (sim->meal_goal > 0 && sim->philosophers[i].meals_eaten >= sim->meal_goal)
                finished_philosophers++;

            pthread_mutex_unlock(&sim->log_mutex);
        }
        if (sim->meal_goal > 0 && finished_philosophers == sim->num_philosophers)
        {
            sim->simulation_running = 0;
            return (NULL);
        }

        usleep(1000);
    }
    return (NULL);
}

void	start_simulation(t_simulation *sim)
{
	int	i; 
	pthread_t monitor_thread;

	i = 0;
	sim->start_time = current_time(); 
	while (i < sim->num_philosophers)
	{
		pthread_create(&sim->philosophers[i].thread, NULL,
			philosopher_lifecycle, &sim->philosophers[i]); //leak
		i++;
	}
	pthread_create(&monitor_thread, NULL, death_monitor, sim); //leak
	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_join(sim->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}
long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
long elapsed_time(long start_time)
{
    return (current_time() - start_time);
}

void	log_action(t_simulation *sim, int id, const char *status)
{
	pthread_mutex_lock(&sim->log_mutex);
    printf("%ld %d %s\n", elapsed_time(sim->start_time), id, status);
	pthread_mutex_unlock(&sim->log_mutex);
}