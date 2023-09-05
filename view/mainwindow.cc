#include "mainwindow.h"

#include "ui_mainwindow.h"

s21::MainWindow::MainWindow::MainWindow(QWidget *parent, MathController *m1,
                                        CreditController *c1)
    : QMainWindow(parent), m_(m1), c_(c1), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  calc_ = new Calculator(nullptr, m_);
  connect(calc_, &Calculator::menu_one, this, &MainWindow::show);

  connect(ui_->calculator, &QPushButton::clicked, this,
          &MainWindow::ProCalculator);

  credit_ = new Credit(nullptr, c_);
  connect(credit_, &Credit::menu_two, this, &MainWindow::show);

  connect(ui_->credit, &QPushButton::clicked, this,
          &MainWindow::CreditCalculator);
}

s21::MainWindow::~MainWindow() {
  delete ui_;
  delete credit_;
  delete calc_;
}

void s21::MainWindow::ProCalculator() {
  calc_->show();
  this->close();
}

void s21::MainWindow::CreditCalculator() {
  credit_->show();
  this->close();
}
