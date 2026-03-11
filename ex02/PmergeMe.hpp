/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:29:27 by rnovotny          #+#    #+#             */
/*   Updated: 2026/03/11 16:35:08 by rnovotny         ###   ########.fr       */
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
	
	PmergeMe();
	
public:
	PmergeMe(int argc, char** argv);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	
	void sort();
	void display() const;
	
private:
	void parseInput(int argc, char** argv);
	bool isValidNumber(const std::string& str) const;
	
	// Ford-Johnson algorithm for vector
	void fordJohnsonVector(std::vector<int>& vec);
	void insertionSortVector(std::vector<int>& vec, size_t left, size_t right);
	void mergeVector(std::vector<int>& vec, size_t left, size_t mid, size_t right);
	
	// Ford-Johnson algorithm for deque
	void fordJohnsonDeque(std::deque<int>& deq);
	void insertionSortDeque(std::deque<int>& deq, size_t left, size_t right);
	void mergeDeque(std::deque<int>& deq, size_t left, size_t mid, size_t right);
};

#endif