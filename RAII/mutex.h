#include <pthread.h>
#include <cstdlib>
#include <stdio.h>

class Mutex {
 public:
  Mutex();
  ~Mutex();

  void Lock();
  void Unlock();

 private:
  pthread_mutex_t mu_;

  // No copying
  Mutex(const Mutex&);
  void operator=(const Mutex&);
};
