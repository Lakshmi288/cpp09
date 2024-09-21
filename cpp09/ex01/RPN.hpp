/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lps <lps@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:25:39 by lps               #+#    #+#             */
/*   Updated: 2024/09/19 12:25:40 by lps              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <deque>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>

class RPN
{
	private:
		std::deque<std::string> _data;
		void initQue(std::string &input);
		bool validateInput(std::deque<std::string> stack);
		void calculate(std::deque<std::string> data);
	public:
		RPN(std::string input);
		RPN(const RPN &other);
		RPN& operator=(const RPN &rhs);
		~RPN();
};

#endif // !RPN_HPP