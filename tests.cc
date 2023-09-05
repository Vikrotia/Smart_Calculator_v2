#include <gtest/gtest.h>

#include "Model/mathmodel.h"

class ModelCalcTest : public ::testing::Test {
 protected:
  s21::MathModel calculator_test;
};

TEST_F(ModelCalcTest, SimpleCalc1) {
  calculator_test.Prossesing("5+3+2+5+5+1+2+3+4+5+6+7+8+9", 0);
  ASSERT_DOUBLE_EQ(calculator_test.get_calculated_result(), 65);
}

TEST_F(ModelCalcTest, SimpleCalc2) {
  calculator_test.Prossesing("5-3-2-5-5-1-2-3-4-5-6-7-8-9", 0);
  ASSERT_DOUBLE_EQ(calculator_test.get_calculated_result(), -55);
}

TEST_F(ModelCalcTest, SimpleCalc3) {
  calculator_test.Prossesing("5143*1213*24532/1213/1445", 0);
  ASSERT_NEAR(calculator_test.get_calculated_result(), 87313.5474048, 1e-7);
}

TEST_F(ModelCalcTest, SimpleCalc4) {
  calculator_test.Prossesing(
      "1.23456789+2.34567890-3.45678901*4.56789012/5.67890123", 0);
  ASSERT_NEAR(calculator_test.get_calculated_result(), 0.79973842646, 1e-7);
}

TEST_F(ModelCalcTest, SimpleCalc5) {
  calculator_test.Prossesing("5", 0);
  ASSERT_DOUBLE_EQ(calculator_test.get_calculated_result(), 5);
}

TEST_F(ModelCalcTest, SimpleCalc6) {
  calculator_test.Prossesing("2^3^2", 0);
  ASSERT_DOUBLE_EQ(calculator_test.get_calculated_result(), 512);
}

TEST_F(ModelCalcTest, SimpleCalc7) {
  calculator_test.Prossesing("5*x", 6);
  ASSERT_DOUBLE_EQ(calculator_test.get_calculated_result(), 30);
}

TEST_F(ModelCalcTest, SimpleCalc8) {
  calculator_test.Prossesing("2+x/x-x*(x%x)", 3);
  ASSERT_DOUBLE_EQ(calculator_test.get_calculated_result(), 3);
}

TEST_F(ModelCalcTest, HardCalc1) {
  calculator_test.Prossesing(
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))",
      3);
  ASSERT_NEAR(calculator_test.get_calculated_result(), -30.0721649, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc2) {
  calculator_test.Prossesing("cos(2-sin(3+0.26*7+1))", 3);
  ASSERT_NEAR(calculator_test.get_calculated_result(), -0.7681865, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc3) {
  calculator_test.Prossesing("10*(-5+log(2+(9/3)))", 3);
  ASSERT_NEAR(calculator_test.get_calculated_result(), -43.0102999, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc4) {
  calculator_test.Prossesing("asin(0.8)+63/(log(8)%7)", 3);
  std::cout << "\n" << calculator_test.get_calculated_result() << "\n";
  std::cout << "\n" << calculator_test.get_status() << "\n";
  ASSERT_NEAR(calculator_test.get_calculated_result(), 70.687785, 1e-6);
}

TEST_F(ModelCalcTest, HardCalc5) {
  calculator_test.Prossesing(
      "acos((0+1))+asin(sqrt(81)-8.321)-atan(123%(5-2)+0.123)", 3);
  ASSERT_NEAR(calculator_test.get_calculated_result(), 0.624014352, 1e-7);
}

TEST_F(ModelCalcTest, HardCalc6) {
  calculator_test.Prossesing("sin(sin(sin(sin(sin(90)))))", 3);
  ASSERT_NEAR(calculator_test.get_calculated_result(), 0.6023926, 1e-7);
}

TEST_F(ModelCalcTest, ErrorCalc1) {
  ASSERT_EQ(calculator_test.Prossesing("", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc2) {
  ASSERT_EQ(calculator_test.Prossesing("5+(3", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc3) {
  ASSERT_EQ(calculator_test.Prossesing("5)+3", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc4) {
  ASSERT_EQ(calculator_test.Prossesing("01%", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc5) {
  ASSERT_EQ(calculator_test.Prossesing("1+()2", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc6) {
  ASSERT_EQ(calculator_test.Prossesing("1+(+-2)", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc7) {
  ASSERT_EQ(calculator_test.Prossesing("*", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc8) {
  ASSERT_EQ(calculator_test.Prossesing("(^)", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc9) {
  ASSERT_EQ(calculator_test.Prossesing(")2+3(", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc10) {
  ASSERT_EQ(calculator_test.Prossesing("2..3", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc11) {
  ASSERT_EQ(calculator_test.Prossesing("7.1*2.3.2", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc12) {
  ASSERT_EQ(calculator_test.Prossesing("5+.2", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc13) {
  ASSERT_EQ(calculator_test.Prossesing("asin(100)", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc14) {
  ASSERT_EQ(calculator_test.Prossesing("%3", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc15) {
  ASSERT_EQ(calculator_test.Prossesing("000.2", 3), 1);
}

TEST_F(ModelCalcTest, ErrorCalc16) {
  ASSERT_EQ(calculator_test.Prossesing("cos(*tan(2))", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc17) {
  ASSERT_EQ(calculator_test.Prossesing("5x", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc18) {
  ASSERT_EQ(calculator_test.Prossesing("xxxx", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc19) {
  ASSERT_EQ(calculator_test.Prossesing("xsin(3)", 3), 0);
}

TEST_F(ModelCalcTest, ErrorCalc20) {
  ASSERT_EQ(calculator_test.Prossesing("x.", 3), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}