/*
* Simd Library (http://ermig1979.github.io/Simd).
*
* Copyright (c) 2011-2019 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "Simd/SimdMergedConvolution.h"
#include "Simd/SimdConvolutionCommon.h"
#include "Simd/SimdUpdate.h"

namespace Simd
{
#if defined(SIMD_AVX_ENABLE)
    namespace Avx
    {
        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution1x1_2x6(const float * src0, size_t srcC,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst0, float * dst1)
        {
            __m256 d00, d01, d10, d11, d20, d21, d30, d31, d40, d41, d50, d51, s0, w0, w1;
            d00 = bias[0], d01 = bias[1];
            d10 = bias[0], d11 = bias[1];
            d20 = bias[0], d21 = bias[1];
            d30 = bias[0], d31 = bias[1];
            d40 = bias[0], d41 = bias[1];
            d50 = bias[0], d51 = bias[1];
            const float * src1 = src0 + 1 * srcC;
            const float * src2 = src0 + 2 * srcC;
            const float * src3 = src0 + 3 * srcC;
            const float * src4 = src0 + 4 * srcC;
            const float * src5 = src0 + 5 * srcC;
            for (size_t sc = 0; sc < srcC; ++sc)
            {
                w0 = _mm256_loadu_ps(weight + 0);
                w1 = _mm256_loadu_ps(weight + F);
                s0 = _mm256_set1_ps(src0[sc]);
                d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                s0 = _mm256_set1_ps(src1[sc]);
                d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                d11 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d11);
                s0 = _mm256_set1_ps(src2[sc]);
                d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                d21 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d21);
                s0 = _mm256_set1_ps(src3[sc]);
                d30 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d30);
                d31 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d31);
                s0 = _mm256_set1_ps(src4[sc]);
                d40 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d40);
                d41 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d41);
                s0 = _mm256_set1_ps(src5[sc]);
                d50 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d50);
                d51 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d51);
                weight += DF;
            }
            _mm256_storeu_ps(dst0 + 0 * F, Activate<type>(d00, params, 0));
            _mm256_storeu_ps(dst1 + 0 * F, Activate<type>(d01, params, 1));
            _mm256_storeu_ps(dst0 + 1 * F, Activate<type>(d10, params, 0));
            _mm256_storeu_ps(dst1 + 1 * F, Activate<type>(d11, params, 1));
            _mm256_storeu_ps(dst0 + 2 * F, Activate<type>(d20, params, 0));
            _mm256_storeu_ps(dst1 + 2 * F, Activate<type>(d21, params, 1));
            _mm256_storeu_ps(dst0 + 3 * F, Activate<type>(d30, params, 0));
            _mm256_storeu_ps(dst1 + 3 * F, Activate<type>(d31, params, 1));
            _mm256_storeu_ps(dst0 + 4 * F, Activate<type>(d40, params, 0));
            _mm256_storeu_ps(dst1 + 4 * F, Activate<type>(d41, params, 1));
            _mm256_storeu_ps(dst0 + 5 * F, Activate<type>(d50, params, 0));
            _mm256_storeu_ps(dst1 + 5 * F, Activate<type>(d51, params, 1));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution1x1_2x4(const float * src0, size_t srcC,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst0, float * dst1)
        {
            __m256 d00, d01, d10, d11, d20, d21, d30, d31, s0, w0, w1;
            d00 = bias[0], d01 = bias[1];
            d10 = bias[0], d11 = bias[1];
            d20 = bias[0], d21 = bias[1];
            d30 = bias[0], d31 = bias[1];
            const float * src1 = src0 + 1 * srcC;
            const float * src2 = src0 + 2 * srcC;
            const float * src3 = src0 + 3 * srcC;
            for (size_t sc = 0; sc < srcC; ++sc)
            {
                w0 = _mm256_loadu_ps(weight + 0);
                w1 = _mm256_loadu_ps(weight + F);
                s0 = _mm256_set1_ps(src0[sc]);
                d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                s0 = _mm256_set1_ps(src1[sc]);
                d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                d11 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d11);
                s0 = _mm256_set1_ps(src2[sc]);
                d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                d21 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d21);
                s0 = _mm256_set1_ps(src3[sc]);
                d30 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d30);
                d31 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d31);
                weight += DF;
            }
            _mm256_storeu_ps(dst0 + 0 * F, Activate<type>(d00, params, 0));
            _mm256_storeu_ps(dst1 + 0 * F, Activate<type>(d01, params, 1));
            _mm256_storeu_ps(dst0 + 1 * F, Activate<type>(d10, params, 0));
            _mm256_storeu_ps(dst1 + 1 * F, Activate<type>(d11, params, 1));
            _mm256_storeu_ps(dst0 + 2 * F, Activate<type>(d20, params, 0));
            _mm256_storeu_ps(dst1 + 2 * F, Activate<type>(d21, params, 1));
            _mm256_storeu_ps(dst0 + 3 * F, Activate<type>(d30, params, 0));
            _mm256_storeu_ps(dst1 + 3 * F, Activate<type>(d31, params, 1));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution1x1_2x3(const float * src0, size_t srcC,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst0, float * dst1)
        {
            __m256 d00, d01, d10, d11, d20, d21, s0, w0, w1;
            d00 = bias[0], d01 = bias[1];
            d10 = bias[0], d11 = bias[1];
            d20 = bias[0], d21 = bias[1];
            const float * src1 = src0 + 1 * srcC;
            const float * src2 = src0 + 2 * srcC;
            for (size_t sc = 0; sc < srcC; ++sc)
            {
                w0 = _mm256_loadu_ps(weight + 0);
                w1 = _mm256_loadu_ps(weight + F);
                s0 = _mm256_set1_ps(src0[sc]);
                d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                s0 = _mm256_set1_ps(src1[sc]);
                d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                d11 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d11);
                s0 = _mm256_set1_ps(src2[sc]);
                d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                d21 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d21);
                weight += DF;
            }
            _mm256_storeu_ps(dst0 + 0 * F, Activate<type>(d00, params, 0));
            _mm256_storeu_ps(dst1 + 0 * F, Activate<type>(d01, params, 1));
            _mm256_storeu_ps(dst0 + 1 * F, Activate<type>(d10, params, 0));
            _mm256_storeu_ps(dst1 + 1 * F, Activate<type>(d11, params, 1));
            _mm256_storeu_ps(dst0 + 2 * F, Activate<type>(d20, params, 0));
            _mm256_storeu_ps(dst1 + 2 * F, Activate<type>(d21, params, 1));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution1x1_2x1(const float * src0, size_t srcC,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst0, float * dst1)
        {
            __m256 d00, d01, s0, w0, w1;
            d00 = bias[0];
            d01 = bias[1];
            for (size_t sc = 0; sc < srcC; ++sc)
            {
                w0 = _mm256_loadu_ps(weight + 0);
                w1 = _mm256_loadu_ps(weight + F);
                s0 = _mm256_set1_ps(src0[sc]);
                d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                weight += DF;
            }
            _mm256_storeu_ps(dst0, Activate<type>(d00, params, 0));
            _mm256_storeu_ps(dst1, Activate<type>(d01, params, 1));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution1x1_1x6(const float * src0, size_t srcC,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst0)
        {
            __m256 d00, d10, d20, d30, d40, d50, s0, w0;
            d00 = bias[0];
            d10 = bias[0];
            d20 = bias[0];
            d30 = bias[0];
            d40 = bias[0];
            d50 = bias[0];
            const float * src1 = src0 + 1 * srcC;
            const float * src2 = src0 + 2 * srcC;
            const float * src3 = src0 + 3 * srcC;
            const float * src4 = src0 + 4 * srcC;
            const float * src5 = src0 + 5 * srcC;
            for (size_t sc = 0; sc < srcC; ++sc)
            {
                w0 = _mm256_loadu_ps(weight + 0);
                s0 = _mm256_set1_ps(src0[sc]);
                d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                s0 = _mm256_set1_ps(src1[sc]);
                d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                s0 = _mm256_set1_ps(src2[sc]);
                d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                s0 = _mm256_set1_ps(src3[sc]);
                d30 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d30);
                s0 = _mm256_set1_ps(src4[sc]);
                d40 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d40);
                s0 = _mm256_set1_ps(src5[sc]);
                d50 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d50);
                weight += DF;
            }
            _mm256_storeu_ps(dst0 + 0 * F, Activate<type>(d00, params, 0));
            _mm256_storeu_ps(dst0 + 1 * F, Activate<type>(d10, params, 0));
            _mm256_storeu_ps(dst0 + 2 * F, Activate<type>(d20, params, 0));
            _mm256_storeu_ps(dst0 + 3 * F, Activate<type>(d30, params, 0));
            _mm256_storeu_ps(dst0 + 4 * F, Activate<type>(d40, params, 0));
            _mm256_storeu_ps(dst0 + 5 * F, Activate<type>(d50, params, 0));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution1x1_1x3(const float * src0, size_t srcC,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst0)
        {
            __m256 d00, d10, d20, s0, w0;
            d00 = bias[0];
            d10 = bias[0];
            d20 = bias[0];
            const float * src1 = src0 + 1 * srcC;
            const float * src2 = src0 + 2 * srcC;
            for (size_t sc = 0; sc < srcC; ++sc)
            {
                w0 = _mm256_loadu_ps(weight + 0);
                s0 = _mm256_set1_ps(src0[sc]);
                d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                s0 = _mm256_set1_ps(src1[sc]);
                d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                s0 = _mm256_set1_ps(src2[sc]);
                d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                weight += DF;
            }
            _mm256_storeu_ps(dst0 + 0 * F, Activate<type>(d00, params, 0));
            _mm256_storeu_ps(dst0 + 1 * F, Activate<type>(d10, params, 0));
            _mm256_storeu_ps(dst0 + 2 * F, Activate<type>(d20, params, 0));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution1x1_1x1(const float * src0, size_t srcC,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst0)
        {
            __m256 d00, s0, w0;
            d00 = bias[0];
            for (size_t sc = 0; sc < srcC; ++sc)
            {
                w0 = _mm256_loadu_ps(weight + 0);
                s0 = _mm256_set1_ps(src0[sc]);
                d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                weight += DF;
            }
            _mm256_storeu_ps(dst0, Activate<type>(d00, params, 0));
        }

        template<SimdConvolutionActivationType type> void InputConvolution1x1(const float * src, const SimdConvolutionParameters & p,
            size_t dstC, size_t yBeg, size_t yEnd, const size_t bufH[2], const float * weight, const float * bias, const float * params, float * dst)
        {
            size_t srcH = p.srcH, srcW = p.srcW, srcC = p.srcC, dstW = p.dstW;
            size_t dstM = (bufH[0] - 1), dstS = bufH[0] * dstW *F;
            size_t dstCDF = AlignLo(dstC, DF), dstW3 = AlignLoAny(dstW, 3), dstW6 = AlignLoAny(dstW, 6);
            __m256 _params[2], _bias[2];
            _params[0] = _mm256_set1_ps(params[0]);
            if (type == ::SimdConvolutionActivationRestrictRange)
                _params[1] = _mm256_set1_ps(params[1]);

            size_t dc = 0;
            for (; dc < dstC; dc += DF)
            {
                _bias[0] = bias ? _mm256_loadu_ps(bias + dc + 0) : _mm256_setzero_ps();
                _bias[1] = bias ? _mm256_loadu_ps(bias + dc + F) : _mm256_setzero_ps();
                if (type == ::SimdConvolutionActivationPrelu)
                {
                    _params[0] = _mm256_loadu_ps(params + dc + 0);
                    _params[1] = _mm256_loadu_ps(params + dc + F);
                }
                const float * pS = src + yBeg * srcW*srcC;
                const float * pW = weight + dc * srcC;
                float * pD = dst + (dc / F)*dstS;
                for (size_t dy = yBeg; dy < yEnd; ++dy)
                {
                    float * dst0 = pD + (dy&dstM)*dstW*F;
                    size_t dx = 0;
                    if (dstC - dc > F)
                    {
                        for (; dx < dstW6; dx += 6, pS += 6 * srcC, dst0 += 6 * F)
                            InputConvolution1x1_2x6<type>(pS, srcC, pW, _bias, _params, dst0, dst0 + dstS);
                        if (dstW - dstW6 == 4)
                            InputConvolution1x1_2x4<type>(pS, srcC, pW, _bias, _params, dst0, dst0 + dstS), pS += 4 * srcC;
                        else
                        {
                            for (; dx < dstW3; dx += 3, pS += 3 * srcC, dst0 += 3 * F)
                                InputConvolution1x1_2x3<type>(pS, srcC, pW, _bias, _params, dst0, dst0 + dstS);
                            for (; dx < dstW; dx += 1, pS += srcC, dst0 += F)
                                InputConvolution1x1_2x1<type>(pS, srcC, pW, _bias, _params, dst0, dst0 + dstS);
                        }
                    }
                    else
                    {
                        for (; dx < dstW6; dx += 6, pS += 6 * srcC, dst0 += 6 * F)
                            InputConvolution1x1_1x6<type>(pS, srcC, pW, _bias, _params, dst0);
                        for (; dx < dstW3; dx += 3, pS += 3 * srcC, dst0 += 3 * F)
                            InputConvolution1x1_1x3<type>(pS, srcC, pW, _bias, _params, dst0);
                        for (; dx < dstW; dx += 1, pS += srcC, dst0 += F)
                            InputConvolution1x1_1x1<type>(pS, srcC, pW, _bias, _params, dst0);
                    }
                }
            }
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution_2x1(const float * src0, const SimdConvolutionParameters & p,
            size_t kH, size_t kW, const float * weight, const __m256 * bias, const __m256 * params, float * dst0, float * dst1)
        {
            __m256 d00, d01, s0, w0, w1;
            d00 = bias[0];
            d01 = bias[1];
            size_t size = kW * p.srcC, tail = DF * (p.kernelX - kW)*p.srcC, stride = p.srcW * p.srcC;
            for (size_t ky = 0; ky < kH; ++ky)
            {
                for (size_t i = 0; i < size; ++i)
                {
                    w0 = _mm256_loadu_ps(weight + 0);
                    w1 = _mm256_loadu_ps(weight + F);
                    s0 = _mm256_set1_ps(src0[i]);
                    d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                    d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                    weight += DF;
                }
                weight += tail;
                src0 += stride;
            }
            _mm256_storeu_ps(dst0, Activate<type>(d00, params, 0));
            _mm256_storeu_ps(dst1, Activate<type>(d01, params, 1));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution_1x1(const float * src0, const SimdConvolutionParameters & p,
            size_t kH, size_t kW, const float * weight, const __m256 * bias, const __m256 * params, float * dst0)
        {
            __m256 d00, s0, w0;
            d00 = bias[0];
            size_t size = kW * p.srcC, tail = DF * (p.kernelX - kW)*p.srcC, stride = p.srcW * p.srcC;
            for (size_t ky = 0; ky < kH; ++ky)
            {
                for (size_t i = 0; i < size; ++i)
                {
                    w0 = _mm256_loadu_ps(weight + 0);
                    s0 = _mm256_set1_ps(src0[i]);
                    d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                    weight += DF;
                }
                weight += tail;
                src0 += stride;
            }
            _mm256_storeu_ps(dst0, Activate<type>(d00, params, 0));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution_2x6(const float * src0, const SimdConvolutionParameters & p,
            size_t kH, size_t kW, const float * weight, const __m256 * bias, const __m256 * params, float * dst0, float * dst1)
        {
            __m256 d00, d01, d10, d11, d20, d21, d30, d31, d40, d41, d50, d51, s0, w0, w1;
            d00 = bias[0], d01 = bias[1];
            d10 = bias[0], d11 = bias[1];
            d20 = bias[0], d21 = bias[1];
            d30 = bias[0], d31 = bias[1];
            d40 = bias[0], d41 = bias[1];
            d50 = bias[0], d51 = bias[1];
            size_t size = kW * p.srcC, tail = DF * (p.kernelX - kW)*p.srcC, stride = p.srcW * p.srcC, step = p.srcC*p.strideX;
            const float * src1 = src0 + 1 * step;
            const float * src2 = src0 + 2 * step;
            const float * src3 = src0 + 3 * step;
            const float * src4 = src0 + 4 * step;
            const float * src5 = src0 + 5 * step;
            for (size_t ky = 0; ky < kH; ++ky)
            {
                size_t offset = ky * stride;
                for (size_t end = offset + size; offset < end; ++offset)
                {
                    w0 = _mm256_loadu_ps(weight + 0);
                    w1 = _mm256_loadu_ps(weight + F);
                    s0 = _mm256_set1_ps(src0[offset]);
                    d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                    d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                    s0 = _mm256_set1_ps(src1[offset]);
                    d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                    d11 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d11);
                    s0 = _mm256_set1_ps(src2[offset]);
                    d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                    d21 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d21);
                    s0 = _mm256_set1_ps(src3[offset]);
                    d30 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d30);
                    d31 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d31);
                    s0 = _mm256_set1_ps(src4[offset]);
                    d40 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d40);
                    d41 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d41);
                    s0 = _mm256_set1_ps(src5[offset]);
                    d50 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d50);
                    d51 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d51);
                    weight += DF;
                }
                weight += tail;
            }
            _mm256_storeu_ps(dst0 + 0 * F, Activate<type>(d00, params, 0));
            _mm256_storeu_ps(dst1 + 0 * F, Activate<type>(d01, params, 1));
            _mm256_storeu_ps(dst0 + 1 * F, Activate<type>(d10, params, 0));
            _mm256_storeu_ps(dst1 + 1 * F, Activate<type>(d11, params, 1));
            _mm256_storeu_ps(dst0 + 2 * F, Activate<type>(d20, params, 0));
            _mm256_storeu_ps(dst1 + 2 * F, Activate<type>(d21, params, 1));
            _mm256_storeu_ps(dst0 + 3 * F, Activate<type>(d30, params, 0));
            _mm256_storeu_ps(dst1 + 3 * F, Activate<type>(d31, params, 1));
            _mm256_storeu_ps(dst0 + 4 * F, Activate<type>(d40, params, 0));
            _mm256_storeu_ps(dst1 + 4 * F, Activate<type>(d41, params, 1));
            _mm256_storeu_ps(dst0 + 5 * F, Activate<type>(d50, params, 0));
            _mm256_storeu_ps(dst1 + 5 * F, Activate<type>(d51, params, 1));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void InputConvolution_1x6(const float * src0, const SimdConvolutionParameters & p,
            size_t kH, size_t kW, const float * weight, const __m256 * bias, const __m256 * params, float * dst0)
        {
            __m256 d00, d10, d20, d30, d40, d50, s0, w0;
            d00 = bias[0];
            d10 = bias[0];
            d20 = bias[0];
            d30 = bias[0];
            d40 = bias[0];
            d50 = bias[0];
            size_t size = kW * p.srcC, tail = DF * (p.kernelX - kW)*p.srcC, stride = p.srcW * p.srcC, step = p.srcC*p.strideX;
            const float * src1 = src0 + 1 * step;
            const float * src2 = src0 + 2 * step;
            const float * src3 = src0 + 3 * step;
            const float * src4 = src0 + 4 * step;
            const float * src5 = src0 + 5 * step;
            for (size_t ky = 0; ky < kH; ++ky)
            {
                size_t offset = ky * stride;
                for (size_t end = offset + size; offset < end; ++offset)
                {
                    w0 = _mm256_loadu_ps(weight + 0);
                    s0 = _mm256_set1_ps(src0[offset]);
                    d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                    s0 = _mm256_set1_ps(src1[offset]);
                    d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                    s0 = _mm256_set1_ps(src2[offset]);
                    d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                    s0 = _mm256_set1_ps(src3[offset]);
                    d30 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d30);
                    s0 = _mm256_set1_ps(src4[offset]);
                    d40 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d40);
                    s0 = _mm256_set1_ps(src5[offset]);
                    d50 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d50);
                    weight += DF;
                }
                weight += tail;
            }
            _mm256_storeu_ps(dst0 + 0 * F, Activate<type>(d00, params, 0));
            _mm256_storeu_ps(dst0 + 1 * F, Activate<type>(d10, params, 0));
            _mm256_storeu_ps(dst0 + 2 * F, Activate<type>(d20, params, 0));
            _mm256_storeu_ps(dst0 + 3 * F, Activate<type>(d30, params, 0));
            _mm256_storeu_ps(dst0 + 4 * F, Activate<type>(d40, params, 0));
            _mm256_storeu_ps(dst0 + 5 * F, Activate<type>(d50, params, 0));
        }

        template<SimdConvolutionActivationType type> void InputConvolution(const float * src, const SimdConvolutionParameters & p,
            size_t dstC, size_t yBeg, size_t yEnd, const size_t bufH[2], const float * weight, const float * bias, const float * params, float * dst)
        {
            size_t srcH = p.srcH, srcW = p.srcW, srcC = p.srcC, dstW = p.dstW;
            size_t kernelY = p.kernelY, kernelX = p.kernelX, strideY = p.strideY, strideX = p.strideX;
            size_t dstM = (bufH[0] - 1), dstS = bufH[0] * dstW * F;
            size_t dstCDF = AlignLo(dstC, DF);
            if (dstC - F > dstCDF)
                dstCDF += DF;

            size_t noseH = p.padY, noseW = p.padX;
            size_t bodyH = p.srcH - p.kernelY + 1 + noseH, bodyW = p.srcW - p.kernelX + 1 + noseW;
            size_t bodyW6 = AlignLoAny(bodyW - noseW, 6 * p.strideX) + noseW;
            size_t tailH = bodyH + p.padH, tailW = bodyW + p.padW;
            size_t wS = p.srcC*p.dstC;
            size_t kY = p.kernelY - noseH, kX = p.kernelX - noseW, kH = bodyH + p.kernelY - 1, kW = bodyW + p.kernelX - 1;

            __m256 _params[2], _bias[2];
            _params[0] = _mm256_set1_ps(params[0]);
            if (type == ::SimdConvolutionActivationRestrictRange)
                _params[1] = _mm256_set1_ps(params[1]);

            size_t dc = 0;
            for (; dc < dstCDF; dc += DF)
            {
                _bias[0] = bias ? _mm256_loadu_ps(bias + dc + 0) : _mm256_setzero_ps();
                _bias[1] = bias ? _mm256_loadu_ps(bias + dc + F) : _mm256_setzero_ps();
                if (type == ::SimdConvolutionActivationPrelu)
                {
                    _params[0] = _mm256_loadu_ps(params + dc + 0);
                    _params[1] = _mm256_loadu_ps(params + dc + F);
                }
                size_t dy = yBeg, sy = dy * strideY;
                for (; sy < noseH && dy < yEnd; sy += strideY, dy++)
                {
                    float * dst0 = dst + (dy&dstM)*dstW*F + (dc / F)*dstS, *dst1 = dst0 + dstS;
                    size_t sx = 0;
                    const float * s = src;
                    const float * w = weight + (noseH - sy) * kernelX * DF * srcC;
                    for (; sx < noseW; sx += strideX, dst0 += F, dst1 += F)
                        InputConvolution_2x1<type>(s, p, kY + sy, kX + sx, w + (noseW - sx)*srcC*DF, _bias, _params, dst0, dst1);
                    for (; sx < bodyW6; sx += 6 * strideX, dst0 += 6 * F, dst1 += 6 * F)
                        InputConvolution_2x6<type>(s + (sx - noseW) * srcC, p, kY + sy, kernelX, w, _bias, _params, dst0, dst1);
                    for (; sx < bodyW; sx += strideX, dst0 += F, dst1 += F)
                        InputConvolution_2x1<type>(s + (sx - noseW) * srcC, p, kY + sy, kernelX, w, _bias, _params, dst0, dst1);
                    for (; sx < tailW; sx += strideX, dst0 += F, dst1 += F)
                        InputConvolution_2x1<type>(s + (sx - noseW) * srcC, p, kY + sy, kW - sx, w, _bias, _params, dst0, dst1);
                }
                for (; sy < bodyH && dy < yEnd; sy += strideY, dy++)
                {
                    float * dst0 = dst + (dy&dstM)*dstW*F + (dc / F)*dstS, *dst1 = dst0 + dstS;
                    size_t sx = 0;
                    const float * s = src + (sy - noseH)*srcW*srcC;
                    const float * w = weight;
                    for (; sx < noseW; sx += strideX, dst0 += F, dst1 += F)
                        InputConvolution_2x1<type>(s, p, kernelY, kX + sx, w + (noseW - sx)*srcC*DF, _bias, _params, dst0, dst1);
                    for (; sx < bodyW6; sx += 6 * strideX, dst0 += 6 * F, dst1 += 6 * F)
                        InputConvolution_2x6<type>(s + (sx - noseW) * srcC, p, kernelY, kernelX, w, _bias, _params, dst0, dst1);
                    for (; sx < bodyW; sx += strideX, dst0 += F, dst1 += F)
                        InputConvolution_2x1<type>(s + (sx - noseW) * srcC, p, kernelY, kernelX, w, _bias, _params, dst0, dst1);
                    for (; sx < tailW; sx += strideX, dst0 += F, dst1 += F)
                        InputConvolution_2x1<type>(s + (sx - noseW) * srcC, p, kernelY, kW - sx, w, _bias, _params, dst0, dst1);
                }
                for (; sy < tailH && dy < yEnd; sy += strideY, dy++)
                {
                    float * dst0 = dst + (dy&dstM)*dstW*F + (dc / F)*dstS, *dst1 = dst0 + dstS;
                    size_t sx = 0;
                    const float * s = src + (sy - noseH)*srcW*srcC;
                    const float * w = weight;
                    for (; sx < noseW; sx += strideX, dst0 += F, dst1 += F)
                        InputConvolution_2x1<type>(s, p, kH - sy, kX + sx, w + (noseW - sx)*srcC*DF, _bias, _params, dst0, dst1);
                    for (; sx < bodyW6; sx += 6 * strideX, dst0 += 6 * F, dst1 += 6 * F)
                        InputConvolution_2x6<type>(s + (sx - noseW) * srcC, p, kH - sy, kernelX, w, _bias, _params, dst0, dst1);
                    for (; sx < bodyW; sx += strideX, dst0 += F, dst1 += F)
                        InputConvolution_2x1<type>(s + (sx - noseW) * srcC, p, kH - sy, kernelX, w, _bias, _params, dst0, dst1);
                    for (; sx < tailW; sx += strideX, dst0 += F, dst1 += F)
                        InputConvolution_2x1<type>(s + (sx - noseW) * srcC, p, kH - sy, kW - sx, w, _bias, _params, dst0, dst1);
                }
                weight += kernelY * kernelX*srcC*DF;
            }
            if (dc < dstC)
            {
                _bias[0] = bias ? _mm256_loadu_ps(bias + dc) : _mm256_setzero_ps();
                if (type == ::SimdConvolutionActivationPrelu)
                    _params[0] = _mm256_loadu_ps(params + dc);
                size_t dy = yBeg, sy = dy * strideY;
                for (; sy < noseH && dy < yEnd; sy += strideY, dy++)
                {
                    float * dst0 = dst + (dy&dstM)*dstW*F + (dc / F)*dstS;
                    size_t sx = 0;
                    const float * s = src;
                    const float * w = weight + (noseH - sy) * kernelX * DF * srcC;
                    for (; sx < noseW; sx += strideX, dst0 += F)
                        InputConvolution_1x1<type>(s, p, kY + sy, kX + sx, w + (noseW - sx)*srcC*DF, _bias, _params, dst0);
                    for (; sx < bodyW6; sx += 6 * strideX, dst0 += 6 * F)
                        InputConvolution_1x6<type>(s + (sx - noseW) * srcC, p, kY + sy, kernelX, w, _bias, _params, dst0);
                    for (; sx < bodyW; sx += strideX, dst0 += F)
                        InputConvolution_1x1<type>(s + (sx - noseW) * srcC, p, kY + sy, kernelX, w, _bias, _params, dst0);
                    for (; sx < tailW; sx += strideX, dst0 += F)
                        InputConvolution_1x1<type>(s + (sx - noseW) * srcC, p, kY + sy, kW - sx, w, _bias, _params, dst0);
                }
                for (; sy < bodyH && dy < yEnd; sy += strideY, dy++)
                {
                    float * dst0 = dst + (dy&dstM)*dstW*F + (dc / F)*dstS;
                    size_t sx = 0;
                    const float * s = src + (sy - noseH)*srcW*srcC;
                    const float * w = weight;
                    for (; sx < noseW; sx += strideX, dst0 += F)
                        InputConvolution_1x1<type>(s, p, kernelY, kX + sx, w + (noseW - sx)*srcC*DF, _bias, _params, dst0);
                    for (; sx < bodyW6; sx += 6 * strideX, dst0 += 6 * F)
                        InputConvolution_1x6<type>(s + (sx - noseW) * srcC, p, kernelY, kernelX, w, _bias, _params, dst0);
                    for (; sx < bodyW; sx += strideX, dst0 += F)
                        InputConvolution_1x1<type>(s + (sx - noseW) * srcC, p, kernelY, kernelX, w, _bias, _params, dst0);
                    for (; sx < tailW; sx += strideX, dst0 += F)
                        InputConvolution_1x1<type>(s + (sx - noseW) * srcC, p, kernelY, kW - sx, w, _bias, _params, dst0);
                }
                for (; sy < tailH && dy < yEnd; sy += strideY, dy++)
                {
                    float * dst0 = dst + (dy&dstM)*dstW*F + (dc / F)*dstS;
                    size_t sx = 0;
                    const float * s = src + (sy - noseH)*srcW*srcC;
                    const float * w = weight;
                    for (; sx < noseW; sx += strideX, dst0 += F)
                        InputConvolution_1x1<type>(s, p, kH - sy, kX + sx, w + (noseW - sx)*srcC*DF, _bias, _params, dst0);
                    for (; sx < bodyW6; sx += 6 * strideX, dst0 += 6 * F)
                        InputConvolution_1x6<type>(s + (sx - noseW) * srcC, p, kH - sy, kernelX, w, _bias, _params, dst0);
                    for (; sx < bodyW; sx += strideX, dst0 += F)
                        InputConvolution_1x1<type>(s + (sx - noseW) * srcC, p, kH - sy, kernelX, w, _bias, _params, dst0);
                    for (; sx < tailW; sx += strideX, dst0 += F)
                        InputConvolution_1x1<type>(s + (sx - noseW) * srcC, p, kH - sy, kW - sx, w, _bias, _params, dst0);
                }
            }
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void ConvolutionDepthwise3x3Edge2x2(
            const float * src0, const float * src1, const __m256 * weight, const __m256 & bias, const __m256 * params, float * dst)
        {
            __m256 sum0 = bias, sum1 = _mm256_setzero_ps();
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 0 * F), weight[0]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 1 * F), weight[1]), sum1);
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 0 * F), weight[3]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 1 * F), weight[4]), sum1);
            _mm256_storeu_ps(dst, Activate<type>(_mm256_add_ps(sum0, sum1), params, 0));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void ConvolutionDepthwise3x3Edge2x3(
            const float * src0, const float * src1, const __m256 * weight, const __m256 & bias, const __m256 * params, float * dst)
        {
            __m256 sum0 = bias, sum1 = _mm256_setzero_ps(), sum2 = _mm256_setzero_ps();
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 0 * F), weight[0]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 1 * F), weight[1]), sum1);
            sum2 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 2 * F), weight[2]), sum2);
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 0 * F), weight[3]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 1 * F), weight[4]), sum1);
            sum2 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 2 * F), weight[5]), sum2);
            _mm256_storeu_ps(dst, Activate<type>(_mm256_add_ps(_mm256_add_ps(sum0, sum1), sum2), params, 0));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void ConvolutionDepthwise3x3Edge3x2(
            const float * src0, const float * src1, const float * src2, const __m256 * weight, const __m256 & bias, const __m256 * params, float * dst)
        {
            __m256 sum0 = bias, sum1 = _mm256_setzero_ps();
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 0 * F), weight[0]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 1 * F), weight[1]), sum1);
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 0 * F), weight[3]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 1 * F), weight[4]), sum1);
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src2 + 0 * F), weight[6]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src2 + 1 * F), weight[7]), sum1);
            _mm256_storeu_ps(dst, Activate<type>(_mm256_add_ps(sum0, sum1), params, 0));
        }

        template<SimdConvolutionActivationType type> SIMD_INLINE void ConvolutionDepthwise3x3Main1x1(
            const float * src0, const float * src1, const float * src2, const __m256 * weight, const __m256 & bias, const __m256 * params, float * dst)
        {
            __m256 sum0 = bias, sum1 = _mm256_setzero_ps(), sum2 = _mm256_setzero_ps();
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 0 * F), weight[0]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 1 * F), weight[1]), sum1);
            sum2 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src0 + 2 * F), weight[2]), sum2);
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 0 * F), weight[3]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 1 * F), weight[4]), sum1);
            sum2 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src1 + 2 * F), weight[5]), sum2);
            sum0 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src2 + 0 * F), weight[6]), sum0);
            sum1 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src2 + 1 * F), weight[7]), sum1);
            sum2 = _mm256_add_ps(_mm256_mul_ps(_mm256_loadu_ps(src2 + 2 * F), weight[8]), sum2);
            _mm256_storeu_ps(dst, Activate<type>(_mm256_add_ps(_mm256_add_ps(sum0, sum1), sum2), params, 0));
        }

        template<SimdConvolutionActivationType type> void DepthwiseConvolution3x3(const float * src, const SimdConvolutionParameters & p,
            size_t srcC, size_t yBeg, size_t yEnd, const size_t bufH[2], const float * weight, const float * bias, const float * params, float * dst)
        {
            size_t strideY = p.strideY, padY = p.padY, padX = p.padX, padH = p.padH, padW = p.padW;
            size_t srcW = p.srcW * F, dstW = p.dstW * F, weightS = p.kernelY * p.kernelX * F;
            size_t srcM = (bufH[0] - 1), dstM = (bufH[1] - 1), srcS = bufH[0] * srcW, dstS = bufH[1] * dstW;
            size_t xStep = F * p.strideX, xStep0 = (p.strideX - p.padX)*F;
            size_t xMainEnd = p.dstW - p.padW, yMainEnd = yEnd == p.dstH && p.padH ? yEnd - 1 : yEnd;

            __m256 _params[2];
            _params[0] = _mm256_set1_ps(params[0]);
            if (type == ::SimdConvolutionActivationRestrictRange)
                _params[1] = _mm256_set1_ps(params[1]);
            for (size_t c = 0; c < srcC; c += F)
            {
                __m256 _weight[9];
                for (size_t i = 0; i < 9; ++i)
                    _weight[i] = _mm256_loadu_ps(weight + i * F);
                __m256 _bias = bias ? _mm256_loadu_ps(bias + c) : _mm256_setzero_ps();
                if (type == ::SimdConvolutionActivationPrelu)
                    _params[0] = _mm256_loadu_ps(params + c);

                size_t dy = yBeg;
                if (yBeg == 0 && padY)
                {
                    size_t sy = 0, dx = 0;
                    const float * src0 = src + ((sy + 0)&srcM)*srcW;
                    const float * src1 = src + ((sy + 1)&srcM)*srcW;
                    float * pDst = dst + (dy&dstM)*dstW;
                    if (padX)
                        ConvolutionDepthwise3x3Edge2x2<type>(src0, src1, _weight + 4, _bias, _params, pDst), pDst += F, dx++, src0 += xStep0, src1 += xStep0;
                    for (; dx < xMainEnd; dx++, pDst += F, src0 += xStep, src1 += xStep)
                        ConvolutionDepthwise3x3Edge2x3<type>(src0, src1, _weight + 3, _bias, _params, pDst);
                    if (padW)
                        ConvolutionDepthwise3x3Edge2x2<type>(src0, src1, _weight + 3, _bias, _params, pDst);
                    dy++;
                }
                for (; dy < yMainEnd; ++dy)
                {
                    size_t sy = dy * strideY - padY, dx = 0;
                    const float * src0 = src + ((sy + 0)&srcM)*srcW;
                    const float * src1 = src + ((sy + 1)&srcM)*srcW;
                    const float * src2 = src + ((sy + 2)&srcM)*srcW;
                    float * pDst = dst + (dy&dstM)*dstW;
                    if (padX)
                        ConvolutionDepthwise3x3Edge3x2<type>(src0, src1, src2, _weight + 1, _bias, _params, pDst), pDst += F, dx++, src0 += xStep0, src1 += xStep0, src2 += xStep0;
                    for (; dx < xMainEnd; dx++, pDst += F, src0 += xStep, src1 += xStep, src2 += xStep)
                        ConvolutionDepthwise3x3Main1x1<type>(src0, src1, src2, _weight + 0, _bias, _params, pDst);
                    if (padW)
                        ConvolutionDepthwise3x3Edge3x2<type>(src0, src1, src2, _weight + 0, _bias, _params, pDst);
                }
                if (dy < yEnd)
                {
                    size_t sy = dy * strideY - padY, dx = 0;
                    const float * src0 = src + ((sy + 0)&srcM)*srcW;
                    const float * src1 = src + ((sy + 1)&srcM)*srcW;
                    float * pDst = dst + (dy&dstM)*dstW;
                    if (padX)
                        ConvolutionDepthwise3x3Edge2x2<type>(src0, src1, _weight + 1, _bias, _params, pDst), pDst += F, dx++, src0 += xStep0, src1 += xStep0;
                    for (; dx < xMainEnd; dx++, pDst += F, src0 += xStep, src1 += xStep)
                        ConvolutionDepthwise3x3Edge2x3<type>(src0, src1, _weight + 0, _bias, _params, pDst);
                    if (padW)
                        ConvolutionDepthwise3x3Edge2x2<type>(src0, src1, _weight + 0, _bias, _params, pDst);
                }
                src += srcS;
                dst += dstS;
                weight += weightS;
            }
        }

        template<TermType term, SimdConvolutionActivationType type> void OutputConvolution_2x6(const float * src, size_t srcC, size_t srcS,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst, size_t dstC, size_t tail)
        {
            __m256 d00, d01, d10, d11, d20, d21, d30, d31, d40, d41, d50, d51, s0, w0, w1;
            if (tail > F)
            {
                d00 = _mm256_setzero_ps(), d01 = _mm256_setzero_ps();
                d10 = _mm256_setzero_ps(), d11 = _mm256_setzero_ps();
                d20 = _mm256_setzero_ps(), d21 = _mm256_setzero_ps();
                d30 = _mm256_setzero_ps(), d31 = _mm256_setzero_ps();
                d40 = _mm256_setzero_ps(), d41 = _mm256_setzero_ps();
                d50 = _mm256_setzero_ps(), d51 = _mm256_setzero_ps();
                for (size_t c = 0; c < srcC; c += F)
                {
                    size_t n = Simd::Min(F, srcC - c);
                    for (size_t i = 0; i < n; ++i, weight += DF)
                    {
                        w0 = _mm256_loadu_ps(weight + 0);
                        w1 = _mm256_loadu_ps(weight + F);
                        s0 = _mm256_set1_ps(src[i + 0 * F]);
                        d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                        d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                        s0 = _mm256_set1_ps(src[i + 1 * F]);
                        d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                        d11 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d11);
                        s0 = _mm256_set1_ps(src[i + 2 * F]);
                        d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                        d21 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d21);
                        s0 = _mm256_set1_ps(src[i + 3 * F]);
                        d30 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d30);
                        d31 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d31);
                        s0 = _mm256_set1_ps(src[i + 4 * F]);
                        d40 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d40);
                        d41 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d41);
                        s0 = _mm256_set1_ps(src[i + 5 * F]);
                        d50 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d50);
                        d51 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d51);
                    }
                    src += srcS;
                }
                if (tail == DF)
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d01, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d11, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d21, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d30, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d31, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d40, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d41, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d50, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d51, bias, params);
                }
                else
                {
                    tail -= F;
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d01, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d11, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d21, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d30, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d31, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d40, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d41, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d50, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d51, bias, params, tail);
                }
            }
            else
            {
                d00 = _mm256_setzero_ps();
                d10 = _mm256_setzero_ps();
                d20 = _mm256_setzero_ps();
                d30 = _mm256_setzero_ps();
                d40 = _mm256_setzero_ps();
                d50 = _mm256_setzero_ps();
                for (size_t c = 0; c < srcC; c += F)
                {
                    size_t n = Simd::Min(F, srcC - c);
                    for (size_t i = 0; i < n; ++i, weight += DF)
                    {
                        w0 = _mm256_loadu_ps(weight + 0);
                        s0 = _mm256_set1_ps(src[i + 0 * F]);
                        d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                        s0 = _mm256_set1_ps(src[i + 1 * F]);
                        d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                        s0 = _mm256_set1_ps(src[i + 2 * F]);
                        d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                        s0 = _mm256_set1_ps(src[i + 3 * F]);
                        d30 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d30);
                        s0 = _mm256_set1_ps(src[i + 4 * F]);
                        d40 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d40);
                        s0 = _mm256_set1_ps(src[i + 5 * F]);
                        d50 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d50);
                    }
                    src += srcS;
                }
                if (tail == F)
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d30, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d40, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d50, bias, params);
                }
                else
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d30, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d40, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d50, bias, params, tail);
                }
            }
        }

        template<TermType term, SimdConvolutionActivationType type> void OutputConvolution_2x4(const float * src, size_t srcC, size_t srcS,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst, size_t dstC, size_t tail)
        {
            __m256 d00, d01, d10, d11, d20, d21, d30, d31, s0, w0, w1;
            if (tail > F)
            {
                d00 = _mm256_setzero_ps(), d01 = _mm256_setzero_ps();
                d10 = _mm256_setzero_ps(), d11 = _mm256_setzero_ps();
                d20 = _mm256_setzero_ps(), d21 = _mm256_setzero_ps();
                d30 = _mm256_setzero_ps(), d31 = _mm256_setzero_ps();
                for (size_t c = 0; c < srcC; c += F)
                {
                    size_t n = Simd::Min(F, srcC - c);
                    for (size_t i = 0; i < n; ++i, weight += DF)
                    {
                        w0 = _mm256_loadu_ps(weight + 0);
                        w1 = _mm256_loadu_ps(weight + F);
                        s0 = _mm256_set1_ps(src[i + 0 * F]);
                        d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                        d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                        s0 = _mm256_set1_ps(src[i + 1 * F]);
                        d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                        d11 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d11);
                        s0 = _mm256_set1_ps(src[i + 2 * F]);
                        d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                        d21 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d21);
                        s0 = _mm256_set1_ps(src[i + 3 * F]);
                        d30 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d30);
                        d31 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d31);
                    }
                    src += srcS;
                }
                if (tail == DF)
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d01, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d11, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d21, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d30, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d31, bias, params);
                }
                else
                {
                    tail -= F;
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d01, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d11, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d21, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d30, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d31, bias, params, tail);
                }
            }
            else
            {
                d00 = _mm256_setzero_ps();
                d10 = _mm256_setzero_ps();
                d20 = _mm256_setzero_ps();
                d30 = _mm256_setzero_ps();
                for (size_t c = 0; c < srcC; c += F)
                {
                    size_t n = Simd::Min(F, srcC - c);
                    for (size_t i = 0; i < n; ++i, weight += DF)
                    {
                        w0 = _mm256_loadu_ps(weight + 0);
                        s0 = _mm256_set1_ps(src[i + 0 * F]);
                        d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                        s0 = _mm256_set1_ps(src[i + 1 * F]);
                        d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                        s0 = _mm256_set1_ps(src[i + 2 * F]);
                        d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                        s0 = _mm256_set1_ps(src[i + 3 * F]);
                        d30 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d30);
                    }
                    src += srcS;
                }
                if (tail == F)
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d30, bias, params);
                }
                else
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d30, bias, params, tail);
                }
            }
        }

        template<TermType term, SimdConvolutionActivationType type> void OutputConvolution_2x3(const float * src, size_t srcC, size_t srcS,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst, size_t dstC, size_t tail)
        {
            __m256 d00, d01, d10, d11, d20, d21, s0, w0, w1;
            if (tail > F)
            {
                d00 = _mm256_setzero_ps(), d01 = _mm256_setzero_ps();
                d10 = _mm256_setzero_ps(), d11 = _mm256_setzero_ps();
                d20 = _mm256_setzero_ps(), d21 = _mm256_setzero_ps();
                for (size_t c = 0; c < srcC; c += F)
                {
                    size_t n = Simd::Min(F, srcC - c);
                    for (size_t i = 0; i < n; ++i, weight += DF)
                    {
                        w0 = _mm256_loadu_ps(weight + 0);
                        w1 = _mm256_loadu_ps(weight + F);
                        s0 = _mm256_set1_ps(src[i + 0 * F]);
                        d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                        d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                        s0 = _mm256_set1_ps(src[i + 1 * F]);
                        d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                        d11 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d11);
                        s0 = _mm256_set1_ps(src[i + 2 * F]);
                        d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                        d21 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d21);
                    }
                    src += srcS;
                }
                if (tail == DF)
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d01, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d11, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d21, bias, params);
                }
                else
                {
                    tail -= F;
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d01, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d11, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d21, bias, params, tail);
                }
            }
            else
            {
                d00 = _mm256_setzero_ps();
                d10 = _mm256_setzero_ps();
                d20 = _mm256_setzero_ps();
                for (size_t c = 0; c < srcC; c += F)
                {
                    size_t n = Simd::Min(F, srcC - c);
                    for (size_t i = 0; i < n; ++i, weight += DF)
                    {
                        w0 = _mm256_loadu_ps(weight + 0);
                        s0 = _mm256_set1_ps(src[i + 0 * F]);
                        d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                        s0 = _mm256_set1_ps(src[i + 1 * F]);
                        d10 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d10);
                        s0 = _mm256_set1_ps(src[i + 2 * F]);
                        d20 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d20);
                    }
                    src += srcS;
                }
                if (tail == F)
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params);
                }
                else
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d10, bias, params, tail);
                    dst += dstC;
                    Term<term>::template Save<type, 0>(dst + 0, d20, bias, params, tail);
                }
            }
        }

        template<TermType term, SimdConvolutionActivationType type> void OutputConvolution_2x1(const float * src, size_t srcC, size_t srcS,
            const float * weight, const __m256 * bias, const __m256 * params, float * dst, size_t dstC, size_t tail)
        {
            __m256 d00, d01, s0, w0, w1;
            if (tail > F)
            {
                d00 = _mm256_setzero_ps(), d01 = _mm256_setzero_ps();
                for (size_t c = 0; c < srcC; c += F)
                {
                    size_t n = Simd::Min(F, srcC - c);
                    for (size_t i = 0; i < n; ++i, weight += DF)
                    {
                        w0 = _mm256_loadu_ps(weight + 0);
                        w1 = _mm256_loadu_ps(weight + F);
                        s0 = _mm256_set1_ps(src[i + 0 * F]);
                        d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                        d01 = _mm256_add_ps(_mm256_mul_ps(s0, w1), d01);
                    }
                    src += srcS;
                }
                if (tail == DF)
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d01, bias, params);
                }
                else
                {
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                    Term<term>::template Save<type, 1>(dst + F, d01, bias, params, tail - F);
                }
            }
            else
            {
                d00 = _mm256_setzero_ps();
                for (size_t c = 0; c < srcC; c += F)
                {
                    size_t n = Simd::Min(F, srcC - c);
                    for (size_t i = 0; i < n; ++i, weight += DF)
                    {
                        w0 = _mm256_loadu_ps(weight + 0);
                        s0 = _mm256_set1_ps(src[i + 0 * F]);
                        d00 = _mm256_add_ps(_mm256_mul_ps(s0, w0), d00);
                    }
                    src += srcS;
                }
                if (tail == F)
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params);
                else
                    Term<term>::template Save<type, 0>(dst + 0, d00, bias, params, tail);
            }
        }

        template<TermType term, SimdConvolutionActivationType type> void OutputConvolution(const float * src, const SimdConvolutionParameters & p,
            size_t srcC, size_t yBeg, size_t yEnd, const size_t bufH[2], const float * weight, const float * bias, const float * params, float * dst)
        {
            assert(p.group == 1 && p.kernelY == 1 && p.strideY == 1);
            size_t srcH = p.srcH, srcW = p.srcW, dstW = p.dstW, dstC = p.dstC;
            size_t srcM = (bufH[1] - 1), srcS = bufH[1] * srcW*F;
            size_t dstW3 = AlignLoAny(dstW, 3), dstW6 = AlignLoAny(dstW, 6);
            __m256 _params[2], _bias[2];
            _params[0] = _mm256_set1_ps(params[0]);
            if (type == ::SimdConvolutionActivationRestrictRange)
                _params[1] = _mm256_set1_ps(params[1]);

            dst += yBeg * p.dstW * p.dstC;
            size_t dc = 0;
            for (; dc < dstC; dc += DF)
            {
                size_t tail = Simd::Min(DF, dstC - dc);
                _bias[0] = _mm256_loadu_ps(bias + dc + 0);
                _bias[1] = _mm256_loadu_ps(bias + dc + F);
                if (type == ::SimdConvolutionActivationPrelu)
                {
                    _params[0] = _mm256_loadu_ps(params + dc + 0);
                    _params[1] = _mm256_loadu_ps(params + dc + F);
                }
                float * pDst = dst + dc;
                for (size_t y = yBeg; y < yEnd; ++y)
                {
                    const float * pSrc = src + (y&srcM)*srcW*F;
                    size_t x = 0;
                    for (; x < dstW6; x += 6, pDst += 6 * dstC, pSrc += 6 * F)
                        OutputConvolution_2x6<term, type>(pSrc, srcC, srcS, weight, _bias, _params, pDst, dstC, tail);
                    if (dstW - dstW6 == 4)
                        OutputConvolution_2x4<term, type>(pSrc, srcC, srcS, weight, _bias, _params, pDst, dstC, tail), pDst += 4 * dstC;
                    else
                    {
                        for (; x < dstW3; x += 3, pDst += 3 * dstC, pSrc += 3 * F)
                            OutputConvolution_2x3<term, type>(pSrc, srcC, srcS, weight, _bias, _params, pDst, dstC, tail);
                        for (; x < dstW; ++x, pDst += dstC, pSrc += F)
                            OutputConvolution_2x1<term, type>(pSrc, srcC, srcS, weight, _bias, _params, pDst, dstC, tail);
                    }
                }
                weight += srcC * DF;
            }
        }

        template <SimdConvolutionActivationType type> void SetConvolutionPtr(const MergConvParam & p, size_t index, MergedConvolution::ConvolutionPtr convolution[3])
        {
            switch (index)
            {
            case 0:
                if (p.conv[0].kernelY == 1 && p.conv[0].strideY == 1)
                    convolution[0] = InputConvolution1x1<type>;
                else
                    convolution[0] = InputConvolution<type>;
                break;
            case 1:
                convolution[1] = DepthwiseConvolution3x3<type>;
                break;
            case 2:
                if (p.add)
                {
                    convolution[2] = OutputConvolution<TermLast, type>;
                    convolution[3] = OutputConvolution<TermIterim, type>;
                    convolution[4] = OutputConvolution<TermIterim, type>;
                    convolution[5] = OutputConvolution<TermLast, type>;
                }
                else
                {
                    convolution[2] = OutputConvolution<TermSingle, type>;
                    convolution[3] = OutputConvolution<TermFirst, type>;
                    convolution[4] = OutputConvolution<TermIterim, type>;
                    convolution[5] = OutputConvolution<TermLast, type>;
                }
                break;
            default:
                assert(0);
            }
        }

        MergedConvolution::MergedConvolution(const MergConvParam & p)
            : Sse::MergedConvolution(p)
        {
            SetSize(32 * 1024, 256 * 1024, 2048 * 1024, Avx::F);
            for (size_t i = 0; i < _param.count; ++i)
            {
                switch (p.conv[i].activation)
                {
                case SimdConvolutionActivationIdentity: SetConvolutionPtr<SimdConvolutionActivationIdentity>(_param, i, _convolution); break;
                case SimdConvolutionActivationRelu: SetConvolutionPtr<SimdConvolutionActivationRelu>(_param, i, _convolution); break;
                case SimdConvolutionActivationLeakyRelu: SetConvolutionPtr<SimdConvolutionActivationLeakyRelu>(_param, i, _convolution); break;
                case SimdConvolutionActivationRestrictRange: SetConvolutionPtr<SimdConvolutionActivationRestrictRange>(_param, i, _convolution); break;
                case SimdConvolutionActivationPrelu: SetConvolutionPtr<SimdConvolutionActivationPrelu>(_param, i, _convolution); break;
                default: assert(0);
                }
            }
        }

        //---------------------------------------------------------------------

        void * MergedConvolutionInit(SimdBool trans, size_t batch, const SimdConvolutionParameters * convs, size_t count, SimdBool add)
        {
            MergConvParam param(trans, batch, convs, count, add);
            if (!param.Valid())
                return NULL;
            if (param.conv[2].dstC < F)
                return new Sse::MergedConvolution(param);
            else
                return new Avx::MergedConvolution(param);
        }
    }
 #endif//SIMD_AVX_ENABLE
}