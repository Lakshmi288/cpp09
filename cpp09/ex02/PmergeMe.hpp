/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lps <lps@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:11:43 by lps               #+#    #+#             */
/*   Updated: 2024/09/20 13:11:46 by lps              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PMERGEME_HPP
#define	PMERGEME_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <climits>
#include <algorithm>
#include <list>
#include <utility>
#include <iomanip>

typedef std::list<int>::iterator IntListIterator;
typedef std::vector<int>::iterator IntVectorIterator;
typedef std::pair<int, int> IntPair;

class PmergeMe
{
	private:
		std::vector<int> vec;
		std::list<int> lst;
		size_t _size;

		PmergeMe();
		size_t jacobsthal(size_t n);
		bool isDigitValid(std::string value);
		void sortAndPrint();
		std::vector<int> sortWithVec();
		std::list<int> sortWithLst();
		std::list<IntPair> createListPairs(std::list<int> lst);
		std::vector<IntPair> createVectorPairs(std::vector<int> vec);

	public:
		PmergeMe(const char **av);
		~PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& rhs);
		// void sort();
	
		template <class T>
		void print(const T& data);
		template <typename Container>
		Container build_jacob_insertion_sequence(size_t size);
    	template <typename Container, typename T>
	    typename Container::iterator bisearch(Container& container, const T& item);
		template <typename Container>
		void sortPair(Container &pairs, size_t n);
		template <typename Container>
		void createSortedContainer(Container &S, Container &pend);
};		

template <class T>
void PmergeMe::print(const T& data)
{
    typename T::const_iterator it = data.begin();
    for (; it != data.end(); ++it)
    {
        std::cout << *it << " ";
    }
	std::cout << std::endl;
}

template <typename Container, typename T>
typename Container::iterator PmergeMe::bisearch(Container& container, const T& item)
{
    return std::upper_bound(container.begin(), container.end(), item);
}

template <typename Container>
void PmergeMe::sortPair(Container &pairs, size_t n) {
    if (n <= 1)
        return;
    sortPair(pairs, n - 1);
    size_t i = n - 1;
    typename Container::iterator it = pairs.begin();
    std::advance(it, n - 1);
    IntPair newPair = *it;
    typename Container::iterator prevIt = it;
    --prevIt;
    for (; i > 0 && (newPair.second < prevIt->second); --i) {
        *it = *prevIt;
        --it;
        --prevIt;
    }
    *it = newPair;
}

template <typename Container>
Container PmergeMe::build_jacob_insertion_sequence(size_t size) {
    Container end_sequence;
    size_t jacob_index = 3;
    while (jacobsthal(jacob_index) < size - 1) {
        end_sequence.push_back(jacobsthal(jacob_index));
        jacob_index += 1;
    }
    return end_sequence;
}

template <typename Container>
void PmergeMe::createSortedContainer(Container &S, Container &pend) {
    Container jacob_sequence = build_jacob_insertion_sequence<Container>(pend.size());
    size_t iter = 0;
    size_t jacobIndex = 3;
    bool isJacob = true;
    typename Container::iterator pend_iter = pend.begin();
    typename Container::iterator jacob_iter = jacob_sequence.begin();
    S.insert(S.begin(), *pend_iter);
    ++pend_iter;
    if (pend_iter == pend.end())
        return;
    Container indexSequence;
    typename Container::value_type item;
    indexSequence.push_back(1);
    while (iter <= pend.size()) {
        if (jacob_iter != jacob_sequence.end() && isJacob) {
            indexSequence.push_back(*jacob_iter);
            typename Container::iterator next = jacob_iter;
            ++next;
            item = *next;
            jacob_iter = jacob_sequence.erase(jacob_iter);
            isJacob = false;
        } else {
            if (std::find(indexSequence.begin(), indexSequence.end(), iter) != indexSequence.end())
                iter++;
            indexSequence.push_back(iter);
            if (iter == 0) {
                iter++;
                continue;
            }
            item = *pend_iter;
            ++pend_iter;
            isJacob = true;
        }
        typename Container::iterator pos = bisearch(S, item);
        S.insert(pos, item);
        iter++;
        jacobIndex++;
    }
}


#endif // PMERGEME_HPP