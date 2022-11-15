/******************************************************************************
 * @file     arm_math.h
 * @brief    Public header file for CMSIS DSP LibraryU
 * @version  V1.5.3
 * @date     10. January 2018
 ******************************************************************************/
/*
 * Copyright (c) 2010-2018 Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
   \mainpage CMSIS DSP Software Library
   *
   * Introduction
   * ------------
   *
   * This user manual describes the CMSIS DSP software library,
   * a suite of common signal processing functions for use on Cortex-M processor based devices.
   *
   * The library is divided into a number of functions each covering a specific category:
   * - Basic math functions
   * - Fast math functions
   * - Complex math functions
   * - Filters
   * - Matrix functions
   * - Transforms
   * - Motor control functions
   * - Statistical functions
   * - Support functions
   * - Interpolation functions
   *
   * The library has separate functions for operating on 8-bit integers, 16-bit integers,
   * 32-bit integer and 32-bit floating-point values.
   *
   * Using the Library
   * ------------
   *
   * The library installer contains prebuilt versions of the libraries in the <code>Lib</code> folder.
   * - arm_cortexM7lfdp_math.lib (Cortex-M7, Little endian, Double Precision Floating Point Unit)
   * - arm_cortexM7bfdp_math.lib (Cortex-M7, Big endian, Double Precision Floating Point Unit)
   * - arm_cortexM7lfsp_math.lib (Cortex-M7, Little endian, Single Precision Floating Point Unit)
   * - arm_cortexM7bfsp_math.lib (Cortex-M7, Big endian and Single Precision Floating Point Unit on)
   * - arm_cortexM7l_math.lib (Cortex-M7, Little endian)
   * - arm_cortexM7b_math.lib (Cortex-M7, Big endian)
   * - arm_cortexM4lf_math.lib (Cortex-M4, Little endian, Floating Point Unit)
   * - arm_cortexM4bf_math.lib (Cortex-M4, Big endian, Floating Point Unit)
   * - arm_cortexM4l_math.lib (Cortex-M4, Little endian)
   * - arm_cortexM4b_math.lib (Cortex-M4, Big endian)
   * - arm_cortexM3l_math.lib (Cortex-M3, Little endian)
   * - arm_cortexM3b_math.lib (Cortex-M3, Big endian)
   * - arm_cortexM0l_math.lib (Cortex-M0 / Cortex-M0+, Little endian)
   * - arm_cortexM0b_math.lib (Cortex-M0 / Cortex-M0+, Big endian)
   * - arm_ARMv8MBLl_math.lib (Armv8-M Baseline, Little endian)
   * - arm_ARMv8MMLl_math.lib (Armv8-M Mainline, Little endian)
   * - arm_ARMv8MMLlfsp_math.lib (Armv8-M Mainline, Little endian, Single Precision Floating Point Unit)
   * - arm_ARMv8MMLld_math.lib (Armv8-M Mainline, Little endian, DSP instructions)
   * - arm_ARMv8MMLldfsp_math.lib (Armv8-M Mainline, Little endian, DSP instructions, Single Precision Floating Point Unit)
   *
   * The library functions are declared in the public file <code>arm_math.h</code> which is placed in the <code>Include</code> folder.
   * Simply include this file and link the appropriate library in the application and begin calling the library functions. The Library supports single
   * public header file <code> arm_math.h</code> for Cortex-M cores with little endian and big endian. Same header file will be used for floating point unit(FPU) variants.
   * Define the appropriate preprocessor macro ARM_MATH_CM7 or ARM_MATH_CM4 or ARM_MATH_CM3 or
   * ARM_MATH_CM0 or ARM_MATH_CM0PLUS depending on the target processor in the application.
   * For Armv8-M cores define preprocessor macro ARM_MATH_ARMV8MBL or ARM_MATH_ARMV8MML.
   * Set preprocessor macro __DSP_PRESENT if Armv8-M Mainline core supports DSP instructions.
   * 
   *
   * Examples
   * --------
   *
   * The library ships with a number of examples which demonstrate how to use the library functions.
   *
   * Toolchain Support
   * ------------
   *
   * The library has been developed and tested with MDK version 5.14.0.0
   * The library is being tested in GCC and IAR toolchains and updates on this activity will be made available shortly.
   *
   * Building the Library
   * ------------
   *
   * The library installer contains a project file to rebuild libraries on MDK toolchain in the <code>CMSIS\\DSP_Lib\\Source\\ARM</code> folder.
   * - arm_cortexM_math.uvprojx
   *
   *
   * The libraries can be built by opening the arm_cortexM_math.uvprojx project in MDK-ARM, selecting a specific target, and defining the optional preprocessor macros detailed above.
   *
   * Preprocessor Macros
   * ------------
   *
   * Each library project have different preprocessor macros.
   *
   * - UNALIGNED_SUPPORT_DISABLE:
   *
   * Define macro UNALIGNED_SUPPORT_DISABLE, If the silicon does not support unaligned memory access
   *
   * - ARM_MATH_BIG_ENDIAN:
   *
   * Define macro ARM_MATH_BIG_ENDIAN to build the library for big endian targets. By default library builds for little endian targets.
   *
   * - ARM_MATH_MATRIX_CHECK:
   *
   * Define macro ARM_MATH_MATRIX_CHECK for checking on the input and output sizes of matrices
   *
   * - ARM_MATH_ROUNDING:
   *
   * Define macro ARM_MATH_ROUNDING for rounding on support functions
   *
   * - ARM_MATH_CMx:
   *
   * Define macro ARM_MATH_CM4 for building the library on Cortex-M4 target, ARM_MATH_CM3 for building library on Cortex-M3 target
   * and ARM_MATH_CM0 for building library on Cortex-M0 target, ARM_MATH_CM0PLUS for building library on Cortex-M0+ target, and
   * ARM_MATH_CM7 for building the library on cortex-M7.
   *
   * - ARM_MATH_ARMV8MxL:
   *
   * Define macro ARM_MATH_ARMV8MBL for building the library on Armv8-M Baseline target, ARM_MATH_ARMV8MML for building library
   * on Armv8-M Mainline target.
   *
   * - __FPU_PRESENT:
   *
   * Initialize macro __FPU_PRESENT = 1 when building on FPU supported Targets. Enable this macro for floating point libraries.
   *
   * - __DSP_PRESENT:
   *
   * Initialize macro __DSP_PRESENT = 1 when Armv8-M Mainline core supports DSP instructions.
   *
   * <hr>
   * CMSIS-DSP in ARM::CMSIS Pack
   * -----------------------------
   *
   * The following files relevant to CMSIS-DSP are present in the <b>ARM::CMSIS</b> Pack directories:
   * |File/Folder                   |Content                                                                 |
   * |------------------------------|------------------------------------------------------------------------|
   * |\b CMSIS\\Documentation\\DSP  | This documentation                                                     |
   * |\b CMSIS\\DSP_Lib             | Software license agreement (license.txt)                               |
   * |\b CMSIS\\DSP_Lib\\Examples   | Example projects demonstrating the usage of the library functions      |
   * |\b CMSIS\\DSP_Lib\\Source     | Source files for rebuilding the library                                |
   *
   * <hr>
   * Revision History of CMSIS-DSP
   * ------------
   * Please refer to \ref ChangeLog_pg.
   *
   * Copyright Notice
   * ------------
   *
   * Copyright (C) 2010-2015 Arm Limited. All rights reserved.
   */


/**
 * @defgroup groupMath Basic Math Functions
 */

/**
 * @defgroup groupFastMath Fast Math Functions
 * This set of functions provides a fast approximation to sine, cosine, and square root.
 * As compared to most of the other functions in the CMSIS math library, the fast math functions
 * operate on individual values and not arrays.
 * There are separate functions for Q15, Q31, and floating-point data.
 *
 */

/**
 * @defgroup groupCmplxMath Complex Math Functions
 * This set of functions operates on complex data vectors.
 * The data in the complex arrays is stored in an interleaved fashion
 * (real, imag, real, imag, ...).
 * In the API functions, the number of samples in a complex array refers
 * to the number of complex values; the array contains twice this number of
 * real values.
 */

/**
 * @defgroup groupFilters Filtering Functions
 */

/**
 * @defgroup groupMatrix Matrix Functions
 *
 * This set of functions provides basic matrix math operations.
 * The functions operate on matrix data structures.  For example,
 * the type
 * definition for the floating-point matrix structure is shown
 * below:
 * <pre>
 *     typedef struct
 *     {
 *       uint16_t numRows;     // number of rows of the matrix.
 *       uint16_t numCols;     // number of columns of the matrix.
 *       float32_t *pData;     // points to the data of the matrix.
 *     } arm_matrix_instance_f32;
 * </pre>
 * There are similar definitions for Q15 and Q31 data types.
 *
 * The structure specifies the size of the matrix and then points to
 * an array of data.  The array is of size <code>numRows X numCols</code>
 * and the values are arranged in row order.  That is, the
 * matrix element (i, j) is stored at:
 * <pre>
 *     pData[i*numCols + j]
 * </pre>
 *
 * \par Init Functions
 * There is an associated initialization function for each type of matrix
 * data structure.
 * The initialization function sets the values of the internal structure fields.
 * Refer to the function <code>arm_mat_init_f32()</code>, <code>arm_mat_init_q31()</code>
 * and <code>arm_mat_init_q15()</code> for floating-point, Q31 and Q15 types,  respectively.
 *
 * \par
 * Use of the initialization function is optional. However, if initialization function is used
 * then the instance structure cannot be placed into a const data section.
 * To place the instance structure in a const data
 * section, manually initialize the data structure.  For example:
 * <pre>
 * <code>arm_matrix_instance_f32 S = {nRows, nColumns, pData};</code>
 * <code>arm_matrix_instance_q31 S = {nRows, nColumns, pData};</code>
 * <code>arm_matrix_instance_q15 S = {nRows, nColumns, pData};</code>
 * </pre>
 * where <code>nRows</code> specifies the number of rows, <code>nColumns</code>
 * specifies the number of columns, and <code>pData</code> points to the
 * data array.
 *
 * \par Size Checking
 * By default all of the matrix functions perform size checking on the input and
 * output matrices. For example, the matrix addition function verifies that the
 * two input matrices and the output matrix all have the same number of rows and
 * columns. If the size check fails the functions return:
 * <pre>
 *     ARM_MATH_SIZE_MISMATCH
 * </pre>
 * Otherwise the functions return
 * <pre>
 *     ARM_MATH_SUCCESS
 * </pre>
 * There is some overhead associated with this matrix size checking.
 * The matrix size checking is enabled via the \#define
 * <pre>
 *     ARM_MATH_MATRIX_CHECK
 * </pre>
 * within the library project settings.  By default this macro is defined
 * and size checking is enabled. By changing the project settings and
 * undefining this macro size checking is eliminated and the functions
 * run a bit faster. With size checking disabled the functions always
 * return <code>ARM_MATH_SUCCESS</code>.
 */

/**
 * @defgroup groupTransforms Transform Functions
 */

/**
 * @defgroup groupController Controller Functions
 */

/**
 * @defgroup groupStats Statistics Functions
 */
/**
 * @defgroup groupSupport Support Functions
 */

/**
 * @defgroup groupInterpolation Interpolation Functions
 * These functions perform 1- and 2-dimensional interpolation of data.
 * Linear interpolation is used for 1-dimensional data and
 * bilinear interpolation is used for 2-dimensional data.
 */

/**
 * @defgroup groupExamples Examples
 */
#ifndef _ARM_MATH_H
#define _ARM_MATH_H

/* Compiler specific diagnostic adjustment */
#if   defined ( __CC_ARM )

#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )

#elif defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#elif defined ( __ICCARM__ )

#elif defined ( __TI_ARM__ )

#elif defined ( __CSMC__ )

#elif defined ( __TASKING__ )

#else
  #error Unknown compiler
#endif


#define __CMSIS_GENERIC         /* disable NVIC and Systick functions */
#define ARM_MATH_CM4

#if defined(ARM_MATH_CM7)
  #include "core_cm7.h"
  #define ARM_MATH_DSP
#elif defined (ARM_MATH_CM4)
  #include "core_cm4.h"
  #define ARM_MATH_DSP
#elif defined (ARM_MATH_CM3)
  #include "core_cm3.h"
#elif defined (ARM_MATH_CM0)
  #include "core_cm0.h"
  #define ARM_MATH_CM0_FAMILY
#elif defined (ARM_MATH_CM0PLUS)
  #include "core_cm0plus.h"
  #define ARM_MATH_CM0_FAMILY
#elif defined (ARM_MATH_ARMV8MBL)
  #include "core_armv8mbl.h"
  #define ARM_MATH_CM0_FAMILY
#elif defined (ARM_MATH_ARMV8MML)
  #include "core_armv8mml.h"
  #if (defined (__DSP_PRESENT) && (__DSP_PRESENT == 1))
    #define ARM_MATH_DSP
  #endif
#else
  #error "Define according the used Cortex core ARM_MATH_CM7, ARM_MATH_CM4, ARM_MATH_CM3, ARM_MATH_CM0PLUS, ARM_MATH_CM0, ARM_MATH_ARMV8MBL, ARM_MATH_ARMV8MML"
#endif

