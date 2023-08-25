#include <vector>
#include <list>
#include <pthread.h>

class Task
{
public:

    Task(std::function<void(void)> fun)
    : m_pFun(fun)
    {}

    Task(Task& rc) {}

    ~Task() {}
    
    void doAction(void)
    {
        m_pFun();
    }

private:

    std::function<void(void)> m_pFun;
};

class ThreadWorking
{
public:

    ThreadWorking()
    : m_iTid(NULL)
    , m_bQuit(false)
    , m_bWorking(false)
    , m_cTaskList()
    {}

    ~ThreadWorking() {}

    void start()
    {
        pthread_create(&m_iTid, NULL, &this->run, NULL);
    }

    void stop()
    {
        m_bQuit = true;
        pthread_join(m_iTid, NULL);
    }

    void addTask(const Task& task)
    {

    }

    void run(void)
    {
        while (1) {
            wait();

            if (m_bQuit) {
                break;
            }

            m_bWorking = true;

            for (auto it = m_cTaskList.begin(); it != m_cTaskList.end(); ++it) {
                it->doAcution();
            }

            m_bWorking = false;
        }
    }

    void wait()
    {}

    void notify(void)
    {}

    bool isWorking(void) {return m_bWorking;}

private:

    pthread_t   m_iTid;
    bool        m_bQuit;
    bool        m_bWorking;

    std::vector<Task> m_cTaskList;

};

static const int THREAD_POOL_WORKING_CNT = 10;

class ThreadPool
{
public:

    ThreadPool()
    : m_cTaskList()
    , m_cWorkingThreadList()
    {}

    ~ThreadPool() {}

    void start(void)
    {
        for (int i = 0; i < THREAD_POOL_WORKING_CNT; i++) {
            ThreadWorking working_thread;
            working_thread.start();
            m_cWorkingThreadList.push_back(working_thread);
        }
    }

    void stop(void)
    {
        for (auto it = m_cWorkingThreadList.begin(); it != m_cWorkingThreadList.end(); ++it) {
            it->stop();
        }
    }

    void runTask(const Task& task)
    {
        m_cTaskList.push_back(task);
        switchTask();
    }

private:

    void switchTask(void)
    {
        while (!m_cTaskList.empty()) {
            bool working = true;
            for (auto it = m_cWorkingThreadList.begin(); it != m_cWorkingThreadList.end(); ++it) {
                if (!it->isWorking()) {
                    Task tmp = m_cTaskList.pop_front();
                    it->addTask(tmp);
                    working = false;
                }
            }

            if (working) {
                break;
            }
        }
    }

    std::list<Task>           m_cTaskList;
    std::vector<ThreadWorking>  m_cWorkingThreadList;

};

int main(int argc, char** argv)
{
    ThreadPool thread_pool;
    thread_pool.start();

    Task task1(
        [](void)
        {
            printf("1 + 1 = %d", 2);
        });
    thread_pool.runTask(task1);

    thread_pool.stop();
    return 1;
}
