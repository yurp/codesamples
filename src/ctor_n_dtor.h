
#pragma once

#include <iostream>
#include <cstddef>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace ctor_and_dtor {

class Obj {
public:
    Obj()
        : Obj("noname") {
    }
    Obj(std::string s)
        : m_s(s) {
        ++m_objs[m_s];
        std::cerr << "Obj ctor\n";
    }
    ~Obj() {
        --m_objs[m_s];
        std::cerr << "Obj dtor\n";
    }

    std::string m_s;

    static void* operator new[](std::size_t sz) {
        ++m_allocCount;
        std::cerr << "Obj new[]\n";
        return ::operator new(sz);
    }

    static void* operator new(std::size_t sz) {
        ++m_allocCount;
        std::cerr << "Obj new\n";
        return ::operator new(sz);
    }

    static void operator delete[](void* ptr) {
        --m_allocCount;
        std::cerr << "Obj del[]\n";
        ::operator delete(ptr);
    }

    static void operator delete(void* ptr) {
        --m_allocCount;
        std::cerr << "Obj del\n";
        ::operator delete(ptr);
    }

    static int m_allocCount;
    static std::map<std::string, int> m_objs;

};

class SampleClass {
public:
    SampleClass()
        : m_obj1(new Obj("sp")) {
        m_obj2 = new Obj[2];
        throw 1;
        m_obj3 = new Obj("rp");
    }
    ~SampleClass() {
        delete[] m_obj3;
        delete[] m_obj2;
    }

    std::shared_ptr<Obj> m_obj1;
    Obj* m_obj2;
    Obj* m_obj3;

};

}

