#include "mathmodel.h"

void s21::MathModel::PrintStack() {
  while (!stack_expr_.empty()) {
    MathModel::element currentElement = stack_expr_.top();
    std::cout << "Value: " << currentElement.value_
              << ", Content: " << currentElement.content_ << std::endl;
    stack_expr_.pop();
  }
  std::cout << "Status: " << status_;
}

bool s21::MathModel::IsUnarySign() {
  return (it_ == expression_.begin() ||
          (it_ != expression_.begin() && *(it_ - 1) == '(')) &&
         (*it_ == '-' || *it_ == '+') &&
         (isdigit(*(it_ + 1)) || *(it_ + 1) == 'x') && it_ != expression_.end();
}

double s21::MathModel::ReadNumber() {
  unsigned int point = 0;
  std::string number;
  bool hasExponent = false;
  for (; IsUnarySign() || isdigit(*it_) || *it_ == '.' || *it_ == 'e'; ++it_) {
    if (*it_ == '.') {
      point++;
      if (point == 2) {
        status_ = false;
        return 0.0;
      }
    } else if (*it_ == 'e') {
      if (hasExponent) {
        status_ = false;
        return 0.0;
      }
      hasExponent = true;
      number += *it_;
      ++it_;
      if (*it_ == '-' || *it_ == '+') {
        number += *it_;
        ++it_;
      }
    }
    number += *it_;
  }
  --it_;
  try {
    return std::stod(number);
  } catch (const std::invalid_argument& error_convertation) {
    status_ = false;
    return 0.0;
  }
}

double s21::MathModel::ReadX() {
  double number = x_;
  if (IsUnarySign() && *it_ == '-') {
    number *= -1;
    ++it_;
  }
  return number;
}

bool s21::MathModel::IsX() {
  return (IsUnarySign() && it_ + 1 != expression_.end() && *(it_ + 1) == 'x') ||
         *it_ == 'x';
}

void s21::MathModel::PopOperatorsUntilOpenBracket() {
  while (!stack_oper_.empty() && stack_oper_.top().content_ != "open") {
    stack_expr_.push(stack_oper_.top());
    stack_oper_.pop();
  }
  if (stack_oper_.empty()) {
    status_ = false;
  } else {
    stack_oper_.pop();
  }
}

std::string s21::MathModel::ReadOperator() {
  std::string oper;
  while (isalpha(*it_) && it_ != expression_.end()) {
    oper += *it_;
    ++it_;
  }
  --it_;
  if (operations.find(oper) != operations.end()) {
    return oper;
  } else {
    status_ = false;
    return "";
  }
}

int s21::MathModel::GetOperatorPriority(std::string oper) {
  auto it_operations = operations.find(oper);
  if (it_operations != operations.end()) {
    return it_operations->second;
  } else {
    status_ = false;
    return 0;
  }
}

void s21::MathModel::ProcessHigherPriorityOperators(std::string oper) {
  while (!stack_oper_.empty() &&
         (GetOperatorPriority(stack_oper_.top().content_) >
              GetOperatorPriority(oper) ||
          (GetOperatorPriority(stack_oper_.top().content_) ==
               GetOperatorPriority(oper) &&
           (oper != "^")))) {
    stack_expr_.push(stack_oper_.top());
    stack_oper_.pop();
  }
  stack_oper_.emplace(0.0, oper);
}

bool s21::MathModel::IsMathematicalSign() const {
  const std::string mathematical_sign = "+-*/^%";
  return (mathematical_sign.find_first_of(*it_) != std::string::npos);
}

void s21::MathModel::CleanStackOper() {
  while (!stack_oper_.empty()) {
    stack_expr_.push(stack_oper_.top());
    stack_oper_.pop();
  }
}

