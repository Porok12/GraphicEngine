#ifndef NOTIMPLEMENTEDEXCEPTION
#define NOTIMPLEMENTEDEXCEPTION

#include <stdexcept>

class NotImplementedException : public std::logic_error{
public:
    NotImplementedException() : logic_error("Function not yet implemented.") { }
};

#endif // NOTIMPLEMENTEDEXCEPTION