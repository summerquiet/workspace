/**
 * @copyright Copyright @ 2014 - 2020 guoxianing.
 * All Rights Reserved.
 *
 * @copyright Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * guoxianing.
 *
 * @copyright Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
 * @file Example.h
 * @brief Declaration file of class Example.(文件描述)
 * @author iauto
 * @version 1.0
 */

#ifndef EXAMPLE_H
#define EXAMPLE_H

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

/*---------------------------------------------------------------------------*/
// Include files

#include "XXX.h"

/*---------------------------------------------------------------------------*/
// Namesapce
namespace nutshell
{

/*---------------------------------------------------------------------------*/
// Value define

static const int TEST_CONST_VALUE = 1;      ///< this is a test const define value

/*---------------------------------------------------------------------------*/
// Class define

/**
 * @class Example
 *
 * @brief class description
 */
class Example
{
public:

    /**
     * @brief   Constructor
     */
    Example();

    /**
     * @brief   Destructor
     */
    virtual ~Example();

    /**
     * @brief   描述
     * @param   [in/out/in,out] 变量名
     * @return  返回值作用
     * @retval  <返回值类型> {返回值范围(可无)}
     * @see     可选, 如果函数与其他函数有关, 可以关联起来
     */
    VOID test(VOID);

    /**
     * @brief   Get now speed
     * @param   none
     * @return  Speed [m/s] 
     * @retval  <INT>
     */
    INT getSpeed(VOID);

    /**
     * @brief   Get event radius
     * @param   [in]    eKind      :enum value to choose event or sign
     * @param   [in]    idx        :index value to choose a event or sign
     * @param   [out]   fRadius    :radius of event effect [m] {0~6553.5}
     * @return  true : get event radius success
     * @retval  <BOOL>
     * @see     get idx count from NXV2XApiDataRsiOrig::getEventCnt()
     */
    BOOL getEventRadius(NXV2XAPI_RSU_INFO_KIND_E eKind, uint32_t idx, FLOST& fRadius);

    /**
     * @brief   Get real time event count in RSI
     * @param   [in]    eKind     :enum value to choose event or sign
     * @return  number of event or sign
     * @retval  <uint32_t>
     */
    uint32_t getEventCnt(NXV2XAPI_RSU_INFO_KIND_E eKind);

private:

    /**
     * @brief   Cvt Scenario To proto
     * @param   [in]     cNXV2XAppContext
     * @param   [in/out] cMsg
     * @param   [in/out] cInformation
     * @return  none
     */
    VOID OutputKeep(NXV2XAppContext& cNXV2XAppContext, v2x::application::V2XInfoUpdate& cMsg, V2X_Traffic_Information& cInformation);
    
private:

    // members
    ExampleOrig    m_cBsmOrig;          ///< use to do what
    ExampleRet     m_cBsmRet;           ///< use to do what

private:

    // Disable copy constructor and operator=
    Example(Example&);
    Example& operator=(Example&);
};

/*---------------------------------------------------------------------------*/
// Namesapce
}

/*---------------------------------------------------------------------------*/
#endif  // EXAMPLE_H
/* EOF */
