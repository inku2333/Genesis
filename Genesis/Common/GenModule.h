#ifndef GENMODULE_H
#define GENMODULE_H


#include "GenObject.h"

class GenObjectManager;

class GenModule
        : public GenObject
{
public:
    GenModule(GenObject * parent);

    virtual std::string getModuleName() = 0;
    virtual std::string getVersion() = 0;
    virtual void initialize(GenObjectManager * m) = 0;
    virtual void terminal() = 0;
};

#endif // GENMODULE_H
