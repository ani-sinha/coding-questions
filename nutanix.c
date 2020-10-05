
struct lock_t {
  int count;
  pthread_mutex_t rm;
};

int lock_init(struct lock_t*);
int read_lock(struct lock_t *);
int write_lock(struct lock_t*);
int read_unlock(struct lock_t*);
int write_unlock(struct lock_t*);
int lock_destroy(struct lock_t *);

int lock_init(struct lock_t* lock)
{
  lock->count = 0;
  return pthread_mutex_init(lock->rm);
}

int read_lock(struct lock_t* lock) {
  int ret;
  ret = pthread_mutex_lock(lock->rm);
  if (ret)
    return ret;
  lock->count++;
  ret = pthread_mutex_unlock(lock->rm);
  return ret;
}

int read_unlock(struct lock_t* lock) {
  int ret;
  ret = pthread_mutex_lock(lock->rm);
  if (ret)
    return ret;
  lock->count--;
  ret = pthread_mutex_unlock(lock->rm);
  return ret;
}

int write_lock(struct lock_t* lock)
{
  return pthread_mutex_lock(lock->rm);
}

int write_trylock(struct lock_t* lock) {
  return lock->count;
}

int write_unlock(struct lock_t* lock)
{
  return pthread_mutex_unlock(lock->rm);
}

int lock_destroy(struct lock_t* lock) {
  return pthread_mutex_destroy(lock->rm);
}


struct lock_t r_lock;
struct lock_t w_lock;

int main() {
  lock_init(&r_lock);
  lock_init(&w_lock);
}

void writer() {
  write_lock(&w_lock);
  while(1) {
    if (!read_trylock(&r_lock)) {
      // critical section
      break;
    }
  }

  write_unlock(w_lock);
}

void reader() {
  write_lock(&w_lock);
  read_lock(&r_lock);
  write_unlock(&w_lock);
  // critical section

  read_unlock(&r_lock);
  
}
