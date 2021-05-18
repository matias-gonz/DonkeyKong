#include "Logger.h"

namespace Logger {

    static std::unique_ptr<Log> glog;

    void startLogger(const std::string& path) {
        glog = std::make_unique<Log>(path);

        Logger::log(Type::Info, "Inicio del log");
    }

    void log(Type logType, const std::string& message) {
        glog->addLog(logType, message);
    }

    Log::Log(const std::string& path) : logFile{} {
        logFile.open(path);
    }

    void Log::addLog(Type logType, const std::string& message) {
        if (logFile.is_open()) {

            logFile << this->getCurrentDateTime() <<" [" << levels[static_cast<int>(logType)] << "]" << message << std::endl;
        }
    }

    std::string Log::getCurrentDateTime(){
        time_t now = time(0);
        struct tm  dateTime;
        dateTime = *localtime(&now);

        char  dateTimeString[80];
        strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d %X", &dateTime);

        return std::string(dateTimeString);
    };

    Log::~Log() {
        addLog(Type::Info, "Fin del log");
        logFile.close();
    }
}