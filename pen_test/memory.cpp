/*
内存管理：
封装一个类，实现简单的内存管理功能，管理一块连续内存
1.实现两个功能，内存分配(malloc)和内存释放(free)
2.分配的内存应是连续的，内存不足时返回空，malloc申请大小的单位是字节
3.释放的内存可重新分配
4.内存分配需兼顾效率和内存利用率，高效率指内存分配要有较低的时间复杂度，高利用率指减少内存碎片产生
5.暂不考虑内存对齐等因素
*/

#include <stdint.h>
#include <map>

class MemoryManager
{
public:

    MemoryManager(uint32_t size)
    : m_uSize(size)
    , m_pMemory(nullptr)
    , m_cMemortyMap()
    {
        m_pMemory = new uint8_t[m_uSize];
    }

    ~MemoryManager()
    {
        if (m_pMemory != nullptr) {
            delete[] m_pMemory;
        }
    }

    uint8_t* malloc(uint32_t size);
    bool free(uint8_t* addr);

private:

    uint32_t m_uSize;
    uint8_t* m_pMemory;

    std::map<uint8_t*, uint32_t> m_cMemortyMap;

    MemoryManager(MemoryManager& rc);
    MemoryManager& operator=(MemoryManager& rc);

};

uint8_t* MemoryManager::malloc(uint32_t size)
{
    // 1.
    auto it_pre = m_cMemortyMap.begin();
    auto it_next = it_pre;
    it_next++;
    while (it_next != m_cMemortyMap.end()) {
        if (it_next->first - (it_pre->first + it_pre->second) > size) {
            uint8_t* alloc_addr = it_next->first + it_next->second;
            m_cMemortyMap[alloc_addr] = size;
            return alloc_addr;
        }

        it_pre = it_next;
        it_next++;
    }

    // 2.
    uint32_t alloced_size = 0;
    for (auto it = m_cMemortyMap.begin(); it != m_cMemortyMap.end(); ++it) {
        alloced_size += it->second;
    }

    if (alloced_size + size > m_uSize) {
        return nullptr;
    }

    uint8_t* alloc_addr = m_pMemory + alloced_size;
    m_cMemortyMap[alloc_addr] = size;
    return alloc_addr;
}

bool MemoryManager::free(uint8_t* addr)
{
    auto it = m_cMemortyMap.find(addr);
    if (it != m_cMemortyMap.end()) {
        m_cMemortyMap.erase(it);
        return true;
    }

    return false;
}
