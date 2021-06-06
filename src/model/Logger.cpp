#include "Logger.h"

namespace Logger {

    static std::unique_ptr<Log> glog;

    bool fileExist(const std::string fileName ){
        std::ifstream fileCheck;
        fileCheck.open(fileName, std::ifstream::in);

        bool exist = fileCheck.is_open();
        if(exist)
            fileCheck.close();

        return  exist;
    }

    void startLogger(Configuration *configuration) {
        const std::string logName = "log.txt";

        if(Logger::fileExist(logName)){
            Logger::logShouldHaveLessThanTenGameplays(logName);
        }

        glog = std::make_unique<Log>(logName);
        json log = configuration->getLogLevel();
        glog->setConfiguration(log);

        if (configuration->isDefault())
            Logger::log(Type::Error, "No se cargó el archivo de configuración,"
                                     "se cargó la configuración default");

        Logger::log(Type::Info, "Inicio del log");
    }

    void logShouldHaveLessThanTenGameplays(const std::string &logName) {
        std::ifstream oldLogFile;
        oldLogFile.open(logName,std::ifstream::in);
        int numberOfGameplays = 0;

        std::string line;
        std::string phrase = "Inicio del log";
        while (getline(oldLogFile, line )) {
            std::string::size_type pos = line.find(phrase);
            if(pos != std::string::npos)
                numberOfGameplays++;
        }

        oldLogFile.close();

        if (numberOfGameplays >= MAXIMUM_NUMBER_OF_LOGS)
            Logger::deleteOldestLog(logName);
    }

    void deleteOldestLog(const std::string &logName){
        int numberOfGameplays =0;

        std::ofstream newLogFile;
        newLogFile.open("newLog.txt");

        std::ifstream oldLogFile;
        oldLogFile.open(logName,std::ifstream::in);

        std::string line;
        std::string phrase = "Inicio del log";
        while (getline(oldLogFile, line )) {
            std::string::size_type pos = line.find(phrase);
            if(pos != std::string::npos)
                numberOfGameplays++;
            if(numberOfGameplays>=2)
                newLogFile << line << std::endl;
        }

        newLogFile.close();
        oldLogFile.close();

        std::remove(logName.c_str());
        rename("newLog.txt", logName.c_str());


    }

    void log(Type logType, const std::string &message) {
        glog->addLog(logType, message);
    }

    Log::Log(const std::string &path) : logFile{} {
        logFile.open(path, std::ofstream::app);
    }


    void Log::addLog(Type logType, const std::string &message) {
        if (logFile.is_open() && this->logTypeIsEnabled(logType)) {
            logFile << this->getCurrentDateTime() << " [" << levels[static_cast<int>(logType)] << "]" << message
                    << std::endl;
        }
    }

    void Log::addFinalLog() {
        if (logFile.is_open()) {
            logFile << this->getCurrentDateTime() << " [" << levels[static_cast<int>(Logger::Info)] << "]" << "Fin del Log"
                    << std::endl << "--------------------------------------------------------------------------"<< std::endl << std::endl;
        }
    }

    void Log::setConfiguration(json log) {
        this->logTypeEnabled[static_cast<int>(Logger::Error)] = this->loadLoggerFromJson("ERROR", log);
        this->logTypeEnabled[static_cast<int>(Logger::Info)] = this->loadLoggerFromJson("INFO", log);
        this->logTypeEnabled[static_cast<int>(Logger::Debug)] = this->loadLoggerFromJson("DEBUG", log);
    }

    bool Log::loadLoggerFromJson(char const *logType, json log) {
      bool defaultType = true;
      if (log.contains(logType)) {
        defaultType = log.at(logType).get<bool>();
      } else {
        std::string message =
                std::string("Error al buscar la clave ") + logType + std::string(". Se pone por defecto como true.");
        Logger::log(Logger::Error, message);
      }
      return defaultType;
    }

    std::string Log::getCurrentDateTime() {
        time_t now = time(0);
        struct tm dateTime;
        dateTime = *localtime(&now);

        char dateTimeString[80];
        strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d %X", &dateTime);

        return std::string(dateTimeString);
    };

    bool Log::logTypeIsEnabled(Type logType) {
        return this->logTypeEnabled[logType];
    }

    Log::~Log() {
        addFinalLog();
        logFile.close();
    }
}