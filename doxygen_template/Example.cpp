/**
 * @copyright Copyright @ 2014 - 2020 guoxianing
 * All Rights Reserved.
 *
 * @copyright Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * guoxianing
 *
 * @copyright Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
 * @file Example.cpp
 * @brief Implement file of class Example.(文件描述)
 * @author iauto
 * @version 1.0
 */

// win32 project need add this
#include "stdafx.h"

/*---------------------------------------------------------------------------*/
// Include files

#include "XXX.h"

/*---------------------------------------------------------------------------*/
// Namesapce
namespace nutshell
{

/*---------------------------------------------------------------------------*/
// Value define

/*---------------------------------------------------------------------------*/
// Constructor
Example::Example()
{

}

/*---------------------------------------------------------------------------*/
// Destructor
Example::~Example()
{

}

/*---------------------------------------------------------------------------*/
// 描述
Example::test(VOID)
{

}

/*---------------------------------------------------------------------------*/
// Get now speed
INT Example::getSpeed(VOID)
{
    return 0;
}

/*---------------------------------------------------------------------------*/
// Get event radius
BOOL Example::getEventRadius(NXV2XAPI_RSU_INFO_KIND_E eKind, uint32_t idx, FLOST& fRadius)
{
    return FALSE;
}

/*---------------------------------------------------------------------------*/
// Get real time event count in RSI
uint32_t Example::getEventCnt(NXV2XAPI_RSU_INFO_KIND_E eKind)
{
    return 0;
}

/*---------------------------------------------------------------------------*/
// Cvt Scenario To proto
VOID Example::OutputKeep(NXV2XAppContext& cNXV2XAppContext, v2x::application::V2XInfoUpdate& cMsg, V2X_Traffic_Information& cInformation)
{

}

/*---------------------------------------------------------------------------*/
// Namesapce
}

/*---------------------------------------------------------------------------*/
/* EOF */
