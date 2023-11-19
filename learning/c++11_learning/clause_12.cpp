/*
 * 条款12：使用override关键字声明覆盖的函数
 */

#include <memory>

class Base {
public:
    virtual void mf1() const {}
    virtual void mf2(int x) {}
    virtual void mf3() & {}
    // void mf4() const {}
    virtual void mf4() const {}
};

class Derived: public Base {
public:
#if 0
    // 这些是使用virtual
    // 这些函数无需和父类完全匹配
    virtual void mf1() {}
    virtual void mf2(unsigned int x) {}
    virtual void mf3() && {}
    void mf4() const {}
#endif
    // 使用override
    // 会检查和父类的函数需要完全匹配
    virtual void mf1() const override {}
    virtual void mf2(int x) override {}
    virtual void mf3() & override {}
    virtual void mf4() const override {}
};

int main(int argc, char** argv)
{
    std::unique_ptr<Base> upb = std::make_unique<Derived>();
    upb->mf1();
    upb->mf2(1);
    upb->mf3();
    upb->mf4();

    return 0;
}

/* EOF */
