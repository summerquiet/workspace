/**
 * @copyright Copyright @ 
 * All Rights Reserved.
 *
 * This Copyright should be changed by diffecent project
 */
/**
 * @file TpUtility.h
 * @brief Declaration file of class TpUtility.(文件描述)
 * @author iauto
 * @version 1.0
 */

#ifndef CXX_TPUTILITY_H
#define CXX_TPUTILITY_H

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

/*---------------------------------------------------------------------------*/
// Include files

/*---------------------------------------------------------------------------*/
// Namesapce
TESTPROJECT_NAMESPACE_BEGINE

/*---------------------------------------------------------------------------*/
// Value define

/*---------------------------------------------------------------------------*/
// Class define

/**
 * @class TpUtility
 *
 * @brief class description
 */
class TpUtility
{
public:

    /**
     * @brief   描述
     * @param   [in/out/in,out] 变量名
     * @return  返回值作用
     * @retval  <返回值类型> {返回值范围(可无)}
     * @see     可选, 如果函数与其他函数有关, 可以关联起来
     */
    static void test(void);

private:

    /**
     * @brief   Constructor
     */
    TpUtility();

    /**
     * @brief   Destructor
     */
    virtual ~TpUtility();

    // Disable copy constructor and operator=
    TpUtility(TpUtility&);
    TpUtility& operator=(TpUtility&);
};

/*---------------------------------------------------------------------------*/
TESTPROJECT_NAMESPACE_END

/*---------------------------------------------------------------------------*/
#endif  // CXX_TPUTILITY_H
/* EOF */
