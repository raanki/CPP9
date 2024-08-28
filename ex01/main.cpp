/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:26:16 by ranki             #+#    #+#             */
/*   Updated: 2024/08/28 10:25:40 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <string>

void runTests();

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
        return 1;
    }

    if (std::string(argv[1]) == "-t") {
      runTests();
      return 0;
    }

    try {
        RPN rpn(argv[1]);
        int result = rpn.evaluate();
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}


void runTests() {
    struct TestCase {
        std::string expression;
        int expectedResult;
    };

    TestCase testCases[] = {
        {"8 9 * 9 - 9 - 9 - 4 - 1 +", 42},
        {"7 7 * 7 -", 42},
        {"1 2 * 2 / 2 * 2 4 - +", 0},
        {"3 4 + 2 * 7 /", 2},
        {"5 1 2 + 4 * + 3 -", 14},
        {"3 5 8 * 7 + * 2 -", 139},
        {"9 3 / 2 * 4 2 + *", 36},
        {"6 5 2 3 + 8 * + 3 + *", 288},
        {"2 3 + 4 * 5 + 6 7 + *", 325},
        {"2 3 4 * + 5 6 * + 7 +", 51},
        {"9 2 + 3 * 4 5 + 6 * +", 87},
        {"7 4 5 + * 2 3 + 6 * +", 93}, 
        {"1 4 3 + 2 * -", -13}, 
        {"5 1 2 + 4 * + 3 -", 14},
        {"8 2 5 * + 1 3 2 * + 4 + -", 7},
        {"7 9 + 8 + 3 + 2 + 5 + 6 + 8 + 9 + 8 - 5 - 6 - 9 8 * 9 * 6 * 5 * - 5 + 4 + 7 + 8 5 / 6 / + 5 - 7 -", -19398}    
    };

    for (size_t i = 0; i < sizeof(testCases) / sizeof(TestCase); ++i) {
      try {
          RPN rpn(testCases[i].expression);
          int result = rpn.evaluate();
          if (result == testCases[i].expectedResult) {
              std::cout << "✅ Test " << i + 1 << " passed!" << std::endl;
          } else {
              std::cout << "❌ Test " << i + 1 << " failed: expected " 
                        << testCases[i].expectedResult << " but got " << result << std::endl;
          }
      } catch (const std::exception& e) {
          std::cerr << "❌ Test " << i + 1 << " failed with error: " << e.what() << std::endl;
      }
    }

}