#include "svm.h"
#include "pwm.h"
#include "stm32g031xx.h"

#define dSQRT3 1.73205080757f

static float fSVM_clamp(float x)
{
    if (x > 1.0f) return 1.0f;
    if (x < -1.0f) return -1.0f;
    return x;
}

