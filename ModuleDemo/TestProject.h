/**
 * @copyright Copyright @ 
 * All Rights Reserved.
 *
 * This Copyright should be changed by diffecent project
 */
/**
 * @file TestProject.h
 * @brief Declaration file of class TestProject.(文件描述)
 * @author iauto
 * @version 1.0
 */

#ifndef CXX_TESTPROJECT_H
#define CXX_TESTPROJECT_H

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

/*---------------------------------------------------------------------------*/
// Include files

#include "working/TpWorking.h"

/*---------------------------------------------------------------------------*/
// Namesapce
TESTPROJECT_NAMESPACE_BEGINE

/*---------------------------------------------------------------------------*/
// Value define

/*---------------------------------------------------------------------------*/
// Class define

/**
 * @class TestProject
 *
 * @brief class description
 */
class TestProject
{
public:

    /**
     * @brief   Constructor
     */
    TestProject();

    /**
     * @brief   Destructor
     */
    virtual ~TestProject();

    /**
     * @brief   描述
     * @param   [in/out/in,out] 变量名
     * @return  返回值作用
     * @retval  <返回值类型> {返回值范围(可无)}
     * @see     可选, 如果函数与其他函数有关, 可以关联起来
     */
    void test(void);

private:

    // members
    TpWorking       m_cWorking;

private:

    // Disable copy constructor and operator=
    TestProject(TestProject&);
    TestProject& operator=(TestProject&);
};

/*---------------------------------------------------------------------------*/
// Namesapce
}

/*---------------------------------------------------------------------------*/
#endif  // CXX_TESTPROJECT_H
/* EOF */
