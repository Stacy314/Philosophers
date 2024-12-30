/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/12/30 17:57:28 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philosopher *philo)
{
	if (check_simulation_running(philo->sim))
		log_action(philo->sim, philo->id, "is thinking");
	usleep(1000);
}

void	for_odd(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			log_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			log_action(philo->sim, philo->id, "has taken a fork");
	}
	else
	{
		usleep(50);
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			log_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			log_action(philo->sim, philo->id, "has taken a fork");
	}
}

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(50);
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			log_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			log_action(philo->sim, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			log_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			log_action(philo->sim, philo->id, "has taken a fork");
	}
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (check_simulation_running(philo->sim))
		log_action(philo->sim, philo->id, "is eating");
	ft_usleep(philo->sim, philo->sim->time_to_eat);
}

void	sleep_and_log(t_philosopher *philo)
{
	if (check_simulation_running(philo->sim))
		log_action(philo->sim, philo->id, "is sleeping");
	ft_usleep(philo->sim, philo->sim->time_to_sleep);
}
