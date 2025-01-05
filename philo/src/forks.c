/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anastasiia <anastasiia@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2025/01/05 17:18:03 by anastasiia       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

void	for_odd(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			print_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			print_action(philo->sim, philo->id, "has taken a fork");
	}
	else
	{
		usleep(50);
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			print_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			print_action(philo->sim, philo->id, "has taken a fork");
	}
}
// void	for_three(t_philosopher *philo)
// {
	
// 	if (philo->id == 0)
// 	{
// 		pthread_mutex_lock(&philo->left_fork->fork_mutex);
// 		if (check_simulation_running(philo->sim))
// 			print_action(philo->sim, philo->id, "has taken a fork");
// 		pthread_mutex_lock(&philo->right_fork->fork_mutex);
// 		if (check_simulation_running(philo->sim))
// 			print_action(philo->sim, philo->id, "has taken a fork");
// 	}
// 	else if (philo->id == 1)
// 	{
// 		usleep(50);
// 		pthread_mutex_lock(&philo->right_fork->fork_mutex);
// 		if (check_simulation_running(philo->sim))
// 			print_action(philo->sim, philo->id, "has taken a fork");
// 		pthread_mutex_lock(&philo->left_fork->fork_mutex);
// 		if (check_simulation_running(philo->sim))
// 			print_action(philo->sim, philo->id, "has taken a fork");
// 	}
// 	else if (philo->id == 2)
// 	{
// 		usleep(100);
// 		pthread_mutex_lock(&philo->right_fork->fork_mutex);
// 		if (check_simulation_running(philo->sim))
// 			print_action(philo->sim, philo->id, "has taken a fork");
// 		pthread_mutex_lock(&philo->left_fork->fork_mutex);
// 		if (check_simulation_running(philo->sim))
// 			print_action(philo->sim, philo->id, "has taken a fork");
// 	}
// }

void	take_forks(t_philosopher *philo)
{
	// if (philo->sim->num_philosophers == 3)
	// {
	// 	for_three(philo);
	// 	return ;
	// }
	if (philo->id % 2 == 0)
	{
		usleep(50);
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			print_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			print_action(philo->sim, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			print_action(philo->sim, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		if (check_simulation_running(philo->sim))
			print_action(philo->sim, philo->id, "has taken a fork");
	}
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
}