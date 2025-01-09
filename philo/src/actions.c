/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/04 18:18:54 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	think(t_philosopher *philo)
{
	if (check_simulation_running(philo->sim))
		log_action(philo->sim, philo->id, "is thinking");
	usleep(1000);
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

void	log_action(t_simulation *sim, int id, const char *status)
{
	pthread_mutex_lock(&sim->log_mutex);
	if (sim->simulation_running)
		printf("%ld %d %s\n", elapsed_time(sim->start_time), id, status);
	pthread_mutex_unlock(&sim->log_mutex);
}
