#include "controller.h"

bool s21::MathController::ProcessingCalculation(const std::string& st,
                                                double x) {
  return math_model_.Prossesing(st, x);
}

bool s21::MathController::get_status() { return math_model_.get_status(); }
double s21::MathController::get_result() {
  return math_model_.get_calculated_result();
}

void s21::CreditController::ProcessingAnnuitCredit(double c_a, int t,
                                                   double i_r) {
  credit_model_.set_credit_model_variable(c_a, t, i_r);
  return credit_model_.ProcessingAnnuitCredit();
}
void s21::CreditController::ProcessingDifferentiatedCredit(double c_a, int t,
                                                           double i_r) {
  credit_model_.set_credit_model_variable(c_a, t, i_r);
  return credit_model_.ProcessingDifferentiatedCredit();
}

double s21::CreditController::get_monthly_payment() {
  return credit_model_.get_monthly_payment();
}

double s21::CreditController::get_total_payment() {
  return credit_model_.get_total_payment();
}

double s21::CreditController::get_overpayment() {
  return credit_model_.get_overpayment();
}

int s21::CreditController::get_term() { return credit_model_.get_term(); }

std::list<double> s21::CreditController::get_amount_result_data() {
  return credit_model_.get_amount_result_data();
}
