/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lps <lps@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:11:36 by lps               #+#    #+#             */
/*   Updated: 2024/09/20 16:40:06 by lps              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool PmergeMe::isDigitValid(std::string value)
{
    std::string::iterator i = value.begin();
    if (value.empty() || *i == '-')
        return (false);
    if (*i == '+')
        i++;
    if (i == value.end())
        return (false);
    while (i != value.end())
    {
        if (!std::isdigit(*i))
            return (false);
        i++;
    }
	if (std::atof(value.c_str()) > INT_MAX)
		return (false);
    return (true);    
}

size_t PmergeMe::jacobsthal(size_t n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

std::list<IntPair> PmergeMe::createListPairs(std::list<int> lst)
{
    std::list<IntPair> pairs;
    IntListIterator i = lst.begin();
    while (i != lst.end())
    {
        IntListIterator next = i;
        ++next;
        if (next != lst.end())
        {
            if (*i < *next)
                pairs.push_back(IntPair(*i, *next));
            else
                pairs.push_back(IntPair(*next, *i));
        }
        ++i; ++i;
    }
    return pairs;
}



std::vector<IntPair> PmergeMe::createVectorPairs(std::vector<int> vec)
{
    std::vector<IntPair> pairs;
    for (size_t i = 0; i < _size - 1; i += 2)
    {
        if (vec[i] < vec[i + 1])
            pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
        else
            pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
    }
    return (pairs);
}

std::list<int> PmergeMe::sortWithLst()
{
    int staggler;
    bool isOdd = false;
    if (lst.size() % 2 != 0)
    {
        staggler = lst.back();
        isOdd = true;
        lst.pop_back();
    }
    std::list<IntPair> pairs =  createListPairs(lst);
    sortPair(pairs, pairs.size());
    std::list<int> S;
    std::list<int> pend;
    std::list<IntPair>::iterator i = pairs.begin();
    for (; i != pairs.end(); i++)
    {
        S.push_back(i->second);
        pend.push_back(i->first);
    }
    if (isOdd)
        pend.push_back(staggler);
    createSortedContainer(S, pend);
    return (S);
}

std::vector<int> PmergeMe::sortWithVec()
{
    int staggler;
    bool isOdd = false;
    if (_size % 2 != 0)
    {
        staggler = vec.back();
        isOdd = true;
        vec.erase(vec.end() - 1);
    }
    std::vector<IntPair> pairs =  createVectorPairs(vec);
    std::vector<int> S;
    std::vector<int> pend;
    sortPair(pairs, pairs.size());
    for (size_t i = 0; i < pairs.size(); i++)
    {
        S.push_back(pairs[i].second);
        pend.push_back(pairs[i].first);
    }
    if (isOdd)
        pend.push_back(staggler);
    createSortedContainer(S, pend);
    return (S);
}

void PmergeMe::sortAndPrint()
{
    std::cout << "Before:  ";
    print(vec);
    clock_t start_vec = clock();
    std::vector<int> S_vec = sortWithVec();
    clock_t end_vec = clock();
    
    clock_t start_lst = clock();
    std::list<int> S_lst = sortWithLst();
    clock_t end_lst = clock();
    
    double elapsed_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC;
    double elapsed_lst = static_cast<double>(end_lst - start_lst) / CLOCKS_PER_SEC;
    std::cout << "After:  ";
    print(S_vec);
    std::cout << "Time to process a range of " << _size << " elements with std::vector : " << std::fixed << std::setprecision(6) << elapsed_vec << " us" << std::endl;
    std::cout << "Time to process a range of " << _size << " elements with std::list : " << std::fixed << std::setprecision(6) << elapsed_lst << " us" << std::endl;
}


PmergeMe::PmergeMe(const char **av)
{
    while (++av && *av)
    {
        if (!isDigitValid(*av))
			throw std::invalid_argument("Error");
        vec.push_back(std::atoi(*av));
		lst.push_back(std::atoi(*av));
    }
    _size = vec.size();
    if (_size == 1)
        return ;

    sortAndPrint();
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
	if (this != &rhs) {
        vec = rhs.vec;
        lst = rhs.lst;
        _size = rhs._size;
    }
	return (*this);
}

PmergeMe::~PmergeMe() { }