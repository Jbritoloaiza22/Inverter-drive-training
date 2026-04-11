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

/**
 * Normalize and center to 0..1 for PWM
 */
static void vSVM_normalize(float *a, float *b, float *c)
{
    float vmax = *a;
    float vmin = *a;

    if (*b > vmax) vmax = *b;
    if (*c > vmax) vmax = *c;

    if (*b < vmin) vmin = *b;
    if (*c < vmin) vmin = *c;

    float offset = (vmax + vmin) * 0.5f;

    *a -= offset;
    *b -= offset;
    *c -= offset;

    /* Scale to range 0..1 */
    *a = (*a + 1.0f) * 0.5f;
    *b = (*b + 1.0f) * 0.5f;
    *c = (*c + 1.0f) * 0.5f;

    *a = fSVM_clamp(*a);
    *b = fSVM_clamp(*b);
    *c = fSVM_clamp(*c);
}

