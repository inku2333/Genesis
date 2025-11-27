#ifndef GENOBJECTFACTORY_H
#define GENOBJECTFACTORY_H


class GenObject;

class GenObjectFactory
{
public:
    virtual ~GenObjectFactory(){}
    virtual GenObject * create() = 0;
};

#define TFACTORY_DECL(CLS)                      \
    class CLS##Factory                          \
        : public GenObjectFactory               \
    {                                           \
    public:                                     \
        virtual ~CLS##Factory(){}               \
        GenObject * create();                   \
    };

#define TFACTORY_IMPL(CLS)                      \
    GenObject * CLS##Factory::create(){         \
        return new CLS();                       \
    }


#define XFACTORY_DECL(CLS)                      \
    class CLS##Factory                          \
        : public GenObjectFactory               \
    {                                           \
    public:                                     \
        virtual ~CLS##Factory(){}               \
        GenObject * create();                   \
    };

#define XFACTORY_IMPL(CLS)                      \
    GenObject * CLS##Factory::create(){         \
        return new CLS();                       \
    }

#endif // GENOBJECTFACTORY_H
