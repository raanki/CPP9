/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:26:23 by ranki             #+#    #+#             */
/*   Updated: 2024/08/28 10:24:32 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <iostream>

RPN::RPN(const std::string& expr) : expression(expr) {
  parseInput();
}

void RPN::parseInput() const {
    if (expression.empty()) {
        throw std::runtime_error("Error");
    }

    std::istringstream tokens(expression);
    std::string token;

    while (tokens >> token) {
        if (isOperator(token)) {
            continue;
        } 

        if (token.length() == 1 && std::isdigit(token[0])) {
            int number = token[0] - '0';
            if (number < 0 || number >= 10) {
                throw std::runtime_error("Error");
            }
        } else {
            throw std::runtime_error("Error");
        }
    }
}

int RPN::evaluate() {
    std::istringstream tokens(expression);
    std::string token;
    
    while (tokens >> token) {
        processToken(token);
    }
    
    if (stack.size() != 1) {
        throw std::runtime_error("Error: invalid expression");
    }
    
    return stack.top();
}

void RPN::processToken(const std::string& token) {
    if (isOperator(token)) {
      
        if (stack.size() < 2) {
            throw std::runtime_error("Error: invalid expression");
        }
        
        int b = stack.top();
        stack.pop();
        
        int a = stack.top();
        stack.pop();

        int result = applyOperator(token, a, b);
        stack.push(result);

    } else {
        std::istringstream iss(token);
        int number;
        if (!(iss >> number)) {
            throw std::runtime_error("Error: invalid number");
        }
        stack.push(number);
    }
}

bool RPN::isOperator(const std::string& token) const {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::applyOperator(const std::string& op, int a, int b) const {
  if (op == "+")
    return a + b;
  if (op == "-")
    return a - b;
  if (op == "*")
    return a * b;
  if (op == "/")
  {
    if (b == 0)
    {
      throw std::runtime_error("Error: division by zero");
    }
    return a / b;
    }
    throw std::runtime_error("Error: unknown operator");
}
