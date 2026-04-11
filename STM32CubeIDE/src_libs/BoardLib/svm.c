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

void vSVM_Init(void)
{
    /* Currently no additional configuration required */
}

/**
 * αβ → abc transformation
 */
static void vSVM_AlphaBetaToABC(float alpha, float beta,
                                  float *a, float *b, float *c)
{
    *a = alpha;
    *b = -0.5f * alpha + (dSQRT3 * 0.5f) * beta;
    *c = -0.5f * alpha - (dSQRT3 * 0.5f) * beta;
}

