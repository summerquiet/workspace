/**
 * @copyright Copyright @ 
 * All Rights Reserved.
 *
 * This Copyright should be changed by diffecent project
 */
/**
 * @file TestProjectIF.cpp
 * @brief Implement file of class TestProjectIF.(文件描述)
 * @author iauto
 * @version 1.0
 */

#include "stdafx.h"

/*---------------------------------------------------------------------------*/
// Include files

#include "include/TestProjectIF.h"
#include "TestProject.h"

/*---------------------------------------------------------------------------*/
// Namesapce
TESTPROJECT_NAMESPACE_BEGINE

/*---------------------------------------------------------------------------*/
// Value define

TestProjectIF*   TestProjectIF::s_pcInstance = nullptr;

/*---------------------------------------------------------------------------*/
// 描述
void TestProjectIF::create(void)
{
    s_pcInstance = new TestProjectIF();
}

/*---------------------------------------------------------------------------*/
// 描述
TestProjectIF* TestProjectIF::getInstance(void)
{
    return s_pcInstance;
}

/*---------------------------------------------------------------------------*/
// description
void TestProjectIF::destory(void)
{
    delete s_pcInstance;
    s_pcInstance = nullptr;
}

/*---------------------------------------------------------------------------*/
// 描述
void TestProjectIF::test(void)
{

}

/*---------------------------------------------------------------------------*/
// Constructor
TestProjectIF::TestProjectIF()
: m_pcImp(nullptr)
{
    m_pcImp = new TestProject();
}

/*---------------------------------------------------------------------------*/
// Destructor
TestProjectIF::~TestProjectIF()
{
    delete m_pcImp;
    m_pcImp = nullptr;
}

/*---------------------------------------------------------------------------*/
TESTPROJECT_NAMESPACE_END

/*---------------------------------------------------------------------------*/
/* EOF */
