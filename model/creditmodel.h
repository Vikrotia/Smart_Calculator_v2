#ifndef CPP3_SMARTCALC_V2_SRC_CREDITMODEL_H
#define CPP3_SMARTCALC_V2_SRC_CREDITMODEL_H

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <list>
#include <stack>
#include <string>

namespace s21 {

class CreditModel {
 public:
  struct CreditStatistics {
    double result_amount_per_month = 0.0;
  };

 private:
  double credit_amount_ = 0.0;
  int term_ = 0;
  double interest_rate_ = 0.0;
  double monthly_payment_ = 0.0;
  double total_payment_ = 0.0;
  double overpayment_ = 0.0;
  std::list<double> amount_result_data_;

 public:
  void ProcessingAnnuitCredit();
  void ProcessingDifferentiatedCredit();

  void set_credit_model_variable(double c_a, int t, double i_r);
  double get_monthly_payment() const;
  double get_total_payment() const;
  double get_overpayment() const;
  int get_term() const;
  std::list<double> get_amount_result_data() const;
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_SRC_CREDITMODEL_H
