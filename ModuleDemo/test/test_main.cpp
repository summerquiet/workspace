/**
 * @copyright Copyright @ 
 * All Rights Reserved.
 *
 * This Copyright should be changed by diffecent project
 */
/**
 * @file test.cpp
 * @brief Implement file of class test.(文件描述)
 * @author iauto
 * @version 1.0
 */

/*---------------------------------------------------------------------------*/
// Include files

#include "../include/TestProjectIF.h"

/*---------------------------------------------------------------------------*/
// Functions
int main()
{
    // Create instance
    testproject::TestProjectIF::create();

    // Get instance
    testproject::TestProjectIF* instance = testproject::TestProjectIF::getInstance();

    // Run
    instance->test();

    // Destory instance
    testproject::TestProjectIF::destory();

    return 0;
}

/*---------------------------------------------------------------------------*/
/* EOF */
