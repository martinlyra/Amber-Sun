//
// Created by Martin Lyrå on 2017-12-21.
//

#ifndef AMBER_SUN_MATRIX4_FUNCTIONS_H
#define AMBER_SUN_MATRIX4_FUNCTIONS_H

#include "Matrix4.h"

class MatrixInversion
{
public:
    /**
     * 4x4 Matrix inversion using Gauss-Jordan elimination method
     * Time complexity is estimated to be O(N^3) where N is the side of a square matrix
     *
     * Using method as described here:
     * https://www.intmath.com/matrices-determinants/inverse-matrix-gauss-jordan-elimination.php
     *
     * @tparam T
     * @param in
     * @param out
     */
    template<typename T>
    static void GaussJordanElimination(const Matrix4<T> in, const Matrix4<T>& out)
    {
        // TODO: Finish this bullshit, consult with the source provided above
        auto md0 = in.data.asArray();
        auto md1 = out.data.asArray();

        for (int i = 0; i < 4; i++)
        {
            int I = i*5;
            T factor = md0[I]; // i + i*4 = i*5

            /*
            if (!factor)
            {
                int o = 1;
                for (int j = 0; j < 4; j++) {
                    if (md0[I + o]) { // the targeted number must not be a zero
                        md0[i + j] += md0[i + j + o];
                        md1[i + j] += md1[i + j + o];
                    } else { o++; j--; continue; }
                }
            }
             */


        }
    }

    /**
     * Inversion of 4x4 matrix using the large yet simple and raw bruteforce formula.
     *
     * As described here:
     * http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
     *
     * @tparam T
     * @param in
     * @param out
     */
    template<typename T>
    static void Bruteforce(const Matrix4<T> in, Matrix4<T>& out)
    {
        auto im = in.data.asMatrix;
        T determine
                =   im._00*(im._11*im._22*im._33 + im._12*im._23*im._31 + im._13*im._21*im._32)
                +   im._01*(im._10*im._23*im._32 + im._12*im._20*im._33 + im._13*im._22*im._30)
                +   im._02*(im._10*im._21*im._33 + im._11*im._23*im._30 + im._13*im._23*im._31)
                +   im._03*(im._10*im._22*im._32 + im._11*im._20*im._32 + im._12*im._21*im._30)

                -   im._00*(im._11*im._23*im._32 + im._12*im._21*im._33 + im._13*im._22*im._31)
                -   im._01*(im._10*im._22*im._33 + im._12*im._23*im._30 + im._13*im._20*im._32)
                -   im._02*(im._10*im._23*im._31 + im._11*im._20*im._33 + im._13*im._21*im._30)
                -   im._03*(im._10*im._21*im._32 + im._11*im._22*im._30 + im._12*im._20*im._31);

        auto om = &out.data.asMatrix;

        /* Row 1 */
        om->_00 = im._11*im._22*im._33 + im._12*im._23*im._31 + im._13*im._21*im._32
                - im._11*im._23*im._32 - im._12*im._21*im._33 - im._13*im._22*im._31;

        om->_01 = im._01*im._23*im._32 + im._02*im._21*im._33 + im._03*im._22*im._31
                - im._01*im._22*im._31 - im._02*im._23*im._31 - im._03*im._21*im._32;

        om->_02 = im._01*im._23*im._33 + im._02*im._13*im._31 + im._03*im._11*im._32
                - im._01*im._13*im._32 - im._02*im._11*im._33 - im._03*im._12*im._31;

        om->_03 = im._01*im._13*im._22 + im._02*im._11*im._23 + im._03*im._12*im._21
                - im._01*im._12*im._23 - im._02*im._13*im._21 - im._03*im._11*im._22;

        /* Row 2 */
        om->_10 = im._10*im._23*im._32 + im._12*im._20*im._33 + im._13*im._22*im._30
                - im._10*im._22*im._33 - im._12*im._23*im._30 - im._13*im._20*im._32;

        om->_11 = im._00*im._22*im._33 + im._02*im._23*im._30 + im._03*im._20*im._32
                - im._00*im._23*im._32 - im._02*im._20*im._33 - im._03*im._22*im._30;

        om->_12 = im._00*im._13*im._32 + im._02*im._10*im._33 + im._03*im._12*im._30
                - im._00*im._12*im._33 - im._02*im._13*im._30 - im._03*im._10*im._32;

        om->_13 = im._00*im._12*im._23 + im._02*im._13*im._20 + im._03*im._10*im._22
                - im._00*im._13*im._22 - im._02*im._10*im._23 - im._03*im._12*im._20;

        /* Row 3 */
        om->_20 = im._10*im._21*im._33 + im._11*im._23*im._30 + im._13*im._20*im._31
                - im._10*im._23*im._31 - im._11*im._20*im._33 - im._13*im._21*im._30;

        om->_21 = im._00*im._23*im._31 + im._01*im._20*im._33 + im._03*im._21*im._30
                - im._00*im._21*im._33 - im._01*im._23*im._30 - im._03*im._20*im._31;

        om->_22 = im._00*im._11*im._33 + im._01*im._13*im._30 + im._03*im._10*im._31
                - im._00*im._13*im._31 - im._01*im._10*im._33 - im._03*im._11*im._30;

        om->_23 = im._00*im._13*im._21 + im._01*im._10*im._23 + im._03*im._11*im._20
                - im._00*im._11*im._23 - im._01*im._13*im._20 - im._03*im._10*im._21;

        /* Row 4 */
        om->_30 = im._10*im._22*im._31 + im._11*im._20*im._32 + im._12*im._21*im._30
                - im._10*im._21*im._32 - im._11*im._22*im._30 - im._12*im._20*im._31;

        om->_31 = im._00*im._21*im._32 + im._01*im._22*im._30 + im._02*im._20*im._31
                - im._00*im._22*im._31 - im._01*im._20*im._32 - im._02*im._21*im._30;

        om->_32 = im._00*im._12*im._31 + im._01*im._10*im._32 + im._02*im._11*im._30
                - im._00*im._11*im._32 - im._01*im._12*im._30 - im._02*im._10*im._31;

        om->_33 = im._00*im._11*im._22 + im._01*im._12*im._20 + im._02*im._10*im._21
                - im._00*im._12*im._21 - im._01*im._10*im._22 - im._02*im._11*im._20;

        out / determine;
    }

};

#endif //AMBER_SUN_MATRIX4_FUNCTIONS_H
