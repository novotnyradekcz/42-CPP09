/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:29:42 by rnovotny          #+#    #+#             */
/*   Updated: 2026/03/11 20:31:09 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int argc, char** argv)
{
	parseInput(argc, argv);
}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseInput(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string str(argv[i]);
		if (!isValidNumber(str))
			throw std::runtime_error("Invalid input");
		
		int num = std::atoi(str.c_str());
		if (num < 0)
			throw std::runtime_error("Negative number");
		
		_vector.push_back(num);
		_deque.push_back(num);
	}
}

bool PmergeMe::isValidNumber(const std::string& str) const
{
	if (str.empty())
		return false;
	
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (!isdigit(str[i]))
			return false;
	}
	
	return true;
}

void PmergeMe::sort()
{
	display("Before: ", _vector);
	
	// Sort with vector
	std::clock_t start = std::clock();
	std::vector<int> vecCopy = _vector;
	fordJohnsonVector(vecCopy);
	std::clock_t end = std::clock();
	double vectorTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	
	// Sort with deque
	start = std::clock();
	std::deque<int> deqCopy = _deque;
	fordJohnsonDeque(deqCopy);
	end = std::clock();
	double dequeTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	
	display("After:  ", vecCopy);
	
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vector.size() 
	          << " elements with std::vector : " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() 
	          << " elements with std::deque  : " << dequeTime << " us" << std::endl;
}

void PmergeMe::display(const std::string& prefix, const std::vector<int>& vec) const
{
	std::cout << prefix;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i];
		if (i < vec.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

// Ford-Johnson merge-insert sort for vector
void PmergeMe::fordJohnsonVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;
	
	const size_t K = 16; // Threshold for insertion sort
	
	if (vec.size() <= K)
	{
		insertionSortVector(vec, 0, vec.size() - 1);
		return;
	}
	
	size_t mid = vec.size() / 2;
	mergeVector(vec, 0, mid, vec.size() - 1);
}

void PmergeMe::insertionSortVector(std::vector<int>& vec, size_t left, size_t right)
{
	for (size_t i = left + 1; i <= right; ++i)
	{
		int key = vec[i];
		size_t j = i;
		
		while (j > left && vec[j - 1] > key)
		{
			vec[j] = vec[j - 1];
			--j;
		}
		vec[j] = key;
	}
}

void PmergeMe::mergeVector(std::vector<int>& vec, size_t left, size_t mid, size_t right)
{
	std::vector<int> leftVec(vec.begin() + left, vec.begin() + mid);
	std::vector<int> rightVec(vec.begin() + mid, vec.begin() + right + 1);
	
	insertionSortVector(leftVec, 0, leftVec.size() - 1);
	insertionSortVector(rightVec, 0, rightVec.size() - 1);
	
	size_t i = 0, j = 0, k = left;
	
	while (i < leftVec.size() && j < rightVec.size())
	{
		if (leftVec[i] <= rightVec[j])
			vec[k++] = leftVec[i++];
		else
			vec[k++] = rightVec[j++];
	}
	
	while (i < leftVec.size())
		vec[k++] = leftVec[i++];
	
	while (j < rightVec.size())
		vec[k++] = rightVec[j++];
}

// Ford-Johnson merge-insert sort for deque
void PmergeMe::fordJohnsonDeque(std::deque<int>& deq)
{
	if (deq.size() <= 1)
		return;
	
	const size_t K = 16; // Threshold for insertion sort
	
	if (deq.size() <= K)
	{
		insertionSortDeque(deq, 0, deq.size() - 1);
		return;
	}
	
	size_t mid = deq.size() / 2;
	mergeDeque(deq, 0, mid, deq.size() - 1);
}

void PmergeMe::insertionSortDeque(std::deque<int>& deq, size_t left, size_t right)
{
	for (size_t i = left + 1; i <= right; ++i)
	{
		int key = deq[i];
		size_t j = i;
		
		while (j > left && deq[j - 1] > key)
		{
			deq[j] = deq[j - 1];
			--j;
		}
		deq[j] = key;
	}
}

void PmergeMe::mergeDeque(std::deque<int>& deq, size_t left, size_t mid, size_t right)
{
	std::deque<int> leftDeq(deq.begin() + left, deq.begin() + mid);
	std::deque<int> rightDeq(deq.begin() + mid, deq.begin() + right + 1);
	
	insertionSortDeque(leftDeq, 0, leftDeq.size() - 1);
	insertionSortDeque(rightDeq, 0, rightDeq.size() - 1);
	
	size_t i = 0, j = 0, k = left;
	
	while (i < leftDeq.size() && j < rightDeq.size())
	{
		if (leftDeq[i] <= rightDeq[j])
			deq[k++] = leftDeq[i++];
		else
			deq[k++] = rightDeq[j++];
	}
	
	while (i < leftDeq.size())
		deq[k++] = leftDeq[i++];
	
	while (j < rightDeq.size())
		deq[k++] = rightDeq[j++];
}