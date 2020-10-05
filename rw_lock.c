reader:

mutex_lock(read_lck);
read_cnt++;
mutex_unlock(read_lck);

// critical section

mutex_lock(read_lck);
read_cnt--;
mutex_unlock(read_lck);


writer:

mutex_lock(write_lck);

while(1) {
  mutex_lock(read_lck);
  if (!read_cnt) {
    // critical section
    mutex_unlock(read_lck);
    break;
  }
  mutex_unlock(read_lck);

}

mutex_unlock(write_lock);
