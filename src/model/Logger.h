#ifndef TALLER_PROG_I_2021_1C_KIWI_LOGGER_H
#define TALLER_PROG_I_2021_1C_KIWI_LOGGER_H

#include <memory>
#include <fstream>
#include <string>

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

    void startLogger(const std::string &path);

    void log(Type logType, const std::string &messsage);

    class Log {
    public:

        Log(const std::string &path);

        void addLog(Type logType, const std::string &messsage);

        ~Log();

    private:
        std::ofstream logFile;
        std::string levels[5] = {"ERROR", "INFO", "DEBUG"};

        std::string getCurrentDateTime();
    };
}


#endif //TALLER_PROG_I_2021_1C_KIWI_LOGGER_H
