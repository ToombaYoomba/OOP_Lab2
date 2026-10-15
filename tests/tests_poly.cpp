#include <gtest/gtest.h>
#include "polynomial.h"


TEST(StructTest, PrintPolynomial){
    double c1[] = {1.0, 2.0};       
    Polynomial a(c1, 1);
    testing::internal::CaptureStdout();
    a.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("1 + 2x\n"), std::string::npos);
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