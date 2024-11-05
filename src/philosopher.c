/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/11/05 12:07:11 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//void	*philosopher_lifecycle(void *arg)
//{
//	t_philosopher	*philo;
//	t_simulation	*sim;

//	philo = (t_philosopher *)arg;
//	sim = philo->sim;
//	if (sim->num_philosophers == 1)
//	{
//		log_action(philo->id, "is thinking");
//		pthread_mutex_lock(&philo->left_fork->mutex);
//		log_action(philo->id, "has taken a fork");
//		usleep(sim->time_to_die * 1000);
//		log_action(philo->id, "died");
//		pthread_mutex_unlock(&philo->left_fork->mutex);
//		return (NULL);
//	}
//	while (sim->simulation_running)
//	{
//		log_action(philo->id, "is thinking");
//		usleep(100);
//		pthread_mutex_lock(&philo->left_fork->mutex);
//		log_action(philo->id, "has taken a fork");
//		pthread_mutex_lock(&philo->right_fork->mutex);
//		log_action(philo->id, "has taken a fork");
//		philo->last_meal_time = current_time();
//		log_action(philo->id, "is eating");
//		usleep(sim->time_to_eat * 1000);
//		philo->meals_eaten++;
//		pthread_mutex_unlock(&philo->right_fork->mutex);
//		pthread_mutex_unlock(&philo->left_fork->mutex);
//		if (sim->meal_goal > 0 && philo->meals_eaten >= sim->meal_goal)
//			break ;
//		log_action(philo->id, "is sleeping");
//		usleep(sim->time_to_sleep * 1000);
//	}
//	return (NULL);
//}

// Handles the case where there's only one philosopher
void handle_single_philosopher(t_philosopher *philo) {
    log_action(philo->id, "is thinking");
    pthread_mutex_lock(&philo->left_fork->mutex);
    log_action(philo->id, "has taken a fork");

    usleep(philo->sim->time_to_die * 1000);  // Wait for time_to_die to simulate death

    log_action(philo->id, "died");
    pthread_mutex_unlock(&philo->left_fork->mutex);
}

// Makes the philosopher think
void think(t_philosopher *philo) {
    log_action(philo->id, "is thinking");
    usleep(100);  // Small delay to avoid rapid cycling
}

// Makes the philosopher take both forks
void take_forks(t_philosopher *philo) {
    pthread_mutex_lock(&philo->left_fork->mutex);
    log_action(philo->id, "has taken a fork");
    pthread_mutex_lock(&philo->right_fork->mutex);
    log_action(philo->id, "has taken a fork");
}

// Makes the philosopher eat and updates their last meal time
void eat(t_philosopher *philo) {
    philo->last_meal_time = current_time();
    log_action(philo->id, "is eating");
    usleep(philo->sim->time_to_eat * 1000);  // Simulate eating time
    philo->meals_eaten++;
}

// Makes the philosopher release both forks
void release_forks(t_philosopher *philo) {
    pthread_mutex_unlock(&philo->right_fork->mutex);
    pthread_mutex_unlock(&philo->left_fork->mutex);
}

// Makes the philosopher sleep
void sleep_and_log(t_philosopher *philo) {
    log_action(philo->id, "is sleeping");
    usleep(philo->sim->time_to_sleep * 1000);  // Simulate sleeping time
}

// The main lifecycle function that uses helper functions to perform actions
void *philosopher_lifecycle(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_simulation *sim = philo->sim;

    // Special case: only one philosopher, handle separately
    if (sim->num_philosophers == 1) {
        handle_single_philosopher(philo);
        return NULL;
    }

    // Main loop for the philosopher's lifecycle
    while (sim->simulation_running) {
        think(philo);

        take_forks(philo);
        eat(philo);
        release_forks(philo);

        if (sim->meal_goal > 0 && philo->meals_eaten >= sim->meal_goal)
            break;

        sleep_and_log(philo);
    }
    return NULL;
}

void	start_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_create(&sim->philosophers[i].thread, NULL,
			philosopher_lifecycle, &sim->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_join(sim->philosophers[i].thread, NULL);
		i++;
	}
	sim->simulation_running = 0;
}
