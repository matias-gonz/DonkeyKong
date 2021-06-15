#include "credentials.h"

credentials::credentials() {
  this->inputUser = "";
  this->inputPass = "";
}

void credentials::initialize(std::string inputUser, std::string inputPass, ClientSocket* socket) {
  this->inputUser = inputUser;
  this->inputPass = inputPass;
  this->socket = socket;
}

std::string credentials::getInputUser() {
  return this->inputUser;
}

std::string credentials::getInpuPass() {
  return this->inputPass;
}

ClientSocket* credentials::getSocket() {
  return this->socket;
}
