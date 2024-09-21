/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lps <lps@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:25:23 by lps               #+#    #+#             */
/*   Updated: 2024/09/19 12:25:24 by lps              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, const char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: ./< input >" << std::endl;
		return (1);
	}
    try
    {
        RPN(std::string(av[1]));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
	return (0);
}
