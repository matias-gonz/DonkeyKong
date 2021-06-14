#include <SDL_events.h>
#include "QueueThrd.h"
#include <pthread.h>

QueueThrd::QueueThrd() {
  pthread_mutex_init(&this->mutex,NULL);
  this->queue = std::queue<EventContainer>();
}

void QueueThrd::push(EventContainer e) {
  //pthread_mutex_lock(&this->mutex);
  this->queue.push(e);
  //pthread_mutex_unlock(&this->mutex);
}

EventContainer QueueThrd::pop(){
  //pthread_mutex_lock(&this->mutex);
  EventContainer e = this->queue.front();
  this->queue.pop();
  //pthread_mutex_unlock(&this->mutex);
  return e;
}

bool QueueThrd::isEmpty() {
  return (this->queue.size() == 0);
}