#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MathModel m;
  s21::CreditModel c;
  s21::MathController cm(m);
  s21::CreditController cc(c);
  s21::MainWindow w(nullptr, &cm, &cc);
  w.show();
  return a.exec();
}
