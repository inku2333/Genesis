#ifndef GENUTILS_H
#define GENUTILS_H


#include "GenGlobal.h"
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <boost/json.hpp>

namespace GenUtils
{

void usleep(int us);
void msleep(int ms);
void sleep(int s);

};

namespace Gen
{

namespace Utils
{

void usleep(int us);
void msleep(int ms);
void sleep(int s);

static inline
void bitSet(unsigned int & dst, int bit)
{
    dst |= (1 << bit);
}

static inline
void bitClear(unsigned int & dst, int bit)
{
    dst &= ~(1 << bit);
}

static inline
void bitSet(unsigned int & dst, bool v, int bit)
{
    v ? bitSet(dst, bit) : bitClear(dst, bit);
}

template<typename T>
std::set<T> fromVector(const std::vector<T>& arr)
{
    std::set<T> t;
    for (auto i = 0; i != arr.size(); ++i){
        t.insert(arr.at(i));
    }
    return t;
}

template <typename T1, typename T2>
std::vector<T1> keys(const std::map<T1, T2>& input)
{
    std::vector<T1> output;
    auto it = input.begin();
    for (; it != input.end(); ++it){
        output.push_back(it->first);
    }
    return output;
}

template <typename T1, typename T2>
std::vector<T2> values(const std::map<T1, T2>& input)
{
    std::vector<T2> output;
    auto it = input.begin();
    for (; it != input.end(); ++it){
        output.push_back(it->second);
    }
    return output;
}

template<typename T>
void remove(std::vector<T>& arr, const T& v)
{
    auto it = arr.begin();
    while (it != arr.end()){
        if (*it != v){
            ++it;
        }else{
            it = arr.erase(it);
        }
    }
}

}

// begin namespace Str
namespace Str
{

void split(const std::string& input, const std::string& spliter, std::vector<std::string>& output);
std::vector<std::string> split(const std::string& input, const std::string& spliter);
void split(const std::string& input, const std::string& spliter, std::list<std::string>& output);
void trim(std::string& s);
std::string join(const std::vector<std::string>& ls, const std::string& sep);
std::string fromInt(int number, const char * format);

std::string toHex(int number);

}
// end namespace Str

// begin namespace Hash
namespace Hash
{

std::string md5(const char * buffer, int length);
std::string md5(const std::string& text);
std::string fileMd5(const std::string& filePath);

unsigned short crc16(const unsigned char * buffer, int length);
unsigned int crc32(const unsigned char * buffer, int length);

}
// end namespace Hash


// begin namespace Json
namespace Json
{

void merge1(boost::json::object& dst, const boost::json::object& data);
boost::json::object merge2(boost::json::object& dst, const boost::json::object& data);

template<class T>
boost::json::array fromValue(const T& v)
{
    boost::json::array t;
    t.push_back(boost::json::value(v));
    return t;
}

template<class T>
boost::json::array fromVector(const std::vector<T>& d)
{
    boost::json::array t;
    for (auto i = 0; i != d.size(); ++i){
        t.push_back(boost::json::value(d.at(i)));
    }
    return t;
}

static inline
int toStringList(const boost::json::array& arr, std::vector<std::string>& output)
{
    for (auto i = 0; i != arr.size(); ++i){
        output.push_back(arr.at(i).as_string().c_str());
    }
    return (int)output.size();
}

int loadFile(const std::string& filePath, boost::json::object& output);
int loadFile(const std::string& filePath, boost::json::array& output);

}
// end namespace Json


// begin namespace FS
namespace FS
{

bool fileExist(const std::string& filePath);
std::string fileDirPath(const std::string& filePath);
bool makePath(const std::string& filePath);
bool removePath(const std::string& filePath);
bool renameFile(const std::string& src, const std::string& dest);

}
// end namespace FS


// begin namespace IO
namespace IO
{

int readFile(const std::string& filePath, char * buffer, int length);
int readFile(const std::string& filePath, std::string& text);
int writeFile(const std::string& filePath, const char * buffer, int length);
int writeFile(const std::string& filePath, const std::string& text);

}
// end namespace IO


}
#endif // GENUTILS_H
