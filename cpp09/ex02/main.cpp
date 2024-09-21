/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lps <lps@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:11:24 by lps               #+#    #+#             */
/*   Updated: 2024/09/20 13:11:26 by lps              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, const char **av)
{
	if (ac < 2)
	{
		std::cerr << "No Input\nUsage: ./PmergeMe < numbers >" << std::endl;
		return (1);
	}
	try
	{
		PmergeMe a = PmergeMe(av);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}