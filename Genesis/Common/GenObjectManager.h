#ifndef GENOBJECTMANAGER_H
#define GENOBJECTMANAGER_H

#include <string>

class GenObject;
//class GenObjectManager;
class GenObjectFactory;
//class GenService;

class GenObjectManager
{
public:
    GenObjectManager();
    virtual ~GenObjectManager() = default;

    virtual int addFactory(const std::string& typeCode, GenObjectFactory * factory) = 0;
    virtual GenObjectFactory * removeFactory(const std::string& typeCode) = 0;
    virtual GenObject * createObject(const std::string& typeCode) = 0;

    virtual int registerService(const std::string& serviceName, GenObject * service) = 0;
    virtual GenObject * removeService(const std::string& serviceName) = 0;
    virtual GenObject * getService(const std::string& serviceName) = 0;
};

#endif // GENOBJECTMANAGER_H
