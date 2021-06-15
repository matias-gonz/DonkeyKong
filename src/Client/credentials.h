#ifndef TALLER_PROG_I_2021_1C_KIWI_CREDENTIALS_H
#define TALLER_PROG_I_2021_1C_KIWI_CREDENTIALS_H

#include <string>
#include "../Socket/ClientSocket.h"

class credentials {
public:
  credentials();

  void initialize(std::string inputUser, std::string inputPass, ClientSocket* socket);

  std::string getInputUser();

  std::string getInpuPass();

  ClientSocket* getSocket();

private:
  std::string inputUser;
  std::string inputPass;
  ClientSocket *socket;
};

#endif //TALLER_PROG_I_2021_1C_KIWI_CREDENTIALS_H
