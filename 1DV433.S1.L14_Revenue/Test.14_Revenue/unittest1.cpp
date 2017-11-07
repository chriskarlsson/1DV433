#include "stdafx.h"
#include "14_Revenue.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test14_Revenue
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(Revenue)
        {
            auto initialAmount = 1;
            auto years = 1;
            auto expectedValue = 1.03;

            auto actualValue = calculateTotal(initialAmount, years);

            Assert::AreEqual(expectedValue, actualValue, 0.000001);
        }

        TEST_METHOD(RevenueRoundUp)
        {
            auto initialAmount = 1000;
            auto years = 10;
            auto expectedValue = 1343.92; // Actual value 1343.9164...

            auto actualValue = calculateTotal(initialAmount, years);

            Assert::AreEqual(expectedValue, actualValue, 0.005);
        }

        TEST_METHOD(RevenueRoundDown)
        {
            auto initialAmount = 1000;
            auto years = 5;
            auto expectedValue = 1159.27; // Actual value 1159.2741...

            auto actualValue = calculateTotal(initialAmount, years);

            Assert::AreEqual(expectedValue, actualValue, 0.005);
        }
    };
}