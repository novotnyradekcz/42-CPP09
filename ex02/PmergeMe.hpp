/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:29:27 by rnovotny          #+#    #+#             */
/*   Updated: 2026/05/06 19:49:26 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>
# include <iostream>
# include <ctime>
# include <iomanip>

// Uncomment the line below to enable comparison counting
// #define COUNT_COMPARISONS

class PmergeMe
{
private:
	std::vector<int> _vector;
	std::deque<int> _deque;
#ifdef COUNT_COMPARISONS
	size_t _vecComparisons;
	size_t _deqComparisons;
#endif
	
	PmergeMe();
	
public:
	PmergeMe(int argc, char** argv);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	
	void sort();
	void display(const std::string& prefix, const std::vector<int>& vec) const;
	
private:
	void parseInput(int argc, char** argv);
	bool isValidNumber(const std::string& str) const;
	
	std::vector<size_t> jacobsthalSequence(size_t n) const;

	// Ford-Johnson algorithm for vector
	void fordJohnsonVector(std::vector<int>& vec);
	void binaryInsertVector(std::vector<int>& chain, int val, size_t end);

	// Ford-Johnson algorithm for deque
	void fordJohnsonDeque(std::deque<int>& deq);
	void binaryInsertDeque(std::deque<int>& chain, int val, size_t end);
};

#endif