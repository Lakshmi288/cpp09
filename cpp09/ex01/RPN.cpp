/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lps <lps@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:25:34 by lps               #+#    #+#             */
/*   Updated: 2024/09/19 12:25:35 by lps              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool RPN::validateInput(std::deque<std::string> stack)
{
	std::string validExp = "+-/*";
	size_t countExp = 0;
	size_t countDigit = 0;

	while (!stack.empty())
    {
		if (stack.front().length() == 1 && validExp.find(stack.front()[0]) != std::string::npos)
			countExp++;
		else
		{
			std::string::iterator it = stack.front().begin();
			if (*it == '-' || *it == '+')
				it++;
			if (std::distance(it, stack.front().end()) < 2)
			{
				if (std::isdigit(*it))
					countDigit++;
				else
					return (false);
			}
			else
				return (false);
		}
        stack.pop_front();
    }
	if (countExp != countDigit - 1)
		return (false);
	return (true);
}

void RPN::calculate(std::deque<std::string> data)
{
    std::deque<int> op;
    std::string exp = "+-*/";

    for (std::deque<std::string>::reverse_iterator rit = data.rbegin(); rit != data.rend(); ++rit) {
        std::string tok = *rit;
        if (exp.find(tok) != std::string::npos) {
            if (op.size() < 2) {
                std::cerr << "Invalid expression" << std::endl;
                return;
            }

            int a = op.back();
            op.pop_back();
            int b = op.back();
            op.pop_back();

            if (tok == "*")
                op.push_back(a * b);
            else if (tok == "-")
                op.push_back(b - a);
            else if (tok == "+")
                op.push_back(a + b);
            else if (tok == "/") {
                if (a == 0 ) {
                    std::cerr << "Error: Division by zero" << std::endl;
                    return;
                }
                op.push_back(b / a);
            }
        } else {
            op.push_back(std::atoi(tok.c_str()));
        }
    }
    if (op.size() != 1) {
        std::cerr << "Invalid expression" << std::endl;
        return;
    }
    std::cout << "Result: " << op.front() << std::endl;
}

void RPN::initQue(std::string &input)
{
	std::string word;
	std::istringstream iss(input);
	while(iss >> word)
		_data.push_front(word);
	if (!validateInput(_data))
		throw std::runtime_error("Error");
}

RPN::RPN(std::string input)
{
    try
    {
	    initQue(input);
        calculate(_data);
    }
    catch(const std::exception& e)
    {
        throw;
    }
}

RPN::RPN(const RPN &other)
{
    this->_data = other._data;
}

RPN& RPN::operator=(const RPN &rhs)
{
    if (this != &rhs)
        this->_data = rhs._data;
    return (*this);
}

RPN::~RPN() { }