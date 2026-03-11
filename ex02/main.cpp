/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:28:19 by rnovotny          #+#    #+#             */
/*   Updated: 2026/03/11 16:35:08 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	try
	{
		PmergeMe sorter(argc, argv);
		sorter.sort();
		sorter.display();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	
	return 0;
}