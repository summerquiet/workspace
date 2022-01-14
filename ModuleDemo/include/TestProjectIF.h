/**
 * @copyright Copyright @ 
 * All Rights Reserved.
 *
 * This Copyright should be changed by diffecent project
 */
/**
 * @file TestProjectIF.h
 * @brief Declaration file of class TestProjectIF.(文件描述)
 * @author iauto
 * @version 1.0
 */

#ifndef CXX_TESTPROJECTIF_H
#define CXX_TESTPROJECTIF_H

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

/*---------------------------------------------------------------------------*/
// Include files

#include "TestProjectPublicDef.h"

/*---------------------------------------------------------------------------*/
// Namesapce
TESTPROJECT_NAMESPACE_BEGINE

/*---------------------------------------------------------------------------*/
// Value define

/*---------------------------------------------------------------------------*/
// Class define

class TestProject;

/**
 * @class TestProjectIF
 *
 * @brief class description
 */
class TestProjectIF
{
public:

    /**
     * @brief   描述
     * @param   none
     * @return  none
     */
    static void create(void);

    /**
     * @brief   描述
     * @param   none
     * @return  TestProjectIF*
     */
    static TestProjectIF* getInstance(void);

    /**
     * @brief   description
     * @param parameter-name description
     * @return description of the return value
     */
    static void destory(void);

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
    static TestProjectIF*   s_pcInstance;       ///< use to do what

    TestProject*            m_pcImp;            ///< use to do what

private:

    /**
     * @brief   Constructor
     */
    TestProjectIF();

    /**
     * @brief   Destructor
     */
    virtual ~TestProjectIF();

    // Disable copy constructor and operator=
    TestProjectIF(TestProjectIF&);
    TestProjectIF& operator=(TestProjectIF&);
};

/*---------------------------------------------------------------------------*/
// Namesapce
}

/*---------------------------------------------------------------------------*/
#endif  // CXX_TESTPROJECTIF_H
/* EOF */
