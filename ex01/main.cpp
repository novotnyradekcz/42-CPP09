/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:28:19 by rnovotny          #+#    #+#             */
/*   Updated: 2026/05/06 19:36:53 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Invalid number of arguments. Usage: ./RPN <expression>" << std::endl;
		return 1;
	}
	
	try
	{
		RPN rpn(argv[1]);
		long result = rpn.calculate();
		std::cout << result << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}