#ifndef ILOGGER_H
#define ILOGGER_H


#include <string>
#include <boost/json.hpp>


class ILogger
{
public:
    virtual ~ILogger(){}

    virtual void addLogData(
            const std::string& logType,
            const std::string& text,
            const std::string& color) = 0;

    virtual void addLogData(
            int dut,
            const std::string& text,
            const std::string& color) = 0;

    virtual void addLogData(
            const std::string& logType,
            const std::string& text) = 0;

    virtual void addLogData(
            int dut,
            const std::string& text) = 0;
};

const std::string GENS_LOGGER = "Gen.S.Logger";
const std::string GENS_FILELOGGER = "Gen.S.FileLogger";
const std::string GENS_HTTPLOGGER = "Gen.S.HttpLogger";

// constants for logger api
const std::string GENC_LT_TEST = "test";
const std::string GENC_LT_RUNNING = "running";
const std::string GENC_LT_SYSTEM = "SYSTEM";
const std::string GENC_LT_WARNING = "WARNING";
const std::string GENC_LT_MONITOR = "MONITOR";

//const std::string GENC_COLOR_READ = "#FF0000";
//const std::string GENC_COLOR_GREEN = "#00FF00";
//const std::string GENC_COLOR_BLUE = "#0000FF";
//const std::string GENC_COLOR_BLACK = "#000000";

#endif // ILOGGER_H
