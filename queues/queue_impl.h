/**************************************
 * @class Queue
 * @desc  Implements Queue
 *************************************/
template <class T>
void Queue<T>::print_queue(){
  for (int i = 0; i < rear; ++i){
    cout << q[i] << endl;
  }
}

template <class T>
void Queue<T>::enqueue(T elem){
  if(front >= max){
    throw runtime_error("Out of space. Reallocate memory");
  }
  q[rear] = elem; rear++;
}

template <class T>
T Queue<T>::dequeue(){
  if(this->is_empty()){
    throw runtime_error("Empty Queue");
  }

  T result = q[front];
  for (int i = 0; i < rear; i++) {
    swap(q[i], q[i + 1]);
  }

  --rear;
  return result;

}

template <class T>
T Queue<T>::get_item_at(int index){
  if (index > max || index < 0) {
    throw runtime_error("Index is out of range");
  }

  if (q[index] == NULL) {
    throw runtime_error("Element at position Index not initialized");
  }

  return q[index];
}

template <class T>
T Queue<T>::get_front(){
  if (this->is_empty()) {
    throw runtime_error("Empty Queue");
  }

  return this->q[this->front];
}

template <class T>
bool Queue<T>::is_empty() {
  if (rear <= 0) {
    return true;
  }

  return false;
}

template <class T>
bool Queue<T>::contains(T item) {
  for (int i = 0; i < rear; ++i) {
    if (this->q[i] == item) {
      return true;
    }
  }

  return false;
}
//End Class
