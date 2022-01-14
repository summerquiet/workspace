/**
 * @copyright Copyright @ 
 * All Rights Reserved.
 *
 * This Copyright should be changed by diffecent project
 */
/**
 * @file TestProjectPulbicDef.h
 * @brief Declaration file of class TestProjectPulbicDef.(文件描述)
 * @author iauto
 * @version 1.0
 */

#ifndef CXX_TESTPROJECTPUBLICDEF_H
#define CXX_TESTPROJECTPUBLICDEF_H

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

/*---------------------------------------------------------------------------*/
// Include files

/*---------------------------------------------------------------------------*/
// Global namespace define

// Define TestProjct namespace for all
#define TESTPROJECT_NAMESPACE_BEGINE \
namespace testproject \
{ \

#define TESTPROJECT_NAMESPACE_END \
} \

/*---------------------------------------------------------------------------*/
// Namesapce
TESTPROJECT_NAMESPACE_BEGINE

/*---------------------------------------------------------------------------*/
// Value define

static const int TEST_CONST_VALUE = 1;      ///< this is a test const define value

/*---------------------------------------------------------------------------*/
// Namesapce
TESTPROJECT_NAMESPACE_END

/*---------------------------------------------------------------------------*/
#endif  // CXX_TESTPROJECTPUBLICDEF_H
/* EOF */
