/**
 * @copyright Copyright @ 
 * All Rights Reserved.
 *
 * This Copyright should be changed by diffecent project
 */
/**
 * @file TestProject.cpp
 * @brief Implement file of class TestProject.(文件描述)
 * @author iauto
 * @version 1.0
 */

#include "stdafx.h"

/*---------------------------------------------------------------------------*/
// Include files

#include "TestProject.h"
#include "working/TpWorking.h"
#include "utility/TpUtility.h"

/*---------------------------------------------------------------------------*/
// Namesapce
TESTPROJECT_NAMESPACE_BEGINE

/*---------------------------------------------------------------------------*/
// Value define

/*---------------------------------------------------------------------------*/
// Constructor
TestProject::TestProject()
: m_cWorking()
{

}

/*---------------------------------------------------------------------------*/
// Destructor
TestProject::~TestProject()
{

}

/*---------------------------------------------------------------------------*/
// 描述
void TestProject::test(void)
{
    // Working
    m_cWorking.test();

    // Utility
    TpUtility::test();
}

/*---------------------------------------------------------------------------*/
TESTPROJECT_NAMESPACE_END

/*---------------------------------------------------------------------------*/
/* EOF */
