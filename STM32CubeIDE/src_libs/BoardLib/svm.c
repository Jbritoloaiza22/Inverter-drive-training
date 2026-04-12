#include "svm.h"
#include "pwm.h"
#include "stm32g031xx.h"

#define dSQRT3 1.73205080757f

/**
 * @brief Clamp value between -1 and 1
 */
static float fSVM_clamp(float x)
{
    if (x > 1.0f) return 1.0f;
    if (x < -1.0f) return -1.0f;
    return x;
}

/**
 * @brief Initialize SVM module
 */
void vSVM_Init(void)
{
    /* Currently no additional configuration required */
}

/**
 * @brief αβ → abc transformation (Inverse Clarke)
 */
static void vSVM_AlphaBetaToABC(float alpha, float beta,
                               float *a, float *b, float *c)
{
    *a = alpha;
    *b = -0.5f * alpha + (dSQRT3 * 0.5f) * beta;
    *c = -0.5f * alpha - (dSQRT3 * 0.5f) * beta;
}

/**
 * @brief Normalize and center to 0..1 for PWM
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

    /* Scale to 0..1 */
    *a = (*a + 1.0f) * 0.5f;
    *b = (*b + 1.0f) * 0.5f;
    *c = (*c + 1.0f) * 0.5f;

    *a = fSVM_clamp(*a);
    *b = fSVM_clamp(*b);
    *c = fSVM_clamp(*c);
}

/**
 * @brief Update PWM using SVM
 */
void vSVM_Update(float Valpha, float Vbeta)
{
    float a, b, c;

    /* Clamp inputs */
    Valpha = fSVM_clamp(Valpha);
    Vbeta  = fSVM_clamp(Vbeta);

    /* Transform */
    vSVM_AlphaBetaToABC(Valpha, Vbeta, &a, &b, &c);

    /* Normalize */
    vSVM_normalize(&a, &b, &c);

    /* Convert to timer counts */
    uint32_t arr = TIM1->ARR;

    uint32_t dutyA = (uint32_t)(a * arr);
    uint32_t dutyB = (uint32_t)(b * arr);
    uint32_t dutyC = (uint32_t)(c * arr);

    /* Update PWM */
    vPWM_UpdatePhaseCompare(dutyA, dutyB, dutyC);
}