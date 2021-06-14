#include <SDL_events.h>
#include "QueueThrd.h"
#include <pthread.h>

QueueThrd::QueueThrd() {
  pthread_mutex_init(&this->mutex,NULL);
  this->queue = std::queue<SDL_Event>();
}

void QueueThrd::push(SDL_Event e) {
  //pthread_mutex_lock(&this->mutex);
  this->queue.push(e);
  //pthread_mutex_unlock(&this->mutex);
}

SDL_Event QueueThrd::pop(){
  //pthread_mutex_lock(&this->mutex);
  SDL_Event e = this->queue.front();
  this->queue.pop();
  //pthread_mutex_unlock(&this->mutex);
  return e;
}

bool QueueThrd::isEmpty() {
  return this->queue.empty();
}