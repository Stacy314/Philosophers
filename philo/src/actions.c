/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/12/03 18:00:33 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philosopher *philo)
{
	if (philo->sim->simulation_running != 0)
		log_action(philo->sim, philo->id, "is thinking");
	usleep(1000);
}

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (philo->sim->simulation_running != 0)
			log_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->sim->simulation_running != 0)
			log_action(philo->sim, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->sim->simulation_running != 0)
			log_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (philo->sim->simulation_running != 0)
			log_action(philo->sim, philo->id, "has taken a fork");
	}
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->sim->simulation_running != 0)
		log_action(philo->sim, philo->id, "is eating");
	usleep(philo->sim->time_to_eat * 1000);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	sleep_and_log(t_philosopher *philo)
{
	if (philo->sim->simulation_running != 0)
		log_action(philo->sim, philo->id, "is sleeping");
	usleep(philo->sim->time_to_sleep * 1000);
}