void s21::MathModel::ConvertToPolishNotation() {
  for (it_ = expression_.begin(); it_ != expression_.end() && status_; ++it_) {
    double number = 0.0;
    if ((IsUnarySign() && isdigit(*(it_ + 1))) || isdigit(*it_)) {
      number = ReadNumber();
      stack_expr_.emplace(number, "number");
    } else if (IsX()) {
      number = ReadX();
      stack_expr_.emplace(number, "number");
    } else if (*it_ == '(') {
      if (*(it_ + 1) == ')') {
        status_ = 0;
      }
      stack_oper_.emplace(0.0, "open");
    } else if (*it_ == ')') {
      if (*(it_ + 1) == '(') {
        status_ = 0;
      }
      PopOperatorsUntilOpenBracket();
    } else if (isalpha(*it_)) {
      ProcessHigherPriorityOperators(ReadOperator());
    } else if (IsMathematicalSign()) {
      std::string operator_str(1, *it_);
      ProcessHigherPriorityOperators(operator_str);
    } else {
      status_ = false;
    }
  }
  CleanStackOper();
  expression_ = "\0";
}
void s21::MathModel::CalculateExpression() {
  std::stack<double> stack_value;
  double one_num = 0.0;
  double two_num = 0.0;
  while (!stack_expr_.empty()) {
    if (stack_expr_.top().content_ == "number") {
      stack_value.push(stack_expr_.top().value_);
      stack_expr_.pop();
    } else if (stack_expr_.top().content_.length() > 1) {
      one_num = stack_value.top();
      stack_value.pop();
      stack_value.push(
          EvaluateUnaryMathFunction(one_num, stack_expr_.top().content_));
      stack_expr_.pop();
    } else if (stack_expr_.top().content_.length() == 1) {
      if (stack_value.size() < 2) {
        status_ = false;
        return;
      }
      two_num = stack_value.top();
      stack_value.pop();
      one_num = stack_value.top();
      stack_value.pop();
      stack_value.push(
          EvaluateMathFunction(one_num, two_num, stack_expr_.top().content_));
      stack_expr_.pop();
    }
  }
  if (stack_value.size() != 1) {
    status_ = false;
    return;
  }
  calculated_result_ = stack_value.top();
  stack_value.pop();
  while (!stack_expr_.empty()) {
    stack_expr_.pop();
  }
  while (!stack_oper_.empty()) {
    stack_oper_.pop();
  }
}

double s21::MathModel::EvaluateUnaryMathFunction(double number,
                                                 std::string sign) {
  double result = 0.0;
  using MathFunction = double (*)(double);
  std::unordered_map<std::string, MathFunction> trigonom = {
      {"sin", sin},
      {"cos", cos},
      {"tan", tan},
      {"acos", std::acos},
      {"asin", std::asin},
      {"atan", atan},
      {"sqrt", [](double x) { return (x < 0) ? NAN : std::sqrt(x); }},
      {"ln", [](double x) { return (x <= 0) ? NAN : std::log(x); }},
      {"log", [](double x) { return (x <= 0) ? NAN : std::log10(x); }}};
  auto it = trigonom.find(sign);
  if (it != trigonom.end()) {
    result = it->second(number);
    if (std::isnan(result)) status_ = false;
  } else {
    status_ = false;
  }

  return result;
}

double s21::MathModel::EvaluateMathFunction(double number_1, double number_2,
                                            std::string sign) {
  double result = 0.0;
  if (sign.empty()) return result;
  using op_func = std::function<double(double, double)>;
  const static std::unordered_map<int, op_func> binary{
      {'+', std::plus<double>()},
      {'-', std::minus<double>()},
      {'*', std::multiplies<double>()},
      {'/', std::divides<double>()},
      {'%', fmodl},
      {'^', powl},
  };
  auto it = binary.find(sign[0]);
  if (it != binary.end()) {
    result = binary.at(sign[0])(number_1, number_2);
    if (std::isnan(result)) status_ = false;
  } else {
    status_ = false;
  }
  return result;
}

void s21::MathModel::InverseStack() {
  std::stack<element> tmpStack;

  while (!stack_expr_.empty()) {
    tmpStack.push(stack_expr_.top());
    stack_expr_.pop();
  }

  stack_expr_ = std::move(tmpStack);
}

double s21::MathModel::get_calculated_result() const {
  return calculated_result_;
}

bool s21::MathModel::get_status() const { return status_; }

bool s21::MathModel::Prossesing(std::string st, double x) {
  status_ = true;
  expression_ = st;
  x_ = x;
  ConvertToPolishNotation();
  if (status_) {
    InverseStack();
    CalculateExpression();
  }
  if (!stack_expr_.empty()) {
    stack_expr_.pop();
  }
  if (!stack_oper_.empty()) {
    stack_oper_.pop();
  }
  expression_ = "\0";
  return get_status();
}
