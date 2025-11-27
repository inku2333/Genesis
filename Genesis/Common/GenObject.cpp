#include "GenObject.h"
#include "GenObjectManager.h"

GenObject::GenObject(GenObject *parent)
    : m_objectManager(nullptr)
    , m_parentObject(parent)
{
    m_typeCode = "Gen.Object";
    if (m_parentObject){
        m_objectManager = m_parentObject->getObjectManager();
    }
}

void GenObject::setObjectName(const std::string& name)
{
    m_objectName = name;
}

const std::string& GenObject::getObjectName() const
{
    return m_objectName;
}

std::string GenObject::getTypeCode() const
{
    return m_typeCode;
}

void GenObject::setObjectManager(GenObjectManager * m)
{
    if(m_objectManager != m){
        m_objectManager = m;
    }
}

GenObjectManager * GenObject::getObjectManager() const
{
    return m_objectManager;
}

GenObject * GenObject::createObjectImpl(const std::string& typeCode)
{
    return m_objectManager->createObject(typeCode);
}

GenObject * GenObject::getServiceImpl(const std::string& serviceName)
{
    return m_objectManager->getService(serviceName);
}
