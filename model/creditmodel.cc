#include "creditmodel.h"

void s21::CreditModel::set_credit_model_variable(double c_a, int t,
                                                 double i_r) {
  credit_amount_ = c_a;
  term_ = t;
  interest_rate_ = i_r;
};

void s21::CreditModel::ProcessingAnnuitCredit() {
  double prosnt = interest_rate_ / 100.0 / 12.0;
  monthly_payment_ =
      credit_amount_ *
      (prosnt * (pow(1 + prosnt, term_) / (pow(1 + prosnt, term_) - 1)));
  total_payment_ = monthly_payment_ * term_;
  overpayment_ = total_payment_ - credit_amount_;
}

void s21::CreditModel::ProcessingDifferentiatedCredit() {
  overpayment_ = 0.0;
  total_payment_ = 0.0;
  double prosnt = interest_rate_ / 100.0 / 12.0;
  amount_result_data_.clear();
  double d = credit_amount_ / term_;
  int n = term_;

  for (int i = 0; i < n; i++) {
    term_--;
    double result_amount_per_month_ =
        (d) + ((credit_amount_) - (d) * (term_)) * (prosnt);

    double tmp = {result_amount_per_month_};
    amount_result_data_.push_front(tmp);
    overpayment_ += result_amount_per_month_ - d;
  }
  total_payment_ = credit_amount_ + overpayment_;
}

double s21::CreditModel::get_monthly_payment() const {
  return monthly_payment_;
}

double s21::CreditModel::get_total_payment() const { return total_payment_; }

double s21::CreditModel::get_overpayment() const { return overpayment_; }

int s21::CreditModel::get_term() const { return term_; }

std::list<double> s21::CreditModel::get_amount_result_data() const {
  return amount_result_data_;
}
