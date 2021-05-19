#ifndef TALLER_PROG_I_2021_1C_KIWI_LOGGER_H
#define TALLER_PROG_I_2021_1C_KIWI_LOGGER_H

#include <memory>
#include <fstream>
#include <string>
#include "../controller/Configuration.h"

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

  void startLogger(const std::string &path, Configuration* configuration);

  void log(Type logType, const std::string &messsage);

  class Log {
  public:

    Log(const std::string &path);

    void addLog(Type logType, const std::string &message);

    void setConfiguration(json log);

    ~Log();

  private:
    std::ofstream logFile;
    std::string levels[3] = {"ERROR", "INFO", "DEBUG"};
    bool logTypeEnabled[3] = {false, false, false};

    std::string getCurrentDateTime();

    bool logTypeIsEnabled(Type logType);

  };
}


#endif //TALLER_PROG_I_2021_1C_KIWI_LOGGER_H
