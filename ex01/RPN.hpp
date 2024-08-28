/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:26:21 by ranki             #+#    #+#             */
/*   Updated: 2024/08/27 22:32:40 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN {
public:
    RPN(const std::string& expression);
    int evaluate();
    
private:
    std::stack<int> stack;
    std::string expression;
    
    void parseInput() const;
    void processToken(const std::string& token);
    bool isOperator(const std::string& token) const;
    int applyOperator(const std::string& op, int a, int b) const;
};

#endif
