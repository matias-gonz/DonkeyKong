#ifndef TALLER_PROG_I_2021_1C_KIWI_LOGGER_H
#define TALLER_PROG_I_2021_1C_KIWI_LOGGER_H


#include <memory>
#include <fstream>
#include <string>
#include "../controller/Configuration.h"

#define MAXIMUM_NUMBER_OF_LOGS 5
#define ERROR Logger::Type::Error
#define INFO Logger::Type::Info
#define DEBUG Logger::Type::Debug

namespace Logger {

    // Severity level enum.
    enum Type {
        Error,
        Info,
        Debug
    };

    bool fileExist(std::string fileName);

    void startLogger(Configuration *configuration, std::string name);

    void logShouldHaveLessThanTenGameplays( std::string &logName);

    void deleteOldestLog(std::string &logName);

    void log(Type logType, const std::string &messsage);

    class Log {
    public:

        Log(const std::string &path);

        void addLog(Type logType, const std::string &message);

        void addFinalLog();

        void setConfiguration(json log);

        ~Log();

    private:
        std::ofstream logFile;
        std::string levels[3] = {"ERROR", "INFO", "DEBUG"};
        bool logTypeEnabled[3] = {false, false, false};

        std::string getCurrentDateTime();

        bool logTypeIsEnabled(Type logType);

        bool loadLoggerFromJson(char const *logType, json log);

    };
}


#endif //TALLER_PROG_I_2021_1C_KIWI_LOGGER_H
