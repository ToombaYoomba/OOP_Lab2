#include <gtest/gtest.h>
#include "polynomial.h"


TEST(StructTest, DefaultEmptyPolynomial) {
    Polynomial empty(nullptr, -1);
    testing::internal::CaptureStdout();
    empty.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("0"), std::string::npos);
    EXPECT_EQ(empty.evaluate(5.0), 0.0);
}

TEST(StructTest, CopyViaEq){
    double c1[] = {1.0, 2.0};
    Polynomial a(c1, 1);
    Polynomial b = a;
    EXPECT_TRUE(a.is_equal(b, 1));
}

TEST(StructTest, MoveConstructor) {
    double c[] = {1.0, 2.0, 3.0};
    Polynomial a(c, 2);
    Polynomial b(std::move(a));
    double expected[] = {1.0, 2.0, 3.0};
    Polynomial exp(expected, 2);
    EXPECT_TRUE(b.is_equal(exp));
    EXPECT_EQ(a.evaluate(10.0), 0.0);
}

TEST(StructTest, PrintPolynomial){
    double c1[] = {1.0, 2.0};       
    Polynomial a(c1, 1);
    testing::internal::CaptureStdout();
    a.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("1 + 2x\n"), std::string::npos);
}

TEST(StructTest, PrintZeroCoefficients) {
    double c[] = {0.0, 0.0, 0.0, 5.0};
    Polynomial a(c, 3);
    testing::internal::CaptureStdout();
    a.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("5x^3"), std::string::npos);
    EXPECT_EQ(output.find("0 +"), std::string::npos);
}

TEST(StructTest, EvalPolynomial){
    double c1[] = {1.0, 2.0};
    Polynomial a(c1, 1);
    double res = a.evaluate(1);
    EXPECT_EQ(res, 3.0);
}

TEST(StructTest, AddPolynomial){
    double c1[] = {1.0, 2.0};
    double c2[] = {0.0, 1.0, 1.0};
    double expected[] = {1.0, 3.0, 1.0};
    Polynomial a(c1, 1);
    Polynomial b(c2, 2);
    Polynomial exp(expected, 2);

    a.add(b);
    EXPECT_TRUE(a.is_equal(exp));
}

TEST(StructTest, AddZeroPolynomial){
    double c1[] = {1.0, 2.0};
    double c2[] = {0.0};
    double expected[] = {1.0, 2.0};
    Polynomial a(c1, 1);
    Polynomial b(c2, 0);
    Polynomial exp(expected, 1);

    a.add(b);
    EXPECT_TRUE(a.is_equal(exp, 1));
}

TEST(StructTest, MulPolynomial){
    double c1[] = {1.0, 2.0};        
    double c2[] = {0.0, 1.0, 1.0};
    double expected[] = {0.0, 1.0, 3.0, 2.0};
    Polynomial a(c1, 1); 
    Polynomial b(c2, 2); 
    Polynomial exp(expected, 3); 
    a.mul(b);
    EXPECT_TRUE(a.is_equal(exp));
}

TEST(StructTest, MulByZeroPolynomial) {
    double c1[] = {1.0, 2.0, 3.0};
    double c2[] = {0.0};
    Polynomial a(c1, 2);
    Polynomial zero(c2, 0);
    a.mul(zero);
    EXPECT_EQ(a.evaluate(3.0), 0.0);
    EXPECT_TRUE(a.is_equal(zero));
}

TEST(StructTest, EqualPolynomialTrue){
    double c1[] = {0.0, 0.0, 1.0};
    double c2[] = {1e-6, 0.0, 1.0};
    Polynomial a(c1, 2); 
    Polynomial b(c2, 2); 
    EXPECT_TRUE(a.is_equal(b, 1e-4));
}

TEST(StructTest, EqualPolynomialFalse){
    double c1[] = {0.0, 0.0, 1.0};
    double c2[] = {1.0, 0.0, 1.0};
    Polynomial a(c1, 2); 
    Polynomial b(c2, 2); 
    EXPECT_FALSE(a.is_equal(b, 1e-4));
}