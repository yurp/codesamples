
#include "ctor_n_dtor.h"

namespace ctor_and_dtor {

int Obj::m_allocCount = 0;
std::map<std::string, int> Obj::m_objs;

}

