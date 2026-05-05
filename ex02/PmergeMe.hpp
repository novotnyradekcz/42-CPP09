/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:29:27 by rnovotny          #+#    #+#             */
/*   Updated: 2026/05/05 22:05:25 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
private:
	std::vector<int> _vector;
	std::deque<int> _deque;
	// mutable size_t _vecComparisons;
	// mutable size_t _deqComparisons;
	
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