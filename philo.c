#include "philo.h"

void	forks(t_info *info, t_philo *philo)
{
	if ((philo->philo_id) % 2 == 0)
	{
		pthread_mutex_lock(&(info->forks[philo->l_fork]));		
		my_printf(info, philo->philo_id, "took a fork");
		pthread_mutex_lock(&(info->forks[philo->r_fork]));
		my_printf(info, philo->philo_id, "took a fork");
	}
	else
	{
		pthread_mutex_lock(&(info->forks[philo->r_fork]));
		my_printf(info, philo->philo_id, "took a fork");
		pthread_mutex_lock(&(info->forks[philo->l_fork]));
		my_printf(info, philo->philo_id, "took a fork");
	}
}

void	eating(t_philo *philo)
{
	t_info	*info;

	info = philo->info_lst;
	pthread_mutex_unlock(&(info->checker));
	pthread_mutex_lock(&(info->checker));
	my_printf(info, philo->philo_id, "is eating");
	philo->finished_eating = ft_time();
	pthread_mutex_unlock(&(info->checker));
	sleep_calculator(info, info->philo_t_eat);
	pthread_mutex_lock(&(info->checker));
	philo->eaten_meals++;
	pthread_mutex_unlock(&(info->checker));
	pthread_mutex_unlock(&(info->forks[philo->r_fork]));
	pthread_mutex_unlock(&(info->forks[philo->l_fork]));
}

void	*routine(void *param)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)param;
	info = philo->info_lst;
	if (philo->philo_id % 2 == 1)
		sleep_calculator(info, info->philo_t_eat * 0.9);
	while (info->is_dead != 1)
	{
		forks(info, philo);
		eating(philo);
		philo_sleeping(info, philo);
	}
	return (NULL);
}

int launch_threads(t_info *info, t_philo *philo)
{
	int		i;

	i = -1;
	info->time = ft_time();
	while (++i < info->total_p_num)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, routine, &(philo[i])))
			return (false);
	}
    return(true);
}

int	first_step(t_info *info, int ac, char **av)
{   
	int i  = 0;
    t_philo	*philo;

	if (check_input(ac, av) == false)
		return (1);
	if (init(ac, av, info) == false)
		return (2);
	philo = info->philos;
    if(launch_threads(info, philo) == false)
        return(4);
	is_dead(info);
	i = -1;
	while (++i < info->total_p_num)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < info->total_p_num)
		pthread_mutex_destroy(&(info->forks[i]));
	pthread_mutex_destroy(&(info->writing));
	pthread_mutex_destroy(&(info->checker));
	pthread_mutex_destroy(&philo->eating);
    return (0);
}