#undef  __CMSIS_GENERIC         /* enable NVIC and Systick functions */
#include "string.h"
#include "math.h"
#ifdef   __cplusplus
extern "C"
{
#endif


  /**
   * @brief Macros required for reciprocal calculation in Normalized LMS
   */

#define DELTA_Q31          (0x100)
#define DELTA_Q15          0x5
#define INDEX_MASK         0x0000003F
#ifndef PI
  #define PI               3.14159265358979f
#endif

  /**
   * @brief Macros required for SINE and COSINE Fast math approximations
   */

#define FAST_MATH_TABLE_SIZE  512
#define FAST_MATH_Q31_SHIFT   (32 - 10)
#define FAST_MATH_Q15_SHIFT   (16 - 10)
#define CONTROLLER_Q31_SHIFT  (32 - 9)
#define TABLE_SPACING_Q31     0x400000
#define TABLE_SPACING_Q15     0x80

  /**
   * @brief Macros required for SINE and COSINE Controller functions
   */
  /* 1.31(q31) Fixed value of 2/360 */
  /* -1 to +1 is divided into 360 values so total spacing is (2/360) */
#define INPUT_SPACING         0xB60B61

  /**
   * @brief Macro for Unaligned Support
   */
#ifndef UNALIGNED_SUPPORT_DISABLE
    #define ALIGN4
#else
  #if defined  (__GNUC__)
    #define ALIGN4 __attribute__((aligned(4)))
  #else
    #define ALIGN4 __align(4)
  #endif
#endif   /* #ifndef UNALIGNED_SUPPORT_DISABLE */

  /**
   * @brief Error status returned by some functions in the library.
   */

  typedef enum
  {
    ARM_MATH_SUCCESS = 0,                /**< No error */
    ARM_MATH_ARGUMENT_ERROR = -1,        /**< One or more arguments are incorrect */
    ARM_MATH_LENGTH_ERROR = -2,          /**< Length of data buffer is incorrect */
    ARM_MATH_SIZE_MISMATCH = -3,         /**< Size of matrices is not compatible with the operation. */
    ARM_MATH_NANINF = -4,                /**< Not-a-number (NaN) or infinity is generated */
    ARM_MATH_SINGULAR = -5,              /**< Generated by matrix inversion if the input matrix is singular and cannot be inverted. */
    ARM_MATH_TEST_FAILURE = -6           /**< Test Failed  */
  } arm_status;

  /**
   * @brief 8-bit fractional data type in 1.7 format.
   */
  typedef int8_t q7_t;

  /**
   * @brief 16-bit fractional data type in 1.15 format.
   */
  typedef int16_t q15_t;

  /**
   * @brief 32-bit fractional data type in 1.31 format.
   */
  typedef int32_t q31_t;

  /**
   * @brief 64-bit fractional data type in 1.63 format.
   */
  typedef int64_t q63_t;

  /**
   * @brief 32-bit floating-point type definition.
   */
  typedef float float32_t;

  /**
   * @brief 64-bit floating-point type definition.
   */
  typedef double float64_t;

  /**
   * @brief definition to read/write two 16 bit values.
   */
#if   defined ( __CC_ARM )
  #define __SIMD32_TYPE int32_t __packed
  #define CMSIS_UNUSED __attribute__((unused))
  #define CMSIS_INLINE __attribute__((always_inline))

#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )
  #define __SIMD32_TYPE int32_t
  #define CMSIS_UNUSED __attribute__((unused))
  #define CMSIS_INLINE __attribute__((always_inline))

#elif defined ( __GNUC__ )
  #define __SIMD32_TYPE int32_t
  #define CMSIS_UNUSED __attribute__((unused))
  #define CMSIS_INLINE __attribute__((always_inline))

#elif defined ( __ICCARM__ )
  #define __SIMD32_TYPE int32_t __packed
  #define CMSIS_UNUSED
  #define CMSIS_INLINE

#elif defined ( __TI_ARM__ )
  #define __SIMD32_TYPE int32_t
  #define CMSIS_UNUSED __attribute__((unused))
  #define CMSIS_INLINE

#elif defined ( __CSMC__ )
  #define __SIMD32_TYPE int32_t
  #define CMSIS_UNUSED
  #define CMSIS_INLINE

#elif defined ( __TASKING__ )
  #define __SIMD32_TYPE __unaligned int32_t
  #define CMSIS_UNUSED
  #define CMSIS_INLINE

#else
  #error Unknown compiler
#endif

#define __SIMD32(addr)        (*(__SIMD32_TYPE **) & (addr))
#define __SIMD32_CONST(addr)  ((__SIMD32_TYPE *)(addr))
#define _SIMD32_OFFSET(addr)  (*(__SIMD32_TYPE *)  (addr))
#define __SIMD64(addr)        (*(int64_t **) & (addr))

#if !defined (ARM_MATH_DSP)
  /**
   * @brief definition to pack two 16 bit values.
   */
#define __PKHBT(ARG1, ARG2, ARG3) ( (((int32_t)(ARG1) <<    0) & (int32_t)0x0000FFFF) | \
                                    (((int32_t)(ARG2) << ARG3) & (int32_t)0xFFFF0000)  )
#define __PKHTB(ARG1, ARG2, ARG3) ( (((int32_t)(ARG1) <<    0) & (int32_t)0xFFFF0000) | \
                                    (((int32_t)(ARG2) >> ARG3) & (int32_t)0x0000FFFF)  )

#endif /* !defined (ARM_MATH_DSP) */

   /**
   * @brief definition to pack four 8 bit values.
   */
#ifndef ARM_MATH_BIG_ENDIAN

#define __PACKq7(v0,v1,v2,v3) ( (((int32_t)(v0) <<  0) & (int32_t)0x000000FF) | \
                                (((int32_t)(v1) <<  8) & (int32_t)0x0000FF00) | \
                                (((int32_t)(v2) << 16) & (int32_t)0x00FF0000) | \
                                (((int32_t)(v3) << 24) & (int32_t)0xFF000000)  )
#else

#define __PACKq7(v0,v1,v2,v3) ( (((int32_t)(v3) <<  0) & (int32_t)0x000000FF) | \
                                (((int32_t)(v2) <<  8) & (int32_t)0x0000FF00) | \
                                (((int32_t)(v1) << 16) & (int32_t)0x00FF0000) | \
                                (((int32_t)(v0) << 24) & (int32_t)0xFF000000)  )

#endif


  /**
   * @brief Clips Q63 to Q31 values.
   */
  CMSIS_INLINE __STATIC_INLINE q31_t clip_q63_to_q31(
  q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFFFFFF ^ ((q31_t) (x >> 63)))) : (q31_t) x;
  }

  /**
   * @brief Clips Q63 to Q15 values.
   */
  CMSIS_INLINE __STATIC_INLINE q15_t clip_q63_to_q15(
  q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFF ^ ((q15_t) (x >> 63)))) : (q15_t) (x >> 15);
  }

  /**
   * @brief Clips Q31 to Q7 values.
   */
  CMSIS_INLINE __STATIC_INLINE q7_t clip_q31_to_q7(
  q31_t x)
  {
    return ((q31_t) (x >> 24) != ((q31_t) x >> 23)) ?
      ((0x7F ^ ((q7_t) (x >> 31)))) : (q7_t) x;
  }

  /**
   * @brief Clips Q31 to Q15 values.
   */
  CMSIS_INLINE __STATIC_INLINE q15_t clip_q31_to_q15(
  q31_t x)
  {
    return ((q31_t) (x >> 16) != ((q31_t) x >> 15)) ?
      ((0x7FFF ^ ((q15_t) (x >> 31)))) : (q15_t) x;
  }

  /**
   * @brief Multiplies 32 X 64 and returns 32 bit result in 2.30 format.
   */

  CMSIS_INLINE __STATIC_INLINE q63_t mult32x64(
  q63_t x,
  q31_t y)
  {
    return ((((q63_t) (x & 0x00000000FFFFFFFF) * y) >> 32) +
            (((q63_t) (x >> 32) * y)));
  }

  /**
   * @brief Function to Calculates 1/in (reciprocal) value of Q31 Data type.
   */

  CMSIS_INLINE __STATIC_INLINE uint32_t arm_recip_q31(
  q31_t in,
  q31_t * dst,
  q31_t * pRecipTable)
  {
    q31_t out;
    uint32_t tempVal;
    uint32_t index, i;
    uint32_t signBits;

    if (in > 0)
    {
      signBits = ((uint32_t) (__CLZ( in) - 1));
    }
    else
    {
      signBits = ((uint32_t) (__CLZ(-in) - 1));
    }

    /* Convert input sample to 1.31 format */
    in = (in << signBits);

    /* calculation of index for initial approximated Val */
    index = (uint32_t)(in >> 24);
    index = (index & INDEX_MASK);

    /* 1.31 with exp 1 */
    out = pRecipTable[index];

    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (i = 0U; i < 2U; i++)
    {
      tempVal = (uint32_t) (((q63_t) in * out) >> 31);
      tempVal = 0x7FFFFFFFu - tempVal;
      /*      1.31 with exp 1 */
      /* out = (q31_t) (((q63_t) out * tempVal) >> 30); */
      out = clip_q63_to_q31(((q63_t) out * tempVal) >> 30);
    }

    /* write output */
    *dst = out;

    /* return num of signbits of out = 1/in value */
    return (signBits + 1U);
  }


  /**
   * @brief Function to Calculates 1/in (reciprocal) value of Q15 Data type.
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t arm_recip_q15(
  q15_t in,
  q15_t * dst,
  q15_t * pRecipTable)
  {
    q15_t out = 0;
    uint32_t tempVal = 0;
    uint32_t index = 0, i = 0;
    uint32_t signBits = 0;

    if (in > 0)
    {
      signBits = ((uint32_t)(__CLZ( in) - 17));
    }
    else
    {
      signBits = ((uint32_t)(__CLZ(-in) - 17));
    }

    /* Convert input sample to 1.15 format */
    in = (in << signBits);

    /* calculation of index for initial approximated Val */
    index = (uint32_t)(in >>  8);
    index = (index & INDEX_MASK);

    /*      1.15 with exp 1  */
    out = pRecipTable[index];

    /* calculation of reciprocal value */
    /* running approximation for two iterations */
    for (i = 0U; i < 2U; i++)
    {
      tempVal = (uint32_t) (((q31_t) in * out) >> 15);
      tempVal = 0x7FFFu - tempVal;
      /*      1.15 with exp 1 */
      out = (q15_t) (((q31_t) out * tempVal) >> 14);
      /* out = clip_q31_to_q15(((q31_t) out * tempVal) >> 14); */
    }

    /* write output */
    *dst = out;

    /* return num of signbits of out = 1/in value */
    return (signBits + 1);
  }


/*
 * @brief C custom defined intrinsic function for M3 and M0 processors
 */
