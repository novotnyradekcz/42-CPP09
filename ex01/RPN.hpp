/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:29:27 by rnovotny          #+#    #+#             */
/*   Updated: 2026/03/11 16:35:08 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

class RPN
{
private:
	std::stack<int> _stack;
	
	RPN();
	
public:
	RPN(const std::string& expression);
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();
	
	int calculate();
	
private:
	bool isOperator(char c) const;
	bool isNumber(const std::string& token) const;
	int performOperation(int a, int b, char op);
};

#endif