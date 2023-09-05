#include "calculator.h"

#include "ui_calculator.h"

s21::Calculator::Calculator(QWidget* parent, MathController* m1)
    : QDialog(parent), controller_(m1), ui_(new Ui::Calculator) {
  ui_->setupUi(this);
  ui_->label->setFocus();

  connect(ui_->back, &QPushButton::clicked, this, &Calculator::BackToMenu);
  ConnectButtons();
}

s21::Calculator::~Calculator() { delete ui_; }

void s21::Calculator::BackToMenu() {
  ui_->label->setText("0");
  this->close();
  emit menu_one();
}

void s21::Calculator::ConnectButtons() {
  for (auto button : ui_->digits->buttons()) {
    connect(button, &QPushButton::clicked, this, &Calculator::DigitNumbers);
  }

  for (auto button : ui_->math_operations->buttons()) {
    connect(button, &QPushButton::clicked, this, &Calculator::MathOperations);
  }

  for (auto button : ui_->trig_operations->buttons()) {
    connect(button, &QPushButton::clicked, this,
            &Calculator::TrigonomOperations);
  }

  connect(ui_->ac, &QPushButton::clicked, this, &Calculator::ACliced);
  connect(ui_->result, &QPushButton::clicked, this, &Calculator::ProcesResult);
  connect(ui_->graph, &QPushButton::clicked, this, &Calculator::GraphPlay);
}

void s21::Calculator::DigitNumbers() {
  QPushButton* button = (QPushButton*)sender();
  QString new_label = "\0";
  if (ui_->label->text() == "0") {
    new_label = button->text();
  } else {
    new_label = ui_->label->text() + button->text();
  }
  ui_->label->setText(new_label);
}

void s21::Calculator::MathOperations() {
  QPushButton* button = static_cast<QPushButton*>(sender());
  QString buttonText = button->text();
  QString new_label;
  new_label = ui_->label->text() + button->text();
  ui_->label->setText(new_label);
}

void s21::Calculator::TrigonomOperations() {
  QPushButton* button = (QPushButton*)sender();
  QString new_label = "\0";
  if (ui_->label->text() == "0") {
    new_label = button->text() + "(";
  } else {
    new_label = ui_->label->text() + button->text() + "(";
  }
  ui_->label->setText(new_label);
}

void s21::Calculator::ACliced() { ui_->label->setText(""); }

void s21::Calculator::ProcesResult() {
  std::string str = ui_->label->text().toStdString();
  double x = ui_->result_x->value();
  bool status = controller_->ProcessingCalculation(str, x);
  double result = controller_->get_result();
  QString num = QString::number(result, 'f', 6);
  if (!status) {
    ui_->label->setText("Incorrect expression");
  } else {
    ui_->label->setText(num);
  }
}

void s21::Calculator::GraphPlay() {
  std::string expression = ui_->label->text().toStdString();
  double x_min = ui_->x_min->value();
  double x_max = ui_->x_max->value();
  double y_min = ui_->y_min->value();
  double y_max = ui_->y_max->value();
  if (x_min >= x_max || y_min >= y_max) {
    return;
  }
  QVector<double> x, y;
  СoordinateСalculation(expression, x_min, x_max, y_min, y_max, x, y);
  ui_->graf->clearGraphs();
  ui_->graf->addGraph();
  ui_->graf->graph(0)->setData(x, y);
  ui_->graf->xAxis->setLabel("x");
  ui_->graf->yAxis->setLabel("y");
  ui_->graf->xAxis->setRange(x_min, x_max);
  ui_->graf->yAxis->setRange(y_min, y_max);
  ui_->graf->replot();
}

void s21::Calculator::СoordinateСalculation(const std::string& expression,
                                            double x_min, double x_max,
                                            double y_min, double y_max,
                                            QVector<double>& x,
                                            QVector<double>& y) {
  double h = (x_max - x_min) / 1500;
  x.clear();
  y.clear();
  double X = 0.0;
  for (X = x_min; X <= x_max; X += h) {
    bool error = controller_->ProcessingCalculation(expression, X);
    double Y = controller_->get_result();
    if (error && Y <= y_max && Y >= y_min) {
      x.push_back(X);
      y.push_back(Y);
    }
  }
}
