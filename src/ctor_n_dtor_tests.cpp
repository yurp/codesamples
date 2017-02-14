
#include "ctor_n_dtor.h"

#include "gtest/gtest.h"


TEST(CtorAndDtor, ExceptionInCtor) {
    try {
        ctor_and_dtor::SampleClass s;
    } catch(int) {
        ASSERT_EQ(1, ctor_and_dtor::Obj::m_allocCount);
        ASSERT_EQ(2u, ctor_and_dtor::Obj::m_objs.size());
        ASSERT_TRUE(ctor_and_dtor::Obj::m_objs.count("sp") > 0);
        ASSERT_TRUE(ctor_and_dtor::Obj::m_objs.count("noname") > 0);
        ASSERT_TRUE(ctor_and_dtor::Obj::m_objs.count("rp") == 0);
        ASSERT_EQ(0, ctor_and_dtor::Obj::m_objs["sp"]);
        ASSERT_EQ(2, ctor_and_dtor::Obj::m_objs["noname"]);
    }
}

