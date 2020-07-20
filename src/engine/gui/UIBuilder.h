#ifndef UIBUILDER_H
#define UIBUILDER_H

template <class T>
class UIBuilder {
private:
public:
    virtual T build() = 0;
};

#endif // UIBUILDER_H