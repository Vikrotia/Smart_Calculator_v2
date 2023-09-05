#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QVector>

#include "../controller/controller.h"

namespace Ui {
class Calculator;
}

namespace s21 {
class Calculator : public QDialog {
  Q_OBJECT

 public:
  explicit Calculator(QWidget *parent = nullptr, MathController *m1 = nullptr);
  ~Calculator();

 signals:
  void menu_one();

 private:
  void BackToMenu();
  void ConnectButtons();
  void DigitNumbers();
  void MathOperations();
  void TrigonomOperations();
  void ACliced();
  void ProcesResult();
  void GraphPlay();
  void СoordinateСalculation(const std::string &expression, double x_min,
                             double x_max, double y_min, double y_max,
                             QVector<double> &x, QVector<double> &y);

  Ui::Calculator *ui_;
  MathController *controller_;
};
}  // namespace s21

#endif  // CALCULATOR_H
