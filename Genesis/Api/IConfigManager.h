#ifndef ICONFIGMANAGER_H
#define ICONFIGMANAGER_H


#include <string>
#include <boost/json.hpp>

class IConfigManager
{
public:
    virtual ~IConfigManager(){}

    virtual bool loadJsonAs(const std::string& filePath, const std::string& name) = 0;
    virtual boost::json::object load(const std::string& filePath) = 0;
    virtual boost::json::object getConfigData(const std::string& name) = 0;
    virtual boost::json::value getItem(const std::string& name, const std::string& item) = 0;
    virtual std::string getString(const std::string& name, const std::string& item) = 0;
    virtual int setItem(const std::string& name, const std::string& item, const boost::json::value& value) = 0;
    virtual int addConfigData(const std::string& name, const boost::json::object& cfgData) = 0;
    virtual int saveConfigData(const std::string& name) = 0;
};

const std::string GENS_CFGMANAGER = "Gen.S.ConfigManager";

const std::string GENC_CFGNAME_MAIN = "app";

extern IConfigManager * GetConfigManager();

#endif // ICONFIGMANAGER_H
