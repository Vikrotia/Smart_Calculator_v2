#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_H
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_H
#include "../model/creditmodel.h"
#include "../model/mathmodel.h"

namespace s21 {

class MathController {
 private:
  MathModel math_model_;

 public:
  MathController(MathModel math) : math_model_(math){};

  bool ProcessingCalculation(const std::string& st, double x);
  bool get_status();
  double get_result();
};

class CreditController {
 private:
  CreditModel credit_model_;

 public:
  CreditController(CreditModel cred) : credit_model_(cred){};

  void ProcessingAnnuitCredit(double c_a, int t, double i_r);
  void ProcessingDifferentiatedCredit(double c_a, int t, double i_r);
  double get_monthly_payment();
  double get_total_payment();
  double get_overpayment();
  int get_term();
  std::list<double> get_amount_result_data();
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_H
