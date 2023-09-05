#include "credit.h"

#include "ui_credit.h"

s21::Credit::Credit(QWidget *parent, CreditController *c1)
    : QDialog(parent), controller_credit_(c1), ui_(new Ui::Credit) {
  ui_->setupUi(this);
  locale_ = QLocale(QLocale::Russian);

  connect(ui_->back, &QPushButton::clicked, this, &Credit::BackToMenu);
  connect(ui_->result_credit, &QPushButton::clicked, this,
          &Credit::ResultCredit);
}

s21::Credit::~Credit() { delete ui_; }

void s21::Credit::BackToMenu() {
  this->close();
  emit menu_two();
}

void s21::Credit::ResultCredit() {
  if (ui_->anuitetni->isChecked()) {
    controller_credit_->ProcessingAnnuitCredit(
        ui_->credit_amount->value(), ui_->term->value(), ui_->rate->value());
    ui_->monthly_payment->setText(
        locale_.toString(controller_credit_->get_monthly_payment(), 'f', 2));
    ui_->overpayment->setText(
        locale_.toString(controller_credit_->get_overpayment(), 'f', 2));
    ui_->total_payout->setText(
        locale_.toString(controller_credit_->get_total_payment(), 'f', 2));
  } else {
    controller_credit_->ProcessingDifferentiatedCredit(
        ui_->credit_amount->value(), ui_->term->value(), ui_->rate->value());

    ui_->overpayment->setText(
        locale_.toString(controller_credit_->get_overpayment(), 'f', 2));
    ui_->total_payout->setText(
        locale_.toString(controller_credit_->get_total_payment(), 'f', 2));
    std::list<double> result = controller_credit_->get_amount_result_data();
    ui_->monthly_payment->setText(locale_.toString(result.front(), 'f', 2) +
                                  "..." +
                                  locale_.toString(result.back(), 'f', 2));
  }
}
