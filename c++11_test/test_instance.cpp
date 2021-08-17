/*
 *
 */

/*---------------------------------------------------------------------------*/
// Include files
#include "test_instance.h"
#include <stdlib.h>

/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
TestInstance* TestInstance::getInstance()
{
    static TestInstance instance;
    return &instance;
}

void TestInstance::output(void)
{
    printf("TestInstance output\n");
}

TestInstance::TestInstance()
{

}

TestInstance::~TestInstance()
{
    
}

/*---------------------------------------------------------------------------*/
/* EOF */
