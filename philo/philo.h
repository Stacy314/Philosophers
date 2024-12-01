/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apechkov <apechkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:17:43 by apechkov          #+#    #+#             */
/*   Updated: 2024/11/29 19:00:37 by apechkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdbool.h>


#define MAX_PHILOSOPHERS 200

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_t			thread;
	struct s_simulation	*sim;
	t_fork				*left_fork;
	t_fork				*right_fork; 
	pthread_mutex_t     meal_mutex;
}	t_philosopher;

typedef struct s_simulation
{
	char			*str;
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	long			start_time;
	t_philosopher	philosophers[MAX_PHILOSOPHERS];
    t_fork			forks[MAX_PHILOSOPHERS];
	bool			simulation_running;
    //bool			should_exit;
	pthread_mutex_t	log_mutex;  
	//pthread_mutex_t state_mutex; 
	//int				has_died;
}	t_simulation;

int		initialize_simulation(t_simulation *sim);
void	start_simulation(t_simulation *sim);
void	*philosopher_lifecycle(void *arg);
void	cleanup_simulation(t_simulation *sim);
long	current_time(void);
void	log_action(t_simulation *sim, int id, const char *status);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

void	think(t_philosopher *philo);
void	take_forks(t_philosopher *philo);
void	eat(t_philosopher *philo);
void	release_forks(t_philosopher *philo);
void	sleep_and_log(t_philosopher *philo);
int		valid_arg(t_simulation *sim, char **argv);
int		parse_arguments(t_simulation *sim, int argc, char **argv);
long	elapsed_time(long start_time);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
char	*ft_itoa(int n);
#endif