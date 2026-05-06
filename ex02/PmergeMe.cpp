/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:29:42 by rnovotny          #+#    #+#             */
/*   Updated: 2026/05/06 15:37:18 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

PmergeMe::PmergeMe()
#ifdef COUNT_COMPARISONS
	: _vecComparisons(0), _deqComparisons(0)
#endif
{}

PmergeMe::PmergeMe(int argc, char** argv)
#ifdef COUNT_COMPARISONS
	: _vecComparisons(0), _deqComparisons(0)
#endif
{
	parseInput(argc, argv);
}

PmergeMe::PmergeMe(const PmergeMe& other) : _vector(other._vector), _deque(other._deque)
#ifdef COUNT_COMPARISONS
	, _vecComparisons(other._vecComparisons), _deqComparisons(other._deqComparisons)
#endif
{}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_deque = other._deque;
#ifdef COUNT_COMPARISONS
		_vecComparisons = other._vecComparisons;
		_deqComparisons = other._deqComparisons;
#endif
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
	
#ifdef COUNT_COMPARISONS
	_vecComparisons = 0;
#endif
	// Sort with vector
	std::clock_t start = std::clock();
	std::vector<int> vecCopy = _vector;
	fordJohnsonVector(vecCopy);
	std::clock_t end = std::clock();
	double vectorTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
	
#ifdef COUNT_COMPARISONS
	_deqComparisons = 0;
#endif
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
#ifdef COUNT_COMPARISONS
	std::cout << "Comparisons (vector): " << _vecComparisons << std::endl;
	std::cout << "Comparisons (deque):  " << _deqComparisons << std::endl;
#endif
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

// Generates Jacobsthal numbers up to n: 0,1,3,5,11,21,43,...
// Used to determine the insertion order of pend elements.
std::vector<size_t> PmergeMe::jacobsthalSequence(size_t n) const
{
	std::vector<size_t> seq;
	if (n == 0) return seq;
	size_t a = 0, b = 1;
	while (b <= n)
	{
		seq.push_back(b);
		size_t c = b + 2 * a;
		a = b;
		b = c;
	}
	return seq;
}

// Binary search insert: insert val into chain[0..end-1] (end is exclusive upper bound)
void PmergeMe::binaryInsertVector(std::vector<int>& chain, int val, size_t end)
{
	size_t lo = 0, hi = end;
	while (lo < hi)
	{
		size_t mid = lo + (hi - lo) / 2;
#ifdef COUNT_COMPARISONS
		++_vecComparisons;
#endif
		if (chain[mid] < val)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(chain.begin() + lo, val);
}

void PmergeMe::fordJohnsonVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;

	// Step 1: pair up elements, sort each pair so larger -> main, smaller -> pend.
	// Store pairs as (pend, main) so we can track which main goes with which pend.
	bool hasStraggler = (vec.size() % 2 != 0);
	int straggler = hasStraggler ? vec.back() : 0;
	size_t numPairs = vec.size() / 2;

	std::vector<std::pair<int,int> > pairs; // (smaller, larger)
	for (size_t i = 0; i < numPairs; ++i)
	{
		int a = vec[2 * i], b = vec[2 * i + 1];
#ifdef COUNT_COMPARISONS
		++_vecComparisons;
#endif
		if (a > b) std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	// Step 2: recursively sort just the larger (main) elements.
	std::vector<int> main_chain;
	for (size_t i = 0; i < pairs.size(); ++i)
		main_chain.push_back(pairs[i].second);
	fordJohnsonVector(main_chain);

	// Step 3: build pend vector in the order that reflects the sorted main_chain.
	// After sorting, main_chain[i] = some pairs[j].second.
	// We need pend[i] = the smaller element paired with main_chain[i].
	std::vector<int> pend;
	for (size_t i = 0; i < main_chain.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].second == main_chain[i])
			{
				pend.push_back(pairs[j].first);
				pairs[j].second = -1; // mark used (handle duplicates)
				break;
			}
		}
	}

	// Step 4: pend[0] is <= main_chain[0] (its pair partner is now at index 0).
	// Prepend it with no comparisons needed.
	main_chain.insert(main_chain.begin(), pend[0]);

	// Step 5: Add straggler to pend if it exists.
	// By adding it to the end, we make sure it gets inserted in the correct position in the next step.
	if (hasStraggler)
    	pend.push_back(straggler);

	// Step 6: insert remaining pend in Jacobsthal group order (TAOCP 5.3.1 eq.11-16).
	// Thresholds t[] = [1, 3, 5, 11, 21, ...]. Group r covers pend[t[r]..t[r+1]-1],
	// inserted high-to-low. Bound = 2^(r+2)-1: the chain up to the first element's
	// partner has exactly that many entries, so binary search costs <= r+2 comparisons.
	{
		std::vector<size_t> t;
		t.push_back(1);
		{
			size_t a = 1, b = 3;
			while (t.back() < pend.size())
			{
				t.push_back(b);
				size_t c = b + 2 * a;
				a = b;
				b = c;
			}
		}
		for (size_t r = 0; r + 1 < t.size(); ++r)
		{
			size_t bound = (size_t(1) << (r + 2)) - 1;
			size_t lo = t[r];
			size_t hi = t[r + 1] - 1;
			if (lo >= pend.size()) break;
			if (hi >= pend.size()) hi = pend.size() - 1;
			for (size_t k = hi; k >= lo; --k)
			{
				size_t cap = bound < main_chain.size() ? bound : main_chain.size();
				binaryInsertVector(main_chain, pend[k], cap);
				if (k == 0) break;
			}
		}
	}

	vec = main_chain;
}

// --- Deque version (identical logic) ---

void PmergeMe::binaryInsertDeque(std::deque<int>& chain, int val, size_t end)
{
	size_t lo = 0, hi = end;
	while (lo < hi)
	{
		size_t mid = lo + (hi - lo) / 2;
#ifdef COUNT_COMPARISONS
		++_deqComparisons;
#endif
		if (chain[mid] < val)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(chain.begin() + lo, val);
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& deq)
{
	if (deq.size() <= 1)
		return;

	bool hasStraggler = (deq.size() % 2 != 0);
	int straggler = hasStraggler ? deq.back() : 0;
	size_t numPairs = deq.size() / 2;

	std::vector<std::pair<int,int> > pairs;
	for (size_t i = 0; i < numPairs; ++i)
	{
		int a = deq[2 * i], b = deq[2 * i + 1];
#ifdef COUNT_COMPARISONS
		++_deqComparisons;
#endif
		if (a > b)
			std::swap(a, b);
		pairs.push_back(std::make_pair(a, b));
	}

	std::deque<int> main_chain;
	for (size_t i = 0; i < pairs.size(); ++i)
		main_chain.push_back(pairs[i].second);
	fordJohnsonDeque(main_chain);

	std::deque<int> pend;
	for (size_t i = 0; i < main_chain.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].second == main_chain[i])
			{
				pend.push_back(pairs[j].first);
				pairs[j].second = -1;
				break;
			}
		}
	}

	main_chain.insert(main_chain.begin(), pend[0]);
	if (hasStraggler)
    	pend.push_back(straggler);

	{
		std::vector<size_t> t;
		t.push_back(1);
		{
			size_t a = 1, b = 3;
			while (t.back() < pend.size())
			{
				t.push_back(b);
				size_t c = b + 2 * a;
				a = b;
				b = c;
			}
		}
		for (size_t r = 0; r + 1 < t.size(); ++r)
		{
			size_t bound = (size_t(1) << (r + 2)) - 1;
			size_t lo = t[r];
			size_t hi = t[r + 1] - 1;
			if (lo >= pend.size()) break;
			if (hi >= pend.size()) hi = pend.size() - 1;
			for (size_t k = hi; k >= lo; --k)
			{
				size_t cap = bound < main_chain.size() ? bound : main_chain.size();
				binaryInsertDeque(main_chain, pend[k], cap);
				if (k == 0) break;
			}
		}
	}

	deq = main_chain;
}