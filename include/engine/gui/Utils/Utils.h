#ifndef GUIUITS_H
#define GUIUITS_H

#include <memory>

class MultiSharedFromThis: public std::enable_shared_from_this<MultiSharedFromThis> {
public:
    virtual ~MultiSharedFromThis() { }
};

template <class T>
class inheritable_enable_shared_from_this : virtual public MultiSharedFromThis {
public:
    std::shared_ptr<T> shared_from_this() {
        return std::dynamic_pointer_cast<T>(MultiSharedFromThis::shared_from_this());
    }

    template <class Down>
    std::shared_ptr<Down> downcasted_shared_from_this() {
        return std::dynamic_pointer_cast<Down>(MultiSharedFromThis::shared_from_this());
    }
};

class virtual_enable_shared_from_this_base : public std::enable_shared_from_this<virtual_enable_shared_from_this_base> {
public:
    virtual ~virtual_enable_shared_from_this_base() {}
};

template<typename T>
class virtual_enable_shared_from_this: virtual virtual_enable_shared_from_this_base {
public:
    std::shared_ptr<T> shared_from_this() {
        return std::dynamic_pointer_cast<T>(virtual_enable_shared_from_this_base::shared_from_this());
    }
};

#endif // GUIUITS_H