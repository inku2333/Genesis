#ifndef GENOBJECT_H
#define GENOBJECT_H


#include "GenGlobal.h"
#include <string>

class GenObject;
class GenObjectManager;
//class GenObjectFactory;
//class GenService;

class GenObject  // ObjectManager最核心，所有实例都由它控制，理论上没有c风格代码可以不需要g_app
{
public:
    explicit GenObject(GenObject *parent = nullptr);
    virtual ~GenObject() = default;

    void setObjectName(const std::string& name);
    const std::string& getObjectName() const;

    virtual std::string getTypeCode() const;
    virtual void setObjectManager(GenObjectManager * m);
    virtual GenObjectManager * getObjectManager() const;

    template<typename T>
    T * getService(const std::string& serviceName)  // 解耦，依赖注入
    {
        return dynamic_cast<T *>(this->getServiceImpl(serviceName));
    }

    template<typename T>
    T * createObject(const std::string& typeCode)
    {
        return dynamic_cast<T *>(this->createObjectImpl(typeCode));
    }

protected:
    GenObject * createObjectImpl(const std::string& typeCode);
    GenObject * getServiceImpl(const std::string& serviceName);

protected:
    GenObjectManager * m_objectManager;
    GenObject * m_parentObject;
    std::string m_typeCode;
    std::string m_objectName;
};

const std::string GENC_TYPECODE = "typeCode";
const std::string GENC_OBJNAME = "name";

#endif // GENOBJECT_H
