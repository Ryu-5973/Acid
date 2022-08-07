#ifndef ACID_SAFE_COUT_H
#define ACID_SAFE_COUT_H

#include <iostream>
#include <sstream>

#include "sync.h"

namespace acid {
class SafeCout: public std::ostringstream{
public:
    using MutexType = SpinLock;
    SafeCout() = default;
    ~SafeCout() {
        MutexType::Lock lock(m_mutex);
        std::cout << this->str();
    }
private:
    static MutexType m_mutex;
};
SafeCout::MutexType SafeCout::m_mutex{};
SafeCout scout;
// using scout = SafeCout;
    
} // namespace acid


#endif  // ACID_SAFE_COUT_H