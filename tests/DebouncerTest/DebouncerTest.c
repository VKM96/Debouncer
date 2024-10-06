#include <unity.h>
#include <stdbool.h>
#include "Debounce.h"

void setUp (void)
{

}

void tearDown (void)
{

}

void DebounceTest_DummyTrue()
{
    TEST_ASSERT(true);
}

void DebounceTest_DummyFalse()
{
    TEST_ASSERT(true);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(DebounceTest_DummyTrue);
    RUN_TEST(DebounceTest_DummyFalse);

    return UNITY_END();
}