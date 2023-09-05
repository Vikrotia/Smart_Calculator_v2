#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "calculator.h"
#include "credit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, MathController *m1 = nullptr,
             CreditController *c1 = nullptr);
  ~MainWindow();

 private slots:
  void ProCalculator();
  void CreditCalculator();

 private:
  Ui::MainWindow *ui_;
  Calculator *calc_;
  Credit *credit_;
  MathController *m_;
  CreditController *c_;
};

}  // namespace s21
#endif  // MAINWINDOW_H
