#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
#include <QLocale>

#include "../controller/controller.h"

namespace Ui {
class Credit;
}

namespace s21 {
class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr, CreditController *c1 = nullptr);
  ~Credit();

 signals:
  void menu_two();

 private:
  Ui::Credit *ui_;
  QLocale locale_;

  void BackToMenu();
  void ResultCredit();

  CreditController *controller_credit_;
};
}  // namespace s21

#endif  // CREDIT_H
