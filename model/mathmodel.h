#ifndef CPP3_SMARTCALC_V2_SRC_MATHMODEL_H
#define CPP3_SMARTCALC_V2_SRC_MATHMODEL_H

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

namespace s21 {
class MathModel {
 private:
  struct element;
  std::string expression_;
  std::string::iterator it_;
  double x_ = 0.0;
  bool status_ = true;
  double calculated_result_ = 0.0;

  struct element {
    double value_;
    std::string content_;

    element(double val, std::string con)
        : value_(val), content_(std::move(con)) {}
  };

  std::stack<element> stack_expr_;
  std::stack<element> stack_oper_;

  const std::string mathematical_sign = "+-*/^%";
  std::unordered_map<std::string, int> operations = {
      {"sin", 3},    {"cos", 3},  {"tg", 3}, {"acos", 4}, {"asin", 4},
      {"atan", 4},   {"sqrt", 4}, {"ln", 2}, {"log", 3},  {"^", 3},
      {"*", 2},      {"/", 2},    {"%", 2},  {"+", 1},    {"-", 1},
      {"number", 0}, {"open", -1}};

  void PrintStack();
  void ConvertToPolishNotation();
  bool IsUnarySign();
  bool IsX();
  bool IsMathematicalSign() const;
  void PopOperatorsUntilOpenBracket();
  void ProcessHigherPriorityOperators(std::string oper);
  void CleanStackOper();
  int GetOperatorPriority(std::string oper);
  double ReadNumber();
  double ReadX();
  std::string ReadOperator();
  void CalculateExpression();
  double EvaluateUnaryMathFunction(double number, std::string sign);
  double EvaluateMathFunction(double number_1, double number_2,
                              std::string sign);
  void InverseStack();

 public:
  bool Prossesing(std::string st, double x);
  double get_calculated_result() const;
  bool get_status() const;
};

}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_SRC_MATHMODEL_H