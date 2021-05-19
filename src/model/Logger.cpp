#include "Logger.h"

namespace Logger {

  static std::unique_ptr<Log> glog;

  void startLogger(const std::string &path, Configuration* configuration) {
    glog = std::make_unique<Log>(path);
    json log = configuration->getLogLevel();
    glog->setConfiguration(log);

    if(configuration->isDefault())
      Logger::log(Type::Error, "No se cargó el archivo de configuración,"
                               "se cargó la configuración default");


    Logger::log(Type::Info, "Inicio del log");
  }

  void log(Type logType, const std::string &message) {
    glog->addLog(logType, message);
  }

  Log::Log(const std::string &path) : logFile{} {
    logFile.open(path);
  }

  void Log::addLog(Type logType, const std::string &message) {
    if (logFile.is_open() && this->logTypeIsEnabled(logType)) {
      logFile << this->getCurrentDateTime() << " [" << levels[static_cast<int>(logType)] << "]" << message << std::endl;
    }
  }

  void Log::setConfiguration(json log) {
    this->logTypeEnabled[static_cast<int>(Logger::Error)] = log.at("ERROR").get<bool>();
    this->logTypeEnabled[static_cast<int>(Logger::Info)] = log.at("INFO").get<bool>();
    this->logTypeEnabled[static_cast<int>(Logger::Debug)] = log.at("DEBUG").get<bool>();
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
    addLog(Type::Info, "Fin del log");
    logFile.close();
  }
}