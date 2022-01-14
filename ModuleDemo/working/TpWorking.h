/**
 * @copyright Copyright @ 
 * All Rights Reserved.
 *
 * This Copyright should be changed by diffecent project
 */
/**
 * @file TpWorking.h
 * @brief Declaration file of class TpWorking.(文件描述)
 * @author iauto
 * @version 1.0
 */

#ifndef CXX_TPWORKING_H
#define CXX_TPWORKING_H

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
 * @class TpWorking
 *
 * @brief class description
 */
class TpWorking
{
public:

    /**
     * @brief   Constructor
     */
    TpWorking();

    /**
     * @brief   Destructor
     */
    virtual ~TpWorking();

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
    // TODO:

private:

    // Disable copy constructor and operator=
    TpWorking(TpWorking&);
    TpWorking& operator=(TpWorking&);
};

/*---------------------------------------------------------------------------*/
TESTPROJECT_NAMESPACE_END

/*---------------------------------------------------------------------------*/
#endif  // CXX_TPWORKING_H
/* EOF */
