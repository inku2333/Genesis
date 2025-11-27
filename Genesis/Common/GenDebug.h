#ifndef GENDEBUG_H
#define GENDEBUG_H


#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <functional>
#include <boost/json.hpp>

typedef std::function<void (const std::string&)> GenMessageHandler;

class GenDebug
{
protected:
    struct Stream{
        std::stringstream ss;
        int refcnt;

        Stream(): refcnt(1){}  // 初次创建就计数为1
    };
    Stream * m_stream;
    GenMessageHandler m_handler;

public:
    GenDebug();
    GenDebug(GenMessageHandler handler);
    GenDebug(const GenDebug& d);
    ~GenDebug();

    GenDebug& operator = (const GenDebug& d);

public:
    template<typename T>
    GenDebug& operator << (const std::vector<T>& c)
    {
        return this->formatSeqContainer(c, "std::vector");
    }

    template<typename T>
    GenDebug& operator << (const std::list<T>& c)
    {
        return this->formatSeqContainer(c, "std::list");
    }

    template<typename T>
    GenDebug& operator << (const std::set<T>& c)
    {
        return this->formatSeqContainer(c, "std::set");
    }

    template<typename K, typename V>
    GenDebug& operator << (const std::map<K, V>& c)
    {
        return this->formatPairContainer(c, "std::map");
    }

    GenDebug& operator << (const boost::json::object& v);
    GenDebug& operator << (const boost::json::array& v);

    template<typename T>
    GenDebug& operator << (const T& v)
    {
        m_stream->ss << v;
        return *this;
    }

    GenDebug& operator << (const unsigned char v)
    {
        m_stream->ss << (int)v;
        return *this;
    }

    GenDebug& format(const char * fmt, ...);

protected:
    template<typename SeqContainer>
    GenDebug& formatSeqContainer(const SeqContainer& c, const std::string& name)
    {
        m_stream->ss << name << "(";
        auto it = c.begin();
        for (; it != c.end(); ++it){
            if (it != c.begin()){
                m_stream->ss << ", ";
            }
            m_stream->ss << *it;
        }
        m_stream->ss << ")";

        return *this;
    }

    template<typename PairContainer>
    GenDebug& formatPairContainer(const PairContainer& c, const std::string& name)
    {
        m_stream->ss << name << "(";
        auto it = c.begin();
        for (; it != c.end(); ++it){
            if (it != c.begin()){
                m_stream->ss << ", ";
            }
            m_stream->ss << "{" << it->first << "," << it->second << "}";
        }
        m_stream->ss << ")";

        return *this;
    }

    void printData(const std::string& data);
};

class GenNoDebug
{
public:
    GenNoDebug();
    GenNoDebug(const GenNoDebug& d);
    ~GenNoDebug();

    template<typename T>
    GenNoDebug& operator << (const T& /*v*/)
    {
        return *this;
    }

    GenNoDebug& format(const char * /*fmt*/, ...)
    {
        return *this;
    }
};


#endif // GENDEBUG_H
