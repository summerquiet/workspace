/*
 *
 */

/*---------------------------------------------------------------------------*/
// Include files
#include <memory>

/*---------------------------------------------------------------------------*/
using std::unique_ptr;

/*---------------------------------------------------------------------------*/
// Class define
class TestInstance
{
public:
    virtual ~TestInstance();
    static TestInstance* getInstance();

    void output(void);

private:
    TestInstance();

    TestInstance(TestInstance&) = delete;
    TestInstance& operator = (TestInstance&) = delete;
};

/*---------------------------------------------------------------------------*/
/* EOF */