#if !defined (ARM_MATH_DSP)

  /*
   * @brief C custom defined QADD8 for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __QADD8(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s, t, u;

    r = __SSAT(((((q31_t)x << 24) >> 24) + (((q31_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((q31_t)x << 16) >> 24) + (((q31_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((q31_t)x <<  8) >> 24) + (((q31_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((q31_t)x      ) >> 24) + (((q31_t)y      ) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r      )));
  }


  /*
   * @brief C custom defined QSUB8 for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __QSUB8(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s, t, u;

    r = __SSAT(((((q31_t)x << 24) >> 24) - (((q31_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((q31_t)x << 16) >> 24) - (((q31_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((q31_t)x <<  8) >> 24) - (((q31_t)y <<  8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((q31_t)x      ) >> 24) - (((q31_t)y      ) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s <<  8) | (r      )));
  }


  /*
   * @brief C custom defined QADD16 for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __QADD16(
  uint32_t x,
  uint32_t y)
  {
/*  q31_t r,     s;  without initialisation 'arm_offset_q15 test' fails  but 'intrinsic' tests pass! for armCC */
    q31_t r = 0, s = 0;

    r = __SSAT(((((q31_t)x << 16) >> 16) + (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x      ) >> 16) + (((q31_t)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SHADD16 for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SHADD16(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = (((((q31_t)x << 16) >> 16) + (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x      ) >> 16) + (((q31_t)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined QSUB16 for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __QSUB16(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = __SSAT(((((q31_t)x << 16) >> 16) - (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x      ) >> 16) - (((q31_t)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SHSUB16 for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SHSUB16(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = (((((q31_t)x << 16) >> 16) - (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x      ) >> 16) - (((q31_t)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined QASX for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __QASX(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = __SSAT(((((q31_t)x << 16) >> 16) - (((q31_t)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x      ) >> 16) + (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SHASX for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SHASX(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = (((((q31_t)x << 16) >> 16) - (((q31_t)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x      ) >> 16) + (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined QSAX for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __QSAX(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = __SSAT(((((q31_t)x << 16) >> 16) + (((q31_t)y      ) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x      ) >> 16) - (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SHSAX for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SHSAX(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = (((((q31_t)x << 16) >> 16) + (((q31_t)y      ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x      ) >> 16) - (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r      )));
  }


  /*
   * @brief C custom defined SMUSDX for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SMUSDX(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y      ) >> 16)) -
                       ((((q31_t)x      ) >> 16) * (((q31_t)y << 16) >> 16))   ));
  }

  /*
   * @brief C custom defined SMUADX for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SMUADX(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y      ) >> 16)) +
                       ((((q31_t)x      ) >> 16) * (((q31_t)y << 16) >> 16))   ));
  }


  /*
   * @brief C custom defined QADD for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE int32_t __QADD(
  int32_t x,
  int32_t y)
  {
    return ((int32_t)(clip_q63_to_q31((q63_t)x + (q31_t)y)));
  }


  /*
   * @brief C custom defined QSUB for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE int32_t __QSUB(
  int32_t x,
  int32_t y)
  {
    return ((int32_t)(clip_q63_to_q31((q63_t)x - (q31_t)y)));
  }


  /*
   * @brief C custom defined SMLAD for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SMLAD(
  uint32_t x,
  uint32_t y,
  uint32_t sum)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ((((q31_t)x      ) >> 16) * (((q31_t)y      ) >> 16)) +
                       ( ((q31_t)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMLADX for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SMLADX(
  uint32_t x,
  uint32_t y,
  uint32_t sum)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y      ) >> 16)) +
                       ((((q31_t)x      ) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ( ((q31_t)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMLSDX for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SMLSDX(
  uint32_t x,
  uint32_t y,
  uint32_t sum)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y      ) >> 16)) -
                       ((((q31_t)x      ) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ( ((q31_t)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMLALD for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint64_t __SMLALD(
  uint32_t x,
  uint32_t y,
  uint64_t sum)
  {
/*  return (sum + ((q15_t) (x >> 16) * (q15_t) (y >> 16)) + ((q15_t) x * (q15_t) y)); */
    return ((uint64_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ((((q31_t)x      ) >> 16) * (((q31_t)y      ) >> 16)) +
                       ( ((q63_t)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMLALDX for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint64_t __SMLALDX(
  uint32_t x,
  uint32_t y,
  uint64_t sum)
  {
/*  return (sum + ((q15_t) (x >> 16) * (q15_t) y)) + ((q15_t) x * (q15_t) (y >> 16)); */
    return ((uint64_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y      ) >> 16)) +
                       ((((q31_t)x      ) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ( ((q63_t)sum    )                                  )   ));
  }


  /*
   * @brief C custom defined SMUAD for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SMUAD(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ((((q31_t)x      ) >> 16) * (((q31_t)y      ) >> 16))   ));
  }


  /*
   * @brief C custom defined SMUSD for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SMUSD(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) -
                       ((((q31_t)x      ) >> 16) * (((q31_t)y      ) >> 16))   ));
  }


  /*
   * @brief C custom defined SXTB16 for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE uint32_t __SXTB16(
  uint32_t x)
  {
    return ((uint32_t)(((((q31_t)x << 24) >> 24) & (q31_t)0x0000FFFF) |
                       ((((q31_t)x <<  8) >>  8) & (q31_t)0xFFFF0000)  ));
  }

  /*
   * @brief C custom defined SMMLA for M3 and M0 processors
   */
  CMSIS_INLINE __STATIC_INLINE int32_t __SMMLA(
  int32_t x,
  int32_t y,
  int32_t sum)
  {
    return (sum + (int32_t) (((int64_t) x * y) >> 32));
  }

#endif /* !defined (ARM_MATH_DSP) */


  /**
   * @brief Instance structure for the Q7 FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;        /**< number of filter coefficients in the filter. */
    q7_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q7_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
  } arm_fir_instance_q7;

  /**
   * @brief Instance structure for the Q15 FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;         /**< number of filter coefficients in the filter. */
    q15_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q15_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
  } arm_fir_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;         /**< number of filter coefficients in the filter. */
    q31_t *pState;            /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q31_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps. */
  } arm_fir_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;     /**< number of filter coefficients in the filter. */
    float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
  } arm_fir_instance_f32;


  /**
   * @brief Processing function for the Q7 FIR filter.
   * @param[in]  S          points to an instance of the Q7 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_q7(
  const arm_fir_instance_q7 * S,
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q7 FIR filter.
   * @param[in,out] S          points to an instance of the Q7 FIR structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed.
   */
  void arm_fir_init_q7(
  arm_fir_instance_q7 * S,
  uint16_t numTaps,
  q7_t * pCoeffs,
  q7_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 FIR filter.
   * @param[in]  S          points to an instance of the Q15 FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_q15(
  const arm_fir_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Processing function for the fast Q15 FIR filter for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q15 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_fast_q15(
  const arm_fir_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 FIR filter.
   * @param[in,out] S          points to an instance of the Q15 FIR filter structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter. Must be even and greater than or equal to 4.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   * @return The function returns ARM_MATH_SUCCESS if initialization was successful or ARM_MATH_ARGUMENT_ERROR if
   * <code>numTaps</code> is not a supported value.
   */
  arm_status arm_fir_init_q15(
  arm_fir_instance_q15 * S,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 FIR filter.
   * @param[in]  S          points to an instance of the Q31 FIR filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_q31(
  const arm_fir_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Processing function for the fast Q31 FIR filter for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q31 FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_fast_q31(
  const arm_fir_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 FIR filter.
   * @param[in,out] S          points to an instance of the Q31 FIR structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   */
  void arm_fir_init_q31(
  arm_fir_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point FIR filter.
   * @param[in]  S          points to an instance of the floating-point FIR structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_f32(
  const arm_fir_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point FIR filter.
   * @param[in,out] S          points to an instance of the floating-point FIR filter structure.
   * @param[in]     numTaps    Number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of samples that are processed at a time.
   */
  void arm_fir_init_f32(
  arm_fir_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 Biquad cascade filter.
   */
  typedef struct
  {
    int8_t numStages;        /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    q15_t *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    q15_t *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
    int8_t postShift;        /**< Additional shift, in bits, applied to each output sample. */
  } arm_biquad_casd_df1_inst_q15;

  /**
   * @brief Instance structure for the Q31 Biquad cascade filter.
   */
  typedef struct
  {
    uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    q31_t *pState;           /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    q31_t *pCoeffs;          /**< Points to the array of coefficients.  The array is of length 5*numStages. */
    uint8_t postShift;       /**< Additional shift, in bits, applied to each output sample. */
  } arm_biquad_casd_df1_inst_q31;

  /**
   * @brief Instance structure for the floating-point Biquad cascade filter.
   */
  typedef struct
  {
    uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float32_t *pState;       /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
    float32_t *pCoeffs;      /**< Points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_casd_df1_inst_f32;


  /**
   * @brief Processing function for the Q15 Biquad cascade filter.
   * @param[in]  S          points to an instance of the Q15 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_q15(
  const arm_biquad_casd_df1_inst_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 Biquad cascade filter.
   * @param[in,out] S          points to an instance of the Q15 Biquad cascade structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     postShift  Shift to be applied to the output. Varies according to the coefficients format
   */
  void arm_biquad_cascade_df1_init_q15(
  arm_biquad_casd_df1_inst_q15 * S,
  uint8_t numStages,
  q15_t * pCoeffs,
  q15_t * pState,
  int8_t postShift);


  /**
   * @brief Fast but less precise processing function for the Q15 Biquad cascade filter for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q15 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_fast_q15(
  const arm_biquad_casd_df1_inst_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 Biquad cascade filter
   * @param[in]  S          points to an instance of the Q31 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_q31(
  const arm_biquad_casd_df1_inst_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Fast but less precise processing function for the Q31 Biquad cascade filter for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q31 Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_fast_q31(
  const arm_biquad_casd_df1_inst_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 Biquad cascade filter.
   * @param[in,out] S          points to an instance of the Q31 Biquad cascade structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     postShift  Shift to be applied to the output. Varies according to the coefficients format
   */
  void arm_biquad_cascade_df1_init_q31(
  arm_biquad_casd_df1_inst_q31 * S,
  uint8_t numStages,
  q31_t * pCoeffs,
  q31_t * pState,
  int8_t postShift);


  /**
   * @brief Processing function for the floating-point Biquad cascade filter.
   * @param[in]  S          points to an instance of the floating-point Biquad cascade structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df1_f32(
  const arm_biquad_casd_df1_inst_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point Biquad cascade filter.
   * @param[in,out] S          points to an instance of the floating-point Biquad cascade structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void arm_biquad_cascade_df1_init_f32(
  arm_biquad_casd_df1_inst_f32 * S,
  uint8_t numStages,
  float32_t * pCoeffs,
  float32_t * pState);


  /**
   * @brief Instance structure for the floating-point matrix structure.
   */
  typedef struct
  {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    float32_t *pData;     /**< points to the data of the matrix. */
  } arm_matrix_instance_f32;


  /**
   * @brief Instance structure for the floating-point matrix structure.
   */
  typedef struct
  {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    float64_t *pData;     /**< points to the data of the matrix. */
  } arm_matrix_instance_f64;

  /**
   * @brief Instance structure for the Q15 matrix structure.
   */
  typedef struct
  {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    q15_t *pData;         /**< points to the data of the matrix. */
  } arm_matrix_instance_q15;

  /**
   * @brief Instance structure for the Q31 matrix structure.
   */
  typedef struct
  {
    uint16_t numRows;     /**< number of rows of the matrix.     */
    uint16_t numCols;     /**< number of columns of the matrix.  */
    q31_t *pData;         /**< points to the data of the matrix. */
  } arm_matrix_instance_q31;


  /**
   * @brief Floating-point matrix addition.
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_add_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);


  /**
   * @brief Q15 matrix addition.
   * @param[in]   pSrcA  points to the first input matrix structure
   * @param[in]   pSrcB  points to the second input matrix structure
   * @param[out]  pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_add_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst);


  /**
   * @brief Q31 matrix addition.
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_add_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief Floating-point, complex, matrix multiplication.
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_cmplx_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);


  /**
   * @brief Q15, complex,  matrix multiplication.
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_cmplx_mult_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst,
  q15_t * pScratch);


  /**
   * @brief Q31, complex, matrix multiplication.
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_cmplx_mult_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief Floating-point matrix transpose.
   * @param[in]  pSrc  points to the input matrix
   * @param[out] pDst  points to the output matrix
   * @return    The function returns either  <code>ARM_MATH_SIZE_MISMATCH</code>
   * or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_trans_f32(
  const arm_matrix_instance_f32 * pSrc,
  arm_matrix_instance_f32 * pDst);


  /**
   * @brief Q15 matrix transpose.
   * @param[in]  pSrc  points to the input matrix
   * @param[out] pDst  points to the output matrix
   * @return    The function returns either  <code>ARM_MATH_SIZE_MISMATCH</code>
   * or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_trans_q15(
  const arm_matrix_instance_q15 * pSrc,
  arm_matrix_instance_q15 * pDst);


  /**
   * @brief Q31 matrix transpose.
   * @param[in]  pSrc  points to the input matrix
   * @param[out] pDst  points to the output matrix
   * @return    The function returns either  <code>ARM_MATH_SIZE_MISMATCH</code>
   * or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_trans_q31(
  const arm_matrix_instance_q31 * pSrc,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief Floating-point matrix multiplication
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);


  /**
   * @brief Q15 matrix multiplication
   * @param[in]  pSrcA   points to the first input matrix structure
   * @param[in]  pSrcB   points to the second input matrix structure
   * @param[out] pDst    points to output matrix structure
   * @param[in]  pState  points to the array for storing intermediate results
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_mult_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst,
  q15_t * pState);


  /**
   * @brief Q15 matrix multiplication (fast variant) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA   points to the first input matrix structure
   * @param[in]  pSrcB   points to the second input matrix structure
   * @param[out] pDst    points to output matrix structure
   * @param[in]  pState  points to the array for storing intermediate results
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_mult_fast_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst,
  q15_t * pState);


  /**
   * @brief Q31 matrix multiplication
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_mult_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief Q31 matrix multiplication (fast variant) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_mult_fast_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief Floating-point matrix subtraction
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_sub_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
  arm_matrix_instance_f32 * pDst);


  /**
   * @brief Q15 matrix subtraction
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_sub_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
  arm_matrix_instance_q15 * pDst);


  /**
   * @brief Q31 matrix subtraction
   * @param[in]  pSrcA  points to the first input matrix structure
   * @param[in]  pSrcB  points to the second input matrix structure
   * @param[out] pDst   points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_sub_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief Floating-point matrix scaling.
   * @param[in]  pSrc   points to the input matrix
   * @param[in]  scale  scale factor
   * @param[out] pDst   points to the output matrix
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_scale_f32(
  const arm_matrix_instance_f32 * pSrc,
  float32_t scale,
  arm_matrix_instance_f32 * pDst);


  /**
   * @brief Q15 matrix scaling.
   * @param[in]  pSrc        points to input matrix
   * @param[in]  scaleFract  fractional portion of the scale factor
   * @param[in]  shift       number of bits to shift the result by
   * @param[out] pDst        points to output matrix
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_scale_q15(
  const arm_matrix_instance_q15 * pSrc,
  q15_t scaleFract,
  int32_t shift,
  arm_matrix_instance_q15 * pDst);


  /**
   * @brief Q31 matrix scaling.
   * @param[in]  pSrc        points to input matrix
   * @param[in]  scaleFract  fractional portion of the scale factor
   * @param[in]  shift       number of bits to shift the result by
   * @param[out] pDst        points to output matrix structure
   * @return     The function returns either
   * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.
   */
  arm_status arm_mat_scale_q31(
  const arm_matrix_instance_q31 * pSrc,
  q31_t scaleFract,
  int32_t shift,
  arm_matrix_instance_q31 * pDst);


  /**
   * @brief  Q31 matrix initialization.
   * @param[in,out] S         points to an instance of the floating-point matrix structure.
   * @param[in]     nRows     number of rows in the matrix.
   * @param[in]     nColumns  number of columns in the matrix.
   * @param[in]     pData     points to the matrix data array.
   */
  void arm_mat_init_q31(
  arm_matrix_instance_q31 * S,
  uint16_t nRows,
  uint16_t nColumns,
  q31_t * pData);


  /**
   * @brief  Q15 matrix initialization.
   * @param[in,out] S         points to an instance of the floating-point matrix structure.
   * @param[in]     nRows     number of rows in the matrix.
   * @param[in]     nColumns  number of columns in the matrix.
   * @param[in]     pData     points to the matrix data array.
   */
  void arm_mat_init_q15(
  arm_matrix_instance_q15 * S,
  uint16_t nRows,
  uint16_t nColumns,
  q15_t * pData);


  /**
   * @brief  Floating-point matrix initialization.
   * @param[in,out] S         points to an instance of the floating-point matrix structure.
   * @param[in]     nRows     number of rows in the matrix.
   * @param[in]     nColumns  number of columns in the matrix.
   * @param[in]     pData     points to the matrix data array.
   */
  void arm_mat_init_f32(
  arm_matrix_instance_f32 * S,
  uint16_t nRows,
  uint16_t nColumns,
  float32_t * pData);



  /**
   * @brief Instance structure for the Q15 PID Control.
   */
  typedef struct
  {
    q15_t A0;           /**< The derived gain, A0 = Kp + Ki + Kd . */
#if !defined (ARM_MATH_DSP)
    q15_t A1;
    q15_t A2;
#else
    q31_t A1;           /**< The derived gain A1 = -Kp - 2Kd | Kd.*/
#endif
    q15_t state[3];     /**< The state array of length 3. */
    q15_t Kp;           /**< The proportional gain. */
    q15_t Ki;           /**< The integral gain. */
    q15_t Kd;           /**< The derivative gain. */
  } arm_pid_instance_q15;

  /**
   * @brief Instance structure for the Q31 PID Control.
   */
  typedef struct
  {
    q31_t A0;            /**< The derived gain, A0 = Kp + Ki + Kd . */
    q31_t A1;            /**< The derived gain, A1 = -Kp - 2Kd. */
    q31_t A2;            /**< The derived gain, A2 = Kd . */
    q31_t state[3];      /**< The state array of length 3. */
    q31_t Kp;            /**< The proportional gain. */
    q31_t Ki;            /**< The integral gain. */
    q31_t Kd;            /**< The derivative gain. */
  } arm_pid_instance_q31;

  /**
   * @brief Instance structure for the floating-point PID Control.
   */
  typedef struct
  {
    float32_t A0;          /**< The derived gain, A0 = Kp + Ki + Kd . */
    float32_t A1;          /**< The derived gain, A1 = -Kp - 2Kd. */
    float32_t A2;          /**< The derived gain, A2 = Kd . */
    float32_t state[3];    /**< The state array of length 3. */
    float32_t Kp;          /**< The proportional gain. */
    float32_t Ki;          /**< The integral gain. */
    float32_t Kd;          /**< The derivative gain. */
  } arm_pid_instance_f32;



  /**
   * @brief  Initialization function for the floating-point PID Control.
   * @param[in,out] S               points to an instance of the PID structure.
   * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
   */
  void arm_pid_init_f32(
  arm_pid_instance_f32 * S,
  int32_t resetStateFlag);


  /**
   * @brief  Reset function for the floating-point PID Control.
   * @param[in,out] S  is an instance of the floating-point PID Control structure
   */
  void arm_pid_reset_f32(
  arm_pid_instance_f32 * S);


  /**
   * @brief  Initialization function for the Q31 PID Control.
   * @param[in,out] S               points to an instance of the Q15 PID structure.
   * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
   */
  void arm_pid_init_q31(
  arm_pid_instance_q31 * S,
  int32_t resetStateFlag);


  /**
   * @brief  Reset function for the Q31 PID Control.
   * @param[in,out] S   points to an instance of the Q31 PID Control structure
   */

  void arm_pid_reset_q31(
  arm_pid_instance_q31 * S);


  /**
   * @brief  Initialization function for the Q15 PID Control.
   * @param[in,out] S               points to an instance of the Q15 PID structure.
   * @param[in]     resetStateFlag  flag to reset the state. 0 = no change in state 1 = reset the state.
   */
  void arm_pid_init_q15(
  arm_pid_instance_q15 * S,
  int32_t resetStateFlag);


  /**
   * @brief  Reset function for the Q15 PID Control.
   * @param[in,out] S  points to an instance of the q15 PID Control structure
   */
  void arm_pid_reset_q15(
  arm_pid_instance_q15 * S);


  /**
   * @brief Instance structure for the floating-point Linear Interpolate function.
   */
  typedef struct
  {
    uint32_t nValues;           /**< nValues */
    float32_t x1;               /**< x1 */
    float32_t xSpacing;         /**< xSpacing */
    float32_t *pYData;          /**< pointer to the table of Y values */
  } arm_linear_interp_instance_f32;

  /**
   * @brief Instance structure for the floating-point bilinear interpolation function.
   */
  typedef struct
  {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    float32_t *pData;   /**< points to the data table. */
  } arm_bilinear_interp_instance_f32;

   /**
   * @brief Instance structure for the Q31 bilinear interpolation function.
   */
  typedef struct
  {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    q31_t *pData;       /**< points to the data table. */
  } arm_bilinear_interp_instance_q31;

   /**
   * @brief Instance structure for the Q15 bilinear interpolation function.
   */
  typedef struct
  {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    q15_t *pData;       /**< points to the data table. */
  } arm_bilinear_interp_instance_q15;

   /**
   * @brief Instance structure for the Q15 bilinear interpolation function.
   */
  typedef struct
  {
    uint16_t numRows;   /**< number of rows in the data table. */
    uint16_t numCols;   /**< number of columns in the data table. */
    q7_t *pData;        /**< points to the data table. */
  } arm_bilinear_interp_instance_q7;


  /**
   * @brief Q7 vector multiplication.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_mult_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q15 vector multiplication.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_mult_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q31 vector multiplication.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_mult_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Floating-point vector multiplication.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_mult_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 CFFT/CIFFT function.
   */
  typedef struct
  {
    uint16_t fftLen;                 /**< length of the FFT. */
    uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    q15_t *pTwiddle;                 /**< points to the Sin twiddle factor table. */
    uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
  } arm_cfft_radix2_instance_q15;

/* Deprecated */
  arm_status arm_cfft_radix2_init_q15(
  arm_cfft_radix2_instance_q15 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

/* Deprecated */
  void arm_cfft_radix2_q15(
  const arm_cfft_radix2_instance_q15 * S,
  q15_t * pSrc);


  /**
   * @brief Instance structure for the Q15 CFFT/CIFFT function.
   */
  typedef struct
  {
    uint16_t fftLen;                 /**< length of the FFT. */
    uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    q15_t *pTwiddle;                 /**< points to the twiddle factor table. */
    uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
  } arm_cfft_radix4_instance_q15;

/* Deprecated */
  arm_status arm_cfft_radix4_init_q15(
  arm_cfft_radix4_instance_q15 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

/* Deprecated */
  void arm_cfft_radix4_q15(
  const arm_cfft_radix4_instance_q15 * S,
  q15_t * pSrc);

  /**
   * @brief Instance structure for the Radix-2 Q31 CFFT/CIFFT function.
   */
  typedef struct
  {
    uint16_t fftLen;                 /**< length of the FFT. */
    uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    q31_t *pTwiddle;                 /**< points to the Twiddle factor table. */
    uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
  } arm_cfft_radix2_instance_q31;

/* Deprecated */
  arm_status arm_cfft_radix2_init_q31(
  arm_cfft_radix2_instance_q31 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

/* Deprecated */
  void arm_cfft_radix2_q31(
  const arm_cfft_radix2_instance_q31 * S,
  q31_t * pSrc);

  /**
   * @brief Instance structure for the Q31 CFFT/CIFFT function.
   */
  typedef struct
  {
    uint16_t fftLen;                 /**< length of the FFT. */
    uint8_t ifftFlag;                /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;          /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    q31_t *pTwiddle;                 /**< points to the twiddle factor table. */
    uint16_t *pBitRevTable;          /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;       /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;           /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
  } arm_cfft_radix4_instance_q31;

/* Deprecated */
  void arm_cfft_radix4_q31(
  const arm_cfft_radix4_instance_q31 * S,
  q31_t * pSrc);

/* Deprecated */
  arm_status arm_cfft_radix4_init_q31(
  arm_cfft_radix4_instance_q31 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

  /**
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
    uint16_t fftLen;                   /**< length of the FFT. */
    uint8_t ifftFlag;                  /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;            /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    float32_t *pTwiddle;               /**< points to the Twiddle factor table. */
    uint16_t *pBitRevTable;            /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;         /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;             /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
    float32_t onebyfftLen;             /**< value of 1/fftLen. */
  } arm_cfft_radix2_instance_f32;

/* Deprecated */
  arm_status arm_cfft_radix2_init_f32(
  arm_cfft_radix2_instance_f32 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

/* Deprecated */
  void arm_cfft_radix2_f32(
  const arm_cfft_radix2_instance_f32 * S,
  float32_t * pSrc);

  /**
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
    uint16_t fftLen;                   /**< length of the FFT. */
    uint8_t ifftFlag;                  /**< flag that selects forward (ifftFlag=0) or inverse (ifftFlag=1) transform. */
    uint8_t bitReverseFlag;            /**< flag that enables (bitReverseFlag=1) or disables (bitReverseFlag=0) bit reversal of output. */
    float32_t *pTwiddle;               /**< points to the Twiddle factor table. */
    uint16_t *pBitRevTable;            /**< points to the bit reversal table. */
    uint16_t twidCoefModifier;         /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    uint16_t bitRevFactor;             /**< bit reversal modifier that supports different size FFTs with the same bit reversal table. */
    float32_t onebyfftLen;             /**< value of 1/fftLen. */
  } arm_cfft_radix4_instance_f32;

/* Deprecated */
  arm_status arm_cfft_radix4_init_f32(
  arm_cfft_radix4_instance_f32 * S,
  uint16_t fftLen,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

/* Deprecated */
  void arm_cfft_radix4_f32(
  const arm_cfft_radix4_instance_f32 * S,
  float32_t * pSrc);

  /**
   * @brief Instance structure for the fixed-point CFFT/CIFFT function.
   */
  typedef struct
  {
    uint16_t fftLen;                   /**< length of the FFT. */
    const q15_t *pTwiddle;             /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
    uint16_t bitRevLength;             /**< bit reversal table length. */
  } arm_cfft_instance_q15;

void arm_cfft_q15(
    const arm_cfft_instance_q15 * S,
    q15_t * p1,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

  /**
   * @brief Instance structure for the fixed-point CFFT/CIFFT function.
   */
  typedef struct
  {
    uint16_t fftLen;                   /**< length of the FFT. */
    const q31_t *pTwiddle;             /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
    uint16_t bitRevLength;             /**< bit reversal table length. */
  } arm_cfft_instance_q31;

void arm_cfft_q31(
    const arm_cfft_instance_q31 * S,
    q31_t * p1,
    uint8_t ifftFlag,
    uint8_t bitReverseFlag);

  /**
   * @brief Instance structure for the floating-point CFFT/CIFFT function.
   */
  typedef struct
  {
    uint16_t fftLen;                   /**< length of the FFT. */
    const float32_t *pTwiddle;         /**< points to the Twiddle factor table. */
    const uint16_t *pBitRevTable;      /**< points to the bit reversal table. */
    uint16_t bitRevLength;             /**< bit reversal table length. */
  } arm_cfft_instance_f32;

  void arm_cfft_f32(
  const arm_cfft_instance_f32 * S,
  float32_t * p1,
  uint8_t ifftFlag,
  uint8_t bitReverseFlag);

  /**
   * @brief Instance structure for the Q15 RFFT/RIFFT function.
   */
  typedef struct
  {
    uint32_t fftLenReal;                      /**< length of the real FFT. */
    uint8_t ifftFlagR;                        /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                  /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    uint32_t twidCoefRModifier;               /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    q15_t *pTwiddleAReal;                     /**< points to the real twiddle factor table. */
    q15_t *pTwiddleBReal;                     /**< points to the imag twiddle factor table. */
    const arm_cfft_instance_q15 *pCfft;       /**< points to the complex FFT instance. */
  } arm_rfft_instance_q15;

  arm_status arm_rfft_init_q15(
  arm_rfft_instance_q15 * S,
  uint32_t fftLenReal,
  uint32_t ifftFlagR,
  uint32_t bitReverseFlag);

  void arm_rfft_q15(
  const arm_rfft_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst);

  /**
   * @brief Instance structure for the Q31 RFFT/RIFFT function.
   */
  typedef struct
  {
    uint32_t fftLenReal;                        /**< length of the real FFT. */
    uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    uint32_t twidCoefRModifier;                 /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    q31_t *pTwiddleAReal;                       /**< points to the real twiddle factor table. */
    q31_t *pTwiddleBReal;                       /**< points to the imag twiddle factor table. */
    const arm_cfft_instance_q31 *pCfft;         /**< points to the complex FFT instance. */
  } arm_rfft_instance_q31;

  arm_status arm_rfft_init_q31(
  arm_rfft_instance_q31 * S,
  uint32_t fftLenReal,
  uint32_t ifftFlagR,
  uint32_t bitReverseFlag);

  void arm_rfft_q31(
  const arm_rfft_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst);

  /**
   * @brief Instance structure for the floating-point RFFT/RIFFT function.
   */
  typedef struct
  {
    uint32_t fftLenReal;                        /**< length of the real FFT. */
    uint16_t fftLenBy2;                         /**< length of the complex FFT. */
    uint8_t ifftFlagR;                          /**< flag that selects forward (ifftFlagR=0) or inverse (ifftFlagR=1) transform. */
    uint8_t bitReverseFlagR;                    /**< flag that enables (bitReverseFlagR=1) or disables (bitReverseFlagR=0) bit reversal of output. */
    uint32_t twidCoefRModifier;                     /**< twiddle coefficient modifier that supports different size FFTs with the same twiddle factor table. */
    float32_t *pTwiddleAReal;                   /**< points to the real twiddle factor table. */
    float32_t *pTwiddleBReal;                   /**< points to the imag twiddle factor table. */
    arm_cfft_radix4_instance_f32 *pCfft;        /**< points to the complex FFT instance. */
  } arm_rfft_instance_f32;

  arm_status arm_rfft_init_f32(
  arm_rfft_instance_f32 * S,
  arm_cfft_radix4_instance_f32 * S_CFFT,
  uint32_t fftLenReal,
  uint32_t ifftFlagR,
  uint32_t bitReverseFlag);

  void arm_rfft_f32(
  const arm_rfft_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst);

  /**
   * @brief Instance structure for the floating-point RFFT/RIFFT function.
   */
typedef struct
  {
    arm_cfft_instance_f32 Sint;      /**< Internal CFFT structure. */
    uint16_t fftLenRFFT;             /**< length of the real sequence */
    float32_t * pTwiddleRFFT;        /**< Twiddle factors real stage  */
  } arm_rfft_fast_instance_f32 ;

arm_status arm_rfft_fast_init_f32 (
   arm_rfft_fast_instance_f32 * S,
   uint16_t fftLen);

void arm_rfft_fast_f32(
  arm_rfft_fast_instance_f32 * S,
  float32_t * p, float32_t * pOut,
  uint8_t ifftFlag);

  /**
   * @brief Instance structure for the floating-point DCT4/IDCT4 function.
   */
  typedef struct
  {
    uint16_t N;                          /**< length of the DCT4. */
    uint16_t Nby2;                       /**< half of the length of the DCT4. */
    float32_t normalize;                 /**< normalizing factor. */
    float32_t *pTwiddle;                 /**< points to the twiddle factor table. */
    float32_t *pCosFactor;               /**< points to the cosFactor table. */
    arm_rfft_instance_f32 *pRfft;        /**< points to the real FFT instance. */
    arm_cfft_radix4_instance_f32 *pCfft; /**< points to the complex FFT instance. */
  } arm_dct4_instance_f32;


  /**
   * @brief  Initialization function for the floating-point DCT4/IDCT4.
   * @param[in,out] S          points to an instance of floating-point DCT4/IDCT4 structure.
   * @param[in]     S_RFFT     points to an instance of floating-point RFFT/RIFFT structure.
   * @param[in]     S_CFFT     points to an instance of floating-point CFFT/CIFFT structure.
   * @param[in]     N          length of the DCT4.
   * @param[in]     Nby2       half of the length of the DCT4.
   * @param[in]     normalize  normalizing factor.
   * @return      arm_status function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>fftLenReal</code> is not a supported transform length.
   */
  arm_status arm_dct4_init_f32(
  arm_dct4_instance_f32 * S,
  arm_rfft_instance_f32 * S_RFFT,
  arm_cfft_radix4_instance_f32 * S_CFFT,
  uint16_t N,
  uint16_t Nby2,
  float32_t normalize);


  /**
   * @brief Processing function for the floating-point DCT4/IDCT4.
   * @param[in]     S              points to an instance of the floating-point DCT4/IDCT4 structure.
   * @param[in]     pState         points to state buffer.
   * @param[in,out] pInlineBuffer  points to the in-place input and output buffer.
   */
  void arm_dct4_f32(
  const arm_dct4_instance_f32 * S,
  float32_t * pState,
  float32_t * pInlineBuffer);


  /**
   * @brief Instance structure for the Q31 DCT4/IDCT4 function.
   */
  typedef struct
  {
    uint16_t N;                          /**< length of the DCT4. */
    uint16_t Nby2;                       /**< half of the length of the DCT4. */
    q31_t normalize;                     /**< normalizing factor. */
    q31_t *pTwiddle;                     /**< points to the twiddle factor table. */
    q31_t *pCosFactor;                   /**< points to the cosFactor table. */
    arm_rfft_instance_q31 *pRfft;        /**< points to the real FFT instance. */
    arm_cfft_radix4_instance_q31 *pCfft; /**< points to the complex FFT instance. */
  } arm_dct4_instance_q31;


  /**
   * @brief  Initialization function for the Q31 DCT4/IDCT4.
   * @param[in,out] S          points to an instance of Q31 DCT4/IDCT4 structure.
   * @param[in]     S_RFFT     points to an instance of Q31 RFFT/RIFFT structure
   * @param[in]     S_CFFT     points to an instance of Q31 CFFT/CIFFT structure
   * @param[in]     N          length of the DCT4.
   * @param[in]     Nby2       half of the length of the DCT4.
   * @param[in]     normalize  normalizing factor.
   * @return      arm_status function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>N</code> is not a supported transform length.
   */
  arm_status arm_dct4_init_q31(
  arm_dct4_instance_q31 * S,
  arm_rfft_instance_q31 * S_RFFT,
  arm_cfft_radix4_instance_q31 * S_CFFT,
  uint16_t N,
  uint16_t Nby2,
  q31_t normalize);


  /**
   * @brief Processing function for the Q31 DCT4/IDCT4.
   * @param[in]     S              points to an instance of the Q31 DCT4 structure.
   * @param[in]     pState         points to state buffer.
   * @param[in,out] pInlineBuffer  points to the in-place input and output buffer.
   */
  void arm_dct4_q31(
  const arm_dct4_instance_q31 * S,
  q31_t * pState,
  q31_t * pInlineBuffer);


  /**
   * @brief Instance structure for the Q15 DCT4/IDCT4 function.
   */
  typedef struct
  {
    uint16_t N;                          /**< length of the DCT4. */
    uint16_t Nby2;                       /**< half of the length of the DCT4. */
    q15_t normalize;                     /**< normalizing factor. */
    q15_t *pTwiddle;                     /**< points to the twiddle factor table. */
    q15_t *pCosFactor;                   /**< points to the cosFactor table. */
    arm_rfft_instance_q15 *pRfft;        /**< points to the real FFT instance. */
    arm_cfft_radix4_instance_q15 *pCfft; /**< points to the complex FFT instance. */
  } arm_dct4_instance_q15;


  /**
   * @brief  Initialization function for the Q15 DCT4/IDCT4.
   * @param[in,out] S          points to an instance of Q15 DCT4/IDCT4 structure.
   * @param[in]     S_RFFT     points to an instance of Q15 RFFT/RIFFT structure.
   * @param[in]     S_CFFT     points to an instance of Q15 CFFT/CIFFT structure.
   * @param[in]     N          length of the DCT4.
   * @param[in]     Nby2       half of the length of the DCT4.
   * @param[in]     normalize  normalizing factor.
   * @return      arm_status function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_ARGUMENT_ERROR if <code>N</code> is not a supported transform length.
   */
  arm_status arm_dct4_init_q15(
  arm_dct4_instance_q15 * S,
  arm_rfft_instance_q15 * S_RFFT,
  arm_cfft_radix4_instance_q15 * S_CFFT,
  uint16_t N,
  uint16_t Nby2,
  q15_t normalize);


  /**
   * @brief Processing function for the Q15 DCT4/IDCT4.
   * @param[in]     S              points to an instance of the Q15 DCT4 structure.
   * @param[in]     pState         points to state buffer.
   * @param[in,out] pInlineBuffer  points to the in-place input and output buffer.
   */
  void arm_dct4_q15(
  const arm_dct4_instance_q15 * S,
  q15_t * pState,
  q15_t * pInlineBuffer);


  /**
   * @brief Floating-point vector addition.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_add_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q7 vector addition.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_add_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q15 vector addition.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_add_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q31 vector addition.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_add_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Floating-point vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q7 vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q15 vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q31 vector subtraction.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_sub_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Multiplies a floating-point vector by a scalar.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  scale      scale factor to be applied
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_scale_f32(
  float32_t * pSrc,
  float32_t scale,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Multiplies a Q7 vector by a scalar.
   * @param[in]  pSrc        points to the input vector
   * @param[in]  scaleFract  fractional portion of the scale value
   * @param[in]  shift       number of bits to shift the result by
   * @param[out] pDst        points to the output vector
   * @param[in]  blockSize   number of samples in the vector
   */
  void arm_scale_q7(
  q7_t * pSrc,
  q7_t scaleFract,
  int8_t shift,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Multiplies a Q15 vector by a scalar.
   * @param[in]  pSrc        points to the input vector
   * @param[in]  scaleFract  fractional portion of the scale value
   * @param[in]  shift       number of bits to shift the result by
   * @param[out] pDst        points to the output vector
   * @param[in]  blockSize   number of samples in the vector
   */
  void arm_scale_q15(
  q15_t * pSrc,
  q15_t scaleFract,
  int8_t shift,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Multiplies a Q31 vector by a scalar.
   * @param[in]  pSrc        points to the input vector
   * @param[in]  scaleFract  fractional portion of the scale value
   * @param[in]  shift       number of bits to shift the result by
   * @param[out] pDst        points to the output vector
   * @param[in]  blockSize   number of samples in the vector
   */
  void arm_scale_q31(
  q31_t * pSrc,
  q31_t scaleFract,
  int8_t shift,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q7 vector absolute value.
   * @param[in]  pSrc       points to the input buffer
   * @param[out] pDst       points to the output buffer
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_abs_q7(
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Floating-point vector absolute value.
   * @param[in]  pSrc       points to the input buffer
   * @param[out] pDst       points to the output buffer
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_abs_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q15 vector absolute value.
   * @param[in]  pSrc       points to the input buffer
   * @param[out] pDst       points to the output buffer
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_abs_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Q31 vector absolute value.
   * @param[in]  pSrc       points to the input buffer
   * @param[out] pDst       points to the output buffer
   * @param[in]  blockSize  number of samples in each vector
   */
  void arm_abs_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Dot product of floating-point vectors.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[in]  blockSize  number of samples in each vector
   * @param[out] result     output result returned here
   */
  void arm_dot_prod_f32(
  float32_t * pSrcA,
  float32_t * pSrcB,
  uint32_t blockSize,
  float32_t * result);


  /**
   * @brief Dot product of Q7 vectors.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[in]  blockSize  number of samples in each vector
   * @param[out] result     output result returned here
   */
  void arm_dot_prod_q7(
  q7_t * pSrcA,
  q7_t * pSrcB,
  uint32_t blockSize,
  q31_t * result);


  /**
   * @brief Dot product of Q15 vectors.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[in]  blockSize  number of samples in each vector
   * @param[out] result     output result returned here
   */
  void arm_dot_prod_q15(
  q15_t * pSrcA,
  q15_t * pSrcB,
  uint32_t blockSize,
  q63_t * result);


  /**
   * @brief Dot product of Q31 vectors.
   * @param[in]  pSrcA      points to the first input vector
   * @param[in]  pSrcB      points to the second input vector
   * @param[in]  blockSize  number of samples in each vector
   * @param[out] result     output result returned here
   */
  void arm_dot_prod_q31(
  q31_t * pSrcA,
  q31_t * pSrcB,
  uint32_t blockSize,
  q63_t * result);


  /**
   * @brief  Shifts the elements of a Q7 vector a specified number of bits.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_shift_q7(
  q7_t * pSrc,
  int8_t shiftBits,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Shifts the elements of a Q15 vector a specified number of bits.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_shift_q15(
  q15_t * pSrc,
  int8_t shiftBits,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Shifts the elements of a Q31 vector a specified number of bits.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  shiftBits  number of bits to shift.  A positive value shifts left; a negative value shifts right.
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_shift_q31(
  q31_t * pSrc,
  int8_t shiftBits,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Adds a constant offset to a floating-point vector.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  offset     is the offset to be added
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_offset_f32(
  float32_t * pSrc,
  float32_t offset,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Adds a constant offset to a Q7 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  offset     is the offset to be added
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_offset_q7(
  q7_t * pSrc,
  q7_t offset,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Adds a constant offset to a Q15 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  offset     is the offset to be added
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_offset_q15(
  q15_t * pSrc,
  q15_t offset,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Adds a constant offset to a Q31 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[in]  offset     is the offset to be added
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_offset_q31(
  q31_t * pSrc,
  q31_t offset,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Negates the elements of a floating-point vector.
   * @param[in]  pSrc       points to the input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_negate_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Negates the elements of a Q7 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_negate_q7(
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Negates the elements of a Q15 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_negate_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Negates the elements of a Q31 vector.
   * @param[in]  pSrc       points to the input vector
   * @param[out] pDst       points to the output vector
   * @param[in]  blockSize  number of samples in the vector
   */
  void arm_negate_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Copies the elements of a floating-point vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void arm_copy_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Copies the elements of a Q7 vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void arm_copy_q7(
  q7_t * pSrc,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Copies the elements of a Q15 vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void arm_copy_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Copies the elements of a Q31 vector.
   * @param[in]  pSrc       input pointer
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void arm_copy_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a floating-point vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void arm_fill_f32(
  float32_t value,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a Q7 vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void arm_fill_q7(
  q7_t value,
  q7_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a Q15 vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void arm_fill_q15(
  q15_t value,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Fills a constant value into a Q31 vector.
   * @param[in]  value      input value to be filled
   * @param[out] pDst       output pointer
   * @param[in]  blockSize  number of samples to process
   */
  void arm_fill_q31(
  q31_t value,
  q31_t * pDst,
  uint32_t blockSize);


/**
 * @brief Convolution of floating-point sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the location where the output result is written.  Length srcALen+srcBLen-1.
 */
  void arm_conv_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst);


  /**
   * @brief Convolution of Q15 sequences.
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in]  pScratch1  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer of size min(srcALen, srcBLen).
   */
  void arm_conv_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  q15_t * pScratch1,
  q15_t * pScratch2);


/**
 * @brief Convolution of Q15 sequences.
 * @param[in]  pSrcA    points to the first input sequence.
 * @param[in]  srcALen  length of the first input sequence.
 * @param[in]  pSrcB    points to the second input sequence.
 * @param[in]  srcBLen  length of the second input sequence.
 * @param[out] pDst     points to the location where the output result is written.  Length srcALen+srcBLen-1.
 */
  void arm_conv_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst);


  /**
   * @brief Convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void arm_conv_fast_q15(
          q15_t * pSrcA,
          uint32_t srcALen,
          q15_t * pSrcB,
          uint32_t srcBLen,
          q15_t * pDst);


  /**
   * @brief Convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in]  pScratch1  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer of size min(srcALen, srcBLen).
   */
  void arm_conv_fast_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  q15_t * pScratch1,
  q15_t * pScratch2);


  /**
   * @brief Convolution of Q31 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void arm_conv_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst);


  /**
   * @brief Convolution of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void arm_conv_fast_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst);


    /**
   * @brief Convolution of Q7 sequences.
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length srcALen+srcBLen-1.
   * @param[in]  pScratch1  points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).
   */
  void arm_conv_opt_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst,
  q15_t * pScratch1,
  q15_t * pScratch2);


  /**
   * @brief Convolution of Q7 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length srcALen+srcBLen-1.
   */
  void arm_conv_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst);


  /**
   * @brief Partial convolution of floating-point sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);


  /**
   * @brief Partial convolution of Q15 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @param[in]  pScratch1   points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2   points to scratch buffer of size min(srcALen, srcBLen).
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints,
  q15_t * pScratch1,
  q15_t * pScratch2);


  /**
   * @brief Partial convolution of Q15 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);


  /**
   * @brief Partial convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_fast_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);


  /**
   * @brief Partial convolution of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @param[in]  pScratch1   points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2   points to scratch buffer of size min(srcALen, srcBLen).
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_fast_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints,
  q15_t * pScratch1,
  q15_t * pScratch2);


  /**
   * @brief Partial convolution of Q31 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);


  /**
   * @brief Partial convolution of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_fast_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);


  /**
   * @brief Partial convolution of Q7 sequences
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @param[in]  pScratch1   points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2   points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_opt_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints,
  q15_t * pScratch1,
  q15_t * pScratch2);


/**
   * @brief Partial convolution of Q7 sequences.
   * @param[in]  pSrcA       points to the first input sequence.
   * @param[in]  srcALen     length of the first input sequence.
   * @param[in]  pSrcB       points to the second input sequence.
   * @param[in]  srcBLen     length of the second input sequence.
   * @param[out] pDst        points to the block of output data
   * @param[in]  firstIndex  is the first output sample to start with.
   * @param[in]  numPoints   is the number of output points to be computed.
   * @return  Returns either ARM_MATH_SUCCESS if the function completed correctly or ARM_MATH_ARGUMENT_ERROR if the requested subset is not in the range [0 srcALen+srcBLen-2].
   */
  arm_status arm_conv_partial_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst,
  uint32_t firstIndex,
  uint32_t numPoints);


  /**
   * @brief Instance structure for the Q15 FIR decimator.
   */
  typedef struct
  {
    uint8_t M;                  /**< decimation factor. */
    uint16_t numTaps;           /**< number of coefficients in the filter. */
    q15_t *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
    q15_t *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } arm_fir_decimate_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR decimator.
   */
  typedef struct
  {
    uint8_t M;                  /**< decimation factor. */
    uint16_t numTaps;           /**< number of coefficients in the filter. */
    q31_t *pCoeffs;             /**< points to the coefficient array. The array is of length numTaps.*/
    q31_t *pState;              /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } arm_fir_decimate_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR decimator.
   */
  typedef struct
  {
    uint8_t M;                  /**< decimation factor. */
    uint16_t numTaps;           /**< number of coefficients in the filter. */
    float32_t *pCoeffs;         /**< points to the coefficient array. The array is of length numTaps.*/
    float32_t *pState;          /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
  } arm_fir_decimate_instance_f32;


  /**
   * @brief Processing function for the floating-point FIR decimator.
   * @param[in]  S          points to an instance of the floating-point FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_decimate_f32(
  const arm_fir_decimate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point FIR decimator.
   * @param[in,out] S          points to an instance of the floating-point FIR decimator structure.
   * @param[in]     numTaps    number of coefficients in the filter.
   * @param[in]     M          decimation factor.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return    The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * <code>blockSize</code> is not a multiple of <code>M</code>.
   */
  arm_status arm_fir_decimate_init_f32(
  arm_fir_decimate_instance_f32 * S,
  uint16_t numTaps,
  uint8_t M,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 FIR decimator.
   * @param[in]  S          points to an instance of the Q15 FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_decimate_q15(
  const arm_fir_decimate_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 FIR decimator (fast variant) for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q15 FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_decimate_fast_q15(
  const arm_fir_decimate_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 FIR decimator.
   * @param[in,out] S          points to an instance of the Q15 FIR decimator structure.
   * @param[in]     numTaps    number of coefficients in the filter.
   * @param[in]     M          decimation factor.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return    The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * <code>blockSize</code> is not a multiple of <code>M</code>.
   */
  arm_status arm_fir_decimate_init_q15(
  arm_fir_decimate_instance_q15 * S,
  uint16_t numTaps,
  uint8_t M,
  q15_t * pCoeffs,
  q15_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 FIR decimator.
   * @param[in]  S     points to an instance of the Q31 FIR decimator structure.
   * @param[in]  pSrc  points to the block of input data.
   * @param[out] pDst  points to the block of output data
   * @param[in] blockSize number of input samples to process per call.
   */
  void arm_fir_decimate_q31(
  const arm_fir_decimate_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);

  /**
   * @brief Processing function for the Q31 FIR decimator (fast variant) for Cortex-M3 and Cortex-M4.
   * @param[in]  S          points to an instance of the Q31 FIR decimator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_decimate_fast_q31(
  arm_fir_decimate_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 FIR decimator.
   * @param[in,out] S          points to an instance of the Q31 FIR decimator structure.
   * @param[in]     numTaps    number of coefficients in the filter.
   * @param[in]     M          decimation factor.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return    The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * <code>blockSize</code> is not a multiple of <code>M</code>.
   */
  arm_status arm_fir_decimate_init_q31(
  arm_fir_decimate_instance_q31 * S,
  uint16_t numTaps,
  uint8_t M,
  q31_t * pCoeffs,
  q31_t * pState,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 FIR interpolator.
   */
  typedef struct
  {
    uint8_t L;                      /**< upsample factor. */
    uint16_t phaseLength;           /**< length of each polyphase filter component. */
    q15_t *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
    q15_t *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
  } arm_fir_interpolate_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR interpolator.
   */
  typedef struct
  {
    uint8_t L;                      /**< upsample factor. */
    uint16_t phaseLength;           /**< length of each polyphase filter component. */
    q31_t *pCoeffs;                 /**< points to the coefficient array. The array is of length L*phaseLength. */
    q31_t *pState;                  /**< points to the state variable array. The array is of length blockSize+phaseLength-1. */
  } arm_fir_interpolate_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR interpolator.
   */
  typedef struct
  {
    uint8_t L;                     /**< upsample factor. */
    uint16_t phaseLength;          /**< length of each polyphase filter component. */
    float32_t *pCoeffs;            /**< points to the coefficient array. The array is of length L*phaseLength. */
    float32_t *pState;             /**< points to the state variable array. The array is of length phaseLength+numTaps-1. */
  } arm_fir_interpolate_instance_f32;


  /**
   * @brief Processing function for the Q15 FIR interpolator.
   * @param[in]  S          points to an instance of the Q15 FIR interpolator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_interpolate_q15(
  const arm_fir_interpolate_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 FIR interpolator.
   * @param[in,out] S          points to an instance of the Q15 FIR interpolator structure.
   * @param[in]     L          upsample factor.
   * @param[in]     numTaps    number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficient buffer.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */
  arm_status arm_fir_interpolate_init_q15(
  arm_fir_interpolate_instance_q15 * S,
  uint8_t L,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 FIR interpolator.
   * @param[in]  S          points to an instance of the Q15 FIR interpolator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_interpolate_q31(
  const arm_fir_interpolate_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 FIR interpolator.
   * @param[in,out] S          points to an instance of the Q31 FIR interpolator structure.
   * @param[in]     L          upsample factor.
   * @param[in]     numTaps    number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficient buffer.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */
  arm_status arm_fir_interpolate_init_q31(
  arm_fir_interpolate_instance_q31 * S,
  uint8_t L,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point FIR interpolator.
   * @param[in]  S          points to an instance of the floating-point FIR interpolator structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of input samples to process per call.
   */
  void arm_fir_interpolate_f32(
  const arm_fir_interpolate_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point FIR interpolator.
   * @param[in,out] S          points to an instance of the floating-point FIR interpolator structure.
   * @param[in]     L          upsample factor.
   * @param[in]     numTaps    number of filter coefficients in the filter.
   * @param[in]     pCoeffs    points to the filter coefficient buffer.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     blockSize  number of input samples to process per call.
   * @return        The function returns ARM_MATH_SUCCESS if initialization is successful or ARM_MATH_LENGTH_ERROR if
   * the filter length <code>numTaps</code> is not a multiple of the interpolation factor <code>L</code>.
   */
  arm_status arm_fir_interpolate_init_f32(
  arm_fir_interpolate_instance_f32 * S,
  uint8_t L,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the high precision Q31 Biquad cascade filter.
   */
  typedef struct
  {
    uint8_t numStages;       /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    q63_t *pState;           /**< points to the array of state coefficients.  The array is of length 4*numStages. */
    q31_t *pCoeffs;          /**< points to the array of coefficients.  The array is of length 5*numStages. */
    uint8_t postShift;       /**< additional shift, in bits, applied to each output sample. */
  } arm_biquad_cas_df1_32x64_ins_q31;


  /**
   * @param[in]  S          points to an instance of the high precision Q31 Biquad cascade filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cas_df1_32x64_q31(
  const arm_biquad_cas_df1_32x64_ins_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @param[in,out] S          points to an instance of the high precision Q31 Biquad cascade filter structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     postShift  shift to be applied to the output. Varies according to the coefficients format
   */
  void arm_biquad_cas_df1_32x64_init_q31(
  arm_biquad_cas_df1_32x64_ins_q31 * S,
  uint8_t numStages,
  q31_t * pCoeffs,
  q63_t * pState,
  uint8_t postShift);


  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
    uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float32_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    float32_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_cascade_df2T_instance_f32;

  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
    uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float32_t *pState;         /**< points to the array of state coefficients.  The array is of length 4*numStages. */
    float32_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_cascade_stereo_df2T_instance_f32;

  /**
   * @brief Instance structure for the floating-point transposed direct form II Biquad cascade filter.
   */
  typedef struct
  {
    uint8_t numStages;         /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
    float64_t *pState;         /**< points to the array of state coefficients.  The array is of length 2*numStages. */
    float64_t *pCoeffs;        /**< points to the array of coefficients.  The array is of length 5*numStages. */
  } arm_biquad_cascade_df2T_instance_f64;


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df2T_f32(
  const arm_biquad_cascade_df2T_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter. 2 channels
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_stereo_df2T_f32(
  const arm_biquad_cascade_stereo_df2T_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Processing function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in]  S          points to an instance of the filter data structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_biquad_cascade_df2T_f64(
  const arm_biquad_cascade_df2T_instance_f64 * S,
  float64_t * pSrc,
  float64_t * pDst,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void arm_biquad_cascade_df2T_init_f32(
  arm_biquad_cascade_df2T_instance_f32 * S,
  uint8_t numStages,
  float32_t * pCoeffs,
  float32_t * pState);


  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void arm_biquad_cascade_stereo_df2T_init_f32(
  arm_biquad_cascade_stereo_df2T_instance_f32 * S,
  uint8_t numStages,
  float32_t * pCoeffs,
  float32_t * pState);


  /**
   * @brief  Initialization function for the floating-point transposed direct form II Biquad cascade filter.
   * @param[in,out] S          points to an instance of the filter data structure.
   * @param[in]     numStages  number of 2nd order stages in the filter.
   * @param[in]     pCoeffs    points to the filter coefficients.
   * @param[in]     pState     points to the state buffer.
   */
  void arm_biquad_cascade_df2T_init_f64(
  arm_biquad_cascade_df2T_instance_f64 * S,
  uint8_t numStages,
  float64_t * pCoeffs,
  float64_t * pState);


  /**
   * @brief Instance structure for the Q15 FIR lattice filter.
   */
  typedef struct
  {
    uint16_t numStages;                  /**< number of filter stages. */
    q15_t *pState;                       /**< points to the state variable array. The array is of length numStages. */
    q15_t *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
  } arm_fir_lattice_instance_q15;

  /**
   * @brief Instance structure for the Q31 FIR lattice filter.
   */
  typedef struct
  {
    uint16_t numStages;                  /**< number of filter stages. */
    q31_t *pState;                       /**< points to the state variable array. The array is of length numStages. */
    q31_t *pCoeffs;                      /**< points to the coefficient array. The array is of length numStages. */
  } arm_fir_lattice_instance_q31;

  /**
   * @brief Instance structure for the floating-point FIR lattice filter.
   */
  typedef struct
  {
    uint16_t numStages;                  /**< number of filter stages. */
    float32_t *pState;                   /**< points to the state variable array. The array is of length numStages. */
    float32_t *pCoeffs;                  /**< points to the coefficient array. The array is of length numStages. */
  } arm_fir_lattice_instance_f32;


  /**
   * @brief Initialization function for the Q15 FIR lattice filter.
   * @param[in] S          points to an instance of the Q15 FIR lattice structure.
   * @param[in] numStages  number of filter stages.
   * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
   * @param[in] pState     points to the state buffer.  The array is of length numStages.
   */
  void arm_fir_lattice_init_q15(
  arm_fir_lattice_instance_q15 * S,
  uint16_t numStages,
  q15_t * pCoeffs,
  q15_t * pState);


  /**
   * @brief Processing function for the Q15 FIR lattice filter.
   * @param[in]  S          points to an instance of the Q15 FIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_lattice_q15(
  const arm_fir_lattice_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Initialization function for the Q31 FIR lattice filter.
   * @param[in] S          points to an instance of the Q31 FIR lattice structure.
   * @param[in] numStages  number of filter stages.
   * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
   * @param[in] pState     points to the state buffer.   The array is of length numStages.
   */
  void arm_fir_lattice_init_q31(
  arm_fir_lattice_instance_q31 * S,
  uint16_t numStages,
  q31_t * pCoeffs,
  q31_t * pState);


  /**
   * @brief Processing function for the Q31 FIR lattice filter.
   * @param[in]  S          points to an instance of the Q31 FIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_lattice_q31(
  const arm_fir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


/**
 * @brief Initialization function for the floating-point FIR lattice filter.
 * @param[in] S          points to an instance of the floating-point FIR lattice structure.
 * @param[in] numStages  number of filter stages.
 * @param[in] pCoeffs    points to the coefficient buffer.  The array is of length numStages.
 * @param[in] pState     points to the state buffer.  The array is of length numStages.
 */
  void arm_fir_lattice_init_f32(
  arm_fir_lattice_instance_f32 * S,
  uint16_t numStages,
  float32_t * pCoeffs,
  float32_t * pState);


  /**
   * @brief Processing function for the floating-point FIR lattice filter.
   * @param[in]  S          points to an instance of the floating-point FIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_fir_lattice_f32(
  const arm_fir_lattice_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 IIR lattice filter.
   */
  typedef struct
  {
    uint16_t numStages;                  /**< number of stages in the filter. */
    q15_t *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
    q15_t *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
    q15_t *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_q15;

  /**
   * @brief Instance structure for the Q31 IIR lattice filter.
   */
  typedef struct
  {
    uint16_t numStages;                  /**< number of stages in the filter. */
    q31_t *pState;                       /**< points to the state variable array. The array is of length numStages+blockSize. */
    q31_t *pkCoeffs;                     /**< points to the reflection coefficient array. The array is of length numStages. */
    q31_t *pvCoeffs;                     /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_q31;

  /**
   * @brief Instance structure for the floating-point IIR lattice filter.
   */
  typedef struct
  {
    uint16_t numStages;                  /**< number of stages in the filter. */
    float32_t *pState;                   /**< points to the state variable array. The array is of length numStages+blockSize. */
    float32_t *pkCoeffs;                 /**< points to the reflection coefficient array. The array is of length numStages. */
    float32_t *pvCoeffs;                 /**< points to the ladder coefficient array. The array is of length numStages+1. */
  } arm_iir_lattice_instance_f32;


  /**
   * @brief Processing function for the floating-point IIR lattice filter.
   * @param[in]  S          points to an instance of the floating-point IIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_iir_lattice_f32(
  const arm_iir_lattice_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Initialization function for the floating-point IIR lattice filter.
   * @param[in] S          points to an instance of the floating-point IIR lattice structure.
   * @param[in] numStages  number of stages in the filter.
   * @param[in] pkCoeffs   points to the reflection coefficient buffer.  The array is of length numStages.
   * @param[in] pvCoeffs   points to the ladder coefficient buffer.  The array is of length numStages+1.
   * @param[in] pState     points to the state buffer.  The array is of length numStages+blockSize-1.
   * @param[in] blockSize  number of samples to process.
   */
  void arm_iir_lattice_init_f32(
  arm_iir_lattice_instance_f32 * S,
  uint16_t numStages,
  float32_t * pkCoeffs,
  float32_t * pvCoeffs,
  float32_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 IIR lattice filter.
   * @param[in]  S          points to an instance of the Q31 IIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_iir_lattice_q31(
  const arm_iir_lattice_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t blockSize);


  /**
   * @brief Initialization function for the Q31 IIR lattice filter.
   * @param[in] S          points to an instance of the Q31 IIR lattice structure.
   * @param[in] numStages  number of stages in the filter.
   * @param[in] pkCoeffs   points to the reflection coefficient buffer.  The array is of length numStages.
   * @param[in] pvCoeffs   points to the ladder coefficient buffer.  The array is of length numStages+1.
   * @param[in] pState     points to the state buffer.  The array is of length numStages+blockSize.
   * @param[in] blockSize  number of samples to process.
   */
  void arm_iir_lattice_init_q31(
  arm_iir_lattice_instance_q31 * S,
  uint16_t numStages,
  q31_t * pkCoeffs,
  q31_t * pvCoeffs,
  q31_t * pState,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 IIR lattice filter.
   * @param[in]  S          points to an instance of the Q15 IIR lattice structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[out] pDst       points to the block of output data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_iir_lattice_q15(
  const arm_iir_lattice_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t blockSize);


/**
 * @brief Initialization function for the Q15 IIR lattice filter.
 * @param[in] S          points to an instance of the fixed-point Q15 IIR lattice structure.
 * @param[in] numStages  number of stages in the filter.
 * @param[in] pkCoeffs   points to reflection coefficient buffer.  The array is of length numStages.
 * @param[in] pvCoeffs   points to ladder coefficient buffer.  The array is of length numStages+1.
 * @param[in] pState     points to state buffer.  The array is of length numStages+blockSize.
 * @param[in] blockSize  number of samples to process per call.
 */
  void arm_iir_lattice_init_q15(
  arm_iir_lattice_instance_q15 * S,
  uint16_t numStages,
  q15_t * pkCoeffs,
  q15_t * pvCoeffs,
  q15_t * pState,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the floating-point LMS filter.
   */
  typedef struct
  {
    uint16_t numTaps;    /**< number of coefficients in the filter. */
    float32_t *pState;   /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    float32_t *pCoeffs;  /**< points to the coefficient array. The array is of length numTaps. */
    float32_t mu;        /**< step size that controls filter coefficient updates. */
  } arm_lms_instance_f32;


  /**
   * @brief Processing function for floating-point LMS filter.
   * @param[in]  S          points to an instance of the floating-point LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_f32(
  const arm_lms_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pRef,
  float32_t * pOut,
  float32_t * pErr,
  uint32_t blockSize);


  /**
   * @brief Initialization function for floating-point LMS filter.
   * @param[in] S          points to an instance of the floating-point LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to the coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   */
  void arm_lms_init_f32(
  arm_lms_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  float32_t mu,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q15 LMS filter.
   */
  typedef struct
  {
    uint16_t numTaps;    /**< number of coefficients in the filter. */
    q15_t *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q15_t *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
    q15_t mu;            /**< step size that controls filter coefficient updates. */
    uint32_t postShift;  /**< bit shift applied to coefficients. */
  } arm_lms_instance_q15;


  /**
   * @brief Initialization function for the Q15 LMS filter.
   * @param[in] S          points to an instance of the Q15 LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to the coefficient buffer.
   * @param[in] pState     points to the state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void arm_lms_init_q15(
  arm_lms_instance_q15 * S,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  q15_t mu,
  uint32_t blockSize,
  uint32_t postShift);


  /**
   * @brief Processing function for Q15 LMS filter.
   * @param[in]  S          points to an instance of the Q15 LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_q15(
  const arm_lms_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pRef,
  q15_t * pOut,
  q15_t * pErr,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q31 LMS filter.
   */
  typedef struct
  {
    uint16_t numTaps;    /**< number of coefficients in the filter. */
    q31_t *pState;       /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q31_t *pCoeffs;      /**< points to the coefficient array. The array is of length numTaps. */
    q31_t mu;            /**< step size that controls filter coefficient updates. */
    uint32_t postShift;  /**< bit shift applied to coefficients. */
  } arm_lms_instance_q31;


  /**
   * @brief Processing function for Q31 LMS filter.
   * @param[in]  S          points to an instance of the Q15 LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_q31(
  const arm_lms_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pRef,
  q31_t * pOut,
  q31_t * pErr,
  uint32_t blockSize);


  /**
   * @brief Initialization function for Q31 LMS filter.
   * @param[in] S          points to an instance of the Q31 LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void arm_lms_init_q31(
  arm_lms_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  q31_t mu,
  uint32_t blockSize,
  uint32_t postShift);


  /**
   * @brief Instance structure for the floating-point normalized LMS filter.
   */
  typedef struct
  {
    uint16_t numTaps;     /**< number of coefficients in the filter. */
    float32_t *pState;    /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    float32_t *pCoeffs;   /**< points to the coefficient array. The array is of length numTaps. */
    float32_t mu;         /**< step size that control filter coefficient updates. */
    float32_t energy;     /**< saves previous frame energy. */
    float32_t x0;         /**< saves previous input sample. */
  } arm_lms_norm_instance_f32;


  /**
   * @brief Processing function for floating-point normalized LMS filter.
   * @param[in]  S          points to an instance of the floating-point normalized LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_norm_f32(
  arm_lms_norm_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pRef,
  float32_t * pOut,
  float32_t * pErr,
  uint32_t blockSize);


  /**
   * @brief Initialization function for floating-point normalized LMS filter.
   * @param[in] S          points to an instance of the floating-point LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   */
  void arm_lms_norm_init_f32(
  arm_lms_norm_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  float32_t mu,
  uint32_t blockSize);


  /**
   * @brief Instance structure for the Q31 normalized LMS filter.
   */
  typedef struct
  {
    uint16_t numTaps;     /**< number of coefficients in the filter. */
    q31_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q31_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
    q31_t mu;             /**< step size that controls filter coefficient updates. */
    uint8_t postShift;    /**< bit shift applied to coefficients. */
    q31_t *recipTable;    /**< points to the reciprocal initial value table. */
    q31_t energy;         /**< saves previous frame energy. */
    q31_t x0;             /**< saves previous input sample. */
  } arm_lms_norm_instance_q31;


  /**
   * @brief Processing function for Q31 normalized LMS filter.
   * @param[in]  S          points to an instance of the Q31 normalized LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_norm_q31(
  arm_lms_norm_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pRef,
  q31_t * pOut,
  q31_t * pErr,
  uint32_t blockSize);


  /**
   * @brief Initialization function for Q31 normalized LMS filter.
   * @param[in] S          points to an instance of the Q31 normalized LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void arm_lms_norm_init_q31(
  arm_lms_norm_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  q31_t mu,
  uint32_t blockSize,
  uint8_t postShift);


  /**
   * @brief Instance structure for the Q15 normalized LMS filter.
   */
  typedef struct
  {
    uint16_t numTaps;     /**< Number of coefficients in the filter. */
    q15_t *pState;        /**< points to the state variable array. The array is of length numTaps+blockSize-1. */
    q15_t *pCoeffs;       /**< points to the coefficient array. The array is of length numTaps. */
    q15_t mu;             /**< step size that controls filter coefficient updates. */
    uint8_t postShift;    /**< bit shift applied to coefficients. */
    q15_t *recipTable;    /**< Points to the reciprocal initial value table. */
    q15_t energy;         /**< saves previous frame energy. */
    q15_t x0;             /**< saves previous input sample. */
  } arm_lms_norm_instance_q15;


  /**
   * @brief Processing function for Q15 normalized LMS filter.
   * @param[in]  S          points to an instance of the Q15 normalized LMS filter structure.
   * @param[in]  pSrc       points to the block of input data.
   * @param[in]  pRef       points to the block of reference data.
   * @param[out] pOut       points to the block of output data.
   * @param[out] pErr       points to the block of error data.
   * @param[in]  blockSize  number of samples to process.
   */
  void arm_lms_norm_q15(
  arm_lms_norm_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pRef,
  q15_t * pOut,
  q15_t * pErr,
  uint32_t blockSize);


  /**
   * @brief Initialization function for Q15 normalized LMS filter.
   * @param[in] S          points to an instance of the Q15 normalized LMS filter structure.
   * @param[in] numTaps    number of filter coefficients.
   * @param[in] pCoeffs    points to coefficient buffer.
   * @param[in] pState     points to state buffer.
   * @param[in] mu         step size that controls filter coefficient updates.
   * @param[in] blockSize  number of samples to process.
   * @param[in] postShift  bit shift applied to coefficients.
   */
  void arm_lms_norm_init_q15(
  arm_lms_norm_instance_q15 * S,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  q15_t mu,
  uint32_t blockSize,
  uint8_t postShift);


  /**
   * @brief Correlation of floating-point sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void arm_correlate_f32(
  float32_t * pSrcA,
  uint32_t srcALen,
  float32_t * pSrcB,
  uint32_t srcBLen,
  float32_t * pDst);


   /**
   * @brief Correlation of Q15 sequences
   * @param[in]  pSrcA     points to the first input sequence.
   * @param[in]  srcALen   length of the first input sequence.
   * @param[in]  pSrcB     points to the second input sequence.
   * @param[in]  srcBLen   length of the second input sequence.
   * @param[out] pDst      points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   * @param[in]  pScratch  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   */
  void arm_correlate_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  q15_t * pScratch);


  /**
   * @brief Correlation of Q15 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */

  void arm_correlate_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst);


  /**
   * @brief Correlation of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */

  void arm_correlate_fast_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst);


  /**
   * @brief Correlation of Q15 sequences (fast version) for Cortex-M3 and Cortex-M4.
   * @param[in]  pSrcA     points to the first input sequence.
   * @param[in]  srcALen   length of the first input sequence.
   * @param[in]  pSrcB     points to the second input sequence.
   * @param[in]  srcBLen   length of the second input sequence.
   * @param[out] pDst      points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   * @param[in]  pScratch  points to scratch buffer of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   */
  void arm_correlate_fast_opt_q15(
  q15_t * pSrcA,
  uint32_t srcALen,
  q15_t * pSrcB,
  uint32_t srcBLen,
  q15_t * pDst,
  q15_t * pScratch);


  /**
   * @brief Correlation of Q31 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void arm_correlate_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst);


  /**
   * @brief Correlation of Q31 sequences (fast version) for Cortex-M3 and Cortex-M4
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void arm_correlate_fast_q31(
  q31_t * pSrcA,
  uint32_t srcALen,
  q31_t * pSrcB,
  uint32_t srcBLen,
  q31_t * pDst);


 /**
   * @brief Correlation of Q7 sequences.
   * @param[in]  pSrcA      points to the first input sequence.
   * @param[in]  srcALen    length of the first input sequence.
   * @param[in]  pSrcB      points to the second input sequence.
   * @param[in]  srcBLen    length of the second input sequence.
   * @param[out] pDst       points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   * @param[in]  pScratch1  points to scratch buffer(of type q15_t) of size max(srcALen, srcBLen) + 2*min(srcALen, srcBLen) - 2.
   * @param[in]  pScratch2  points to scratch buffer (of type q15_t) of size min(srcALen, srcBLen).
   */
  void arm_correlate_opt_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst,
  q15_t * pScratch1,
  q15_t * pScratch2);


  /**
   * @brief Correlation of Q7 sequences.
   * @param[in]  pSrcA    points to the first input sequence.
   * @param[in]  srcALen  length of the first input sequence.
   * @param[in]  pSrcB    points to the second input sequence.
   * @param[in]  srcBLen  length of the second input sequence.
   * @param[out] pDst     points to the block of output data  Length 2 * max(srcALen, srcBLen) - 1.
   */
  void arm_correlate_q7(
  q7_t * pSrcA,
  uint32_t srcALen,
  q7_t * pSrcB,
  uint32_t srcBLen,
  q7_t * pDst);


  /**
   * @brief Instance structure for the floating-point sparse FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    float32_t *pState;            /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    float32_t *pCoeffs;           /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_f32;

  /**
   * @brief Instance structure for the Q31 sparse FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    q31_t *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    q31_t *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q31;

  /**
   * @brief Instance structure for the Q15 sparse FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    q15_t *pState;                /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    q15_t *pCoeffs;               /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q15;

  /**
   * @brief Instance structure for the Q7 sparse FIR filter.
   */
  typedef struct
  {
    uint16_t numTaps;             /**< number of coefficients in the filter. */
    uint16_t stateIndex;          /**< state buffer index.  Points to the oldest sample in the state buffer. */
    q7_t *pState;                 /**< points to the state buffer array. The array is of length maxDelay+blockSize-1. */
    q7_t *pCoeffs;                /**< points to the coefficient array. The array is of length numTaps.*/
    uint16_t maxDelay;            /**< maximum offset specified by the pTapDelay array. */
    int32_t *pTapDelay;           /**< points to the array of delay values.  The array is of length numTaps. */
  } arm_fir_sparse_instance_q7;


  /**
   * @brief Processing function for the floating-point sparse FIR filter.
   * @param[in]  S           points to an instance of the floating-point sparse FIR structure.
   * @param[in]  pSrc        points to the block of input data.
   * @param[out] pDst        points to the block of output data
   * @param[in]  pScratchIn  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize   number of input samples to process per call.
   */
  void arm_fir_sparse_f32(
  arm_fir_sparse_instance_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  float32_t * pScratchIn,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the floating-point sparse FIR filter.
   * @param[in,out] S          points to an instance of the floating-point sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void arm_fir_sparse_init_f32(
  arm_fir_sparse_instance_f32 * S,
  uint16_t numTaps,
  float32_t * pCoeffs,
  float32_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q31 sparse FIR filter.
   * @param[in]  S           points to an instance of the Q31 sparse FIR structure.
   * @param[in]  pSrc        points to the block of input data.
   * @param[out] pDst        points to the block of output data
   * @param[in]  pScratchIn  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize   number of input samples to process per call.
   */
  void arm_fir_sparse_q31(
  arm_fir_sparse_instance_q31 * S,
  q31_t * pSrc,
  q31_t * pDst,
  q31_t * pScratchIn,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q31 sparse FIR filter.
   * @param[in,out] S          points to an instance of the Q31 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void arm_fir_sparse_init_q31(
  arm_fir_sparse_instance_q31 * S,
  uint16_t numTaps,
  q31_t * pCoeffs,
  q31_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q15 sparse FIR filter.
   * @param[in]  S            points to an instance of the Q15 sparse FIR structure.
   * @param[in]  pSrc         points to the block of input data.
   * @param[out] pDst         points to the block of output data
   * @param[in]  pScratchIn   points to a temporary buffer of size blockSize.
   * @param[in]  pScratchOut  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize    number of input samples to process per call.
   */
  void arm_fir_sparse_q15(
  arm_fir_sparse_instance_q15 * S,
  q15_t * pSrc,
  q15_t * pDst,
  q15_t * pScratchIn,
  q31_t * pScratchOut,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q15 sparse FIR filter.
   * @param[in,out] S          points to an instance of the Q15 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void arm_fir_sparse_init_q15(
  arm_fir_sparse_instance_q15 * S,
  uint16_t numTaps,
  q15_t * pCoeffs,
  q15_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);


  /**
   * @brief Processing function for the Q7 sparse FIR filter.
   * @param[in]  S            points to an instance of the Q7 sparse FIR structure.
   * @param[in]  pSrc         points to the block of input data.
   * @param[out] pDst         points to the block of output data
   * @param[in]  pScratchIn   points to a temporary buffer of size blockSize.
   * @param[in]  pScratchOut  points to a temporary buffer of size blockSize.
   * @param[in]  blockSize    number of input samples to process per call.
   */
  void arm_fir_sparse_q7(
  arm_fir_sparse_instance_q7 * S,
  q7_t * pSrc,
  q7_t * pDst,
  q7_t * pScratchIn,
  q31_t * pScratchOut,
  uint32_t blockSize);


  /**
   * @brief  Initialization function for the Q7 sparse FIR filter.
   * @param[in,out] S          points to an instance of the Q7 sparse FIR structure.
   * @param[in]     numTaps    number of nonzero coefficients in the filter.
   * @param[in]     pCoeffs    points to the array of filter coefficients.
   * @param[in]     pState     points to the state buffer.
   * @param[in]     pTapDelay  points to the array of offset times.
   * @param[in]     maxDelay   maximum offset time supported.
   * @param[in]     blockSize  number of samples that will be processed per block.
   */
  void arm_fir_sparse_init_q7(
  arm_fir_sparse_instance_q7 * S,
  uint16_t numTaps,
  q7_t * pCoeffs,
  q7_t * pState,
  int32_t * pTapDelay,
  uint16_t maxDelay,
  uint32_t blockSize);


  /**
   * @brief  Floating-point sin_cos function.
   * @param[in]  theta   input value in degrees
   * @param[out] pSinVal  points to the processed sine output.
   * @param[out] pCosVal  points to the processed cos output.
   */
  void arm_sin_cos_f32(
  float32_t theta,
  float32_t * pSinVal,
  float32_t * pCosVal);


  /**
   * @brief  Q31 sin_cos function.
   * @param[in]  theta    scaled input value in degrees
   * @param[out] pSinVal  points to the processed sine output.
   * @param[out] pCosVal  points to the processed cosine output.
   */
  void arm_sin_cos_q31(
  q31_t theta,
  q31_t * pSinVal,
  q31_t * pCosVal);


  /**
   * @brief  Floating-point complex conjugate.
   * @param[in]  pSrc        points to the input vector
   * @param[out] pDst        points to the output vector
   * @param[in]  numSamples  number of complex samples in each vector
   */
  void arm_cmplx_conj_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples);

  /**
   * @brief  Q31 complex conjugate.
   * @param[in]  pSrc        points to the input vector
   * @param[out] pDst        points to the output vector
   * @param[in]  numSamples  number of complex samples in each vector
   */
  void arm_cmplx_conj_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples);


  /**
   * @brief  Q15 complex conjugate.
   * @param[in]  pSrc        points to the input vector
   * @param[out] pDst        points to the output vector
   * @param[in]  numSamples  number of complex samples in each vector
   */
  void arm_cmplx_conj_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t numSamples);


  /**
   * @brief  Floating-point complex magnitude squared
   * @param[in]  pSrc        points to the complex input vector
   * @param[out] pDst        points to the real output vector
   * @param[in]  numSamples  number of complex samples in the input vector
   */
  void arm_cmplx_mag_squared_f32(
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t numSamples);


  /**
   * @brief  Q31 complex magnitude squared
   * @param[in]  pSrc        points to the complex input vector
   * @param[out] pDst        points to the real output vector
   * @param[in]  numSamples  number of complex samples in the input vector
   */
  void arm_cmplx_mag_squared_q31(
  q31_t * pSrc,
  q31_t * pDst,
  uint32_t numSamples);


  /**
   * @brief  Q15 complex magnitude squared
   * @param[in]  pSrc        points to the complex input vector
   * @param[out] pDst        points to the real output vector
   * @param[in]  numSamples  number of complex samples in the input vector
   */
  void arm_cmplx_mag_squared_q15(
  q15_t * pSrc,
  q15_t * pDst,
  uint32_t numSamples);


 /**
   * @ingroup groupController
   */

  /**
   * @defgroup PID PID Motor Control
   *
   * A Proportional Integral Derivative (PID) controller is a generic feedback control
   * loop mechanism widely used in industrial control systems.
   * A PID controller is the most commonly used type of feedback controller.
   *
   * This set of functions implements (PID) controllers
   * for Q15, Q31, and floating-point data types.  The functions operate on a single sample
   * of data and each call to the function returns a single processed value.
   * <code>S</code> points to an instance of the PID control data structure.  <code>in</code>
   * is the input sample value. The functions return the output value.
   *
   * \par Algorithm:
   * <pre>
   *    y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]
   *    A0 = Kp + Ki + Kd
   *    A1 = (-Kp ) - (2 * Kd )
   *    A2 = Kd  </pre>
   *
   * \par
   * where \c Kp is proportional constant, \c Ki is Integral constant and \c Kd is Derivative constant
   *
   * \par
   * \image html PID.gif "Proportional Integral Derivative Controller"
   *
   * \par
   * The PID controller calculates an "error" value as the difference between
   * the measured output and the reference input.
   * The controller attempts to minimize the error by adjusting the process control inputs.
   * The proportional value determines the reaction to the current error,
   * the integral value determines the reaction based on the sum of recent errors,
   * and the derivative value determines the reaction based on the rate at which the error has been changing.
   *
   * \par Instance Structure
   * The Gains A0, A1, A2 and state variables for a PID controller are stored together in an instance data structure.
   * A separate instance structure must be defined for each PID Controller.
   * There are separate instance structure declarations for each of the 3 supported data types.
   *
   * \par Reset Functions
   * There is also an associated reset function for each data type which clears the state array.
   *
   * \par Initialization Functions
   * There is also an associated initialization function for each data type.
   * The initialization function performs the following operations:
   * - Initializes the Gains A0, A1, A2 from Kp,Ki, Kd gains.
   * - Zeros out the values in the state buffer.
   *
   * \par
   * Instance structure cannot be placed into a const data section and it is recommended to use the initialization function.
   *
   * \par Fixed-Point Behavior
   * Care must be taken when using the fixed-point versions of the PID Controller functions.
   * In particular, the overflow and saturation behavior of the accumulator used in each function must be considered.
   * Refer to the function specific documentation below for usage guidelines.
   */

  /**
   * @addtogroup PID
   * @{
   */

  /**
   * @brief  Process function for the floating-point PID Control.
   * @param[in,out] S   is an instance of the floating-point PID Control structure
   * @param[in]     in  input sample to process
   * @return out processed output sample.
   */
  CMSIS_INLINE __STATIC_INLINE float32_t arm_pid_f32(
  arm_pid_instance_f32 * S,
  float32_t in)
  {
    float32_t out;

    /* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
      (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);

  }

  /**
   * @brief  Process function for the Q31 PID Control.
   * @param[in,out] S  points to an instance of the Q31 PID Control structure
   * @param[in]     in  input sample to process
   * @return out processed output sample.
   *
   * <b>Scaling and Overflow Behavior:</b>
   * \par
   * The function is implemented using an internal 64-bit accumulator.
   * The accumulator has a 2.62 format and maintains full precision of the intermediate multiplication results but provides only a single guard bit.
   * Thus, if the accumulator result overflows it wraps around rather than clip.
   * In order to avoid overflows completely the input signal must be scaled down by 2 bits as there are four additions.
   * After all multiply-accumulates are performed, the 2.62 accumulator is truncated to 1.32 format and then saturated to 1.31 format.
   */
  CMSIS_INLINE __STATIC_INLINE q31_t arm_pid_q31(
  arm_pid_instance_q31 * S,
  q31_t in)
  {
    q63_t acc;
    q31_t out;

    /* acc = A0 * x[n]  */
    acc = (q63_t) S->A0 * in;

    /* acc += A1 * x[n-1] */
    acc += (q63_t) S->A1 * S->state[0];

    /* acc += A2 * x[n-2]  */
    acc += (q63_t) S->A2 * S->state[1];

    /* convert output to 1.31 format to add y[n-1] */
    out = (q31_t) (acc >> 31U);

    /* out += y[n-1] */
    out += S->state[2];

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);
  }

  CMSIS_INLINE __STATIC_INLINE float32_t arm_linear_interp_f32(
      arm_linear_interp_instance_f32* S,
      float32_t x)
  {
      float32_t y;
      float32_t x0, x1;                            /* Nearest input values */
      float32_t y0, y1;                            /* Nearest output values */
      float32_t xSpacing = S->xSpacing;            /* spacing between input values */
      int32_t i;                                   /* Index variable */
      float32_t* pYData = S->pYData;               /* pointer to output table */

      /* Calculation of index */
      i = (int32_t)((x - S->x1) / xSpacing);

      if (i < 0)
      {
          /* Iniatilize output for below specified range as least output value of table */
          y = pYData[0];
      }
      else if ((uint32_t)i >= S->nValues)
      {
          /* Iniatilize output for above specified range as last output value of table */
          y = pYData[S->nValues - 1];
      }
      else
      {
          /* Calculation of nearest input values */
          x0 = S->x1 + i * xSpacing;
          x1 = S->x1 + (i + 1) * xSpacing;

          /* Read of nearest output values */
          y0 = pYData[i];
          y1 = pYData[i + 1];

          /* Calculation of output */
          y = y0 + (x - x0) * ((y1 - y0) / (x1 - x0));

      }

      /* returns output value */
      return (y);
  }


#ifdef   __cplusplus
}
#endif

/* Compiler specific diagnostic adjustment */
#if   defined ( __CC_ARM )

#elif defined ( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )

#elif defined ( __GNUC__ )
#pragma GCC diagnostic pop

#elif defined ( __ICCARM__ )

#elif defined ( __TI_ARM__ )

#elif defined ( __CSMC__ )

#elif defined ( __TASKING__ )

#else
  #error Unknown compiler
#endif

#endif /* _ARM_MATH_H */

/**
 *
 * End of file.
 */
