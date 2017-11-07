#include "stdafx.h"
#include "12_Windchill.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test12_Windchill
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(PerceivedTemperature1)
        {
            auto measuredTemp = 4;
            auto windSpeed = 10;
            auto expectedValue = -2;

            auto actualValue = perceivedTemperature(measuredTemp, windSpeed);

            Assert::AreEqual(expectedValue, actualValue);
        }

        TEST_METHOD(PerceivedTemperature2)
        {
            auto measuredTemp = -6;
            auto windSpeed = 10;
            auto expectedValue = -15;

            auto actualValue = perceivedTemperature(measuredTemp, windSpeed);

            Assert::AreEqual(expectedValue, actualValue);
        }
    };
}