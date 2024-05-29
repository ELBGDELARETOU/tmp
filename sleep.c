#include "philo.h"

void	sleep_calculator(t_info *info, unsigned long time_to_wait)
{
	unsigned long	time;

	time = ft_time();
	while (ft_time() - time < time_to_wait && info->is_dead == 0)
		usleep(100);
}

void	philo_sleeping(t_info *info, t_philo *philo)
{
	my_printf(info, philo->philo_id,  "is sleeping");
	sleep_calculator(info, info->philo_t_sleep);
	my_printf(info, philo->philo_id,  "is thinking");
	if (info->total_p_num % 2 == 1)
		sleep_calculator(info, info->philo_t_eat);
	else
		usleep(10);
}