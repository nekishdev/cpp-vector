#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class vector {

public:
  using value_type = T;

  using reference = T&;
  using const_reference = const T&;

  using pointer = T*;
  using const_pointer = const T*;

  using iterator = pointer;
  using const_iterator = const_pointer;

private:
  pointer _data;
  size_t _size, _capacity, _cur_index;

  void copy(const vector& other);

public:
  // O(1) nothrow
  vector() noexcept;

  // O(N) strong
  vector(const vector& other);

  // O(1) strong
  vector(vector&& other);

  // O(N) strong
  vector& operator=(const vector& other);

  // O(1) strong
  vector& operator=(vector&& other);

  // O(N) nothrow
  ~vector() noexcept;

  // O(1) nothrow
  reference operator[](size_t index);

  // O(1) nothrow
  const_reference operator[](size_t index) const;

  // O(1) nothrow
  pointer data() noexcept;

  // O(1) nothrow
  const_pointer data() const noexcept;

  // O(1) nothrow
  size_t size() const noexcept;

  // O(1) nothrow
  reference front();

  // O(1) nothrow
  const_reference front() const;

  // O(1) nothrow
  reference back();

  // O(1) nothrow
  const_reference back() const;

  // O(1)* strong
  void push_back(const T& value);

  // O(1) nothrow
  void pop_back();

  // O(1) nothrow
  bool empty() const noexcept;

  // O(1) nothrow
  size_t capacity() const noexcept;

  // O(N) strong
  void reserve(size_t new_capacity);

  // // O(N) strong
  void shrink_to_fit();

  // O(N) nothrow
  void clear() noexcept;

  // // O(1) nothrow
  // void swap(vector& other) noexcept;

  // // O(1) nothrow
  iterator begin() noexcept;

  // // O(1) nothrow
  iterator end() noexcept;

  // // O(1) nothrow
  const_iterator begin() const noexcept;

  // // O(1) nothrow
  const_iterator end() const noexcept;

  // // O(N) strong
  iterator insert(const_iterator pos, const T& value);

  // // O(N) nothrow(swap)
  iterator erase(const_iterator pos);

  // // O(N) nothrow(swap)
  iterator erase(const_iterator first, const_iterator last);
};







template<typename T>
vector<T>::vector() noexcept : _data{nullptr}, _size{0}, _capacity{0}, _cur_index{0} {
    //printf("constructor vector() called\n");
}

template<typename T>
void vector<T>::copy(const vector& other) {    
    if (!other.empty())
    {
        size_t mem_size = other.size() * sizeof(T), copied = 0;
        _data = static_cast<T*>(operator new(mem_size));
        try {
            for (size_t i = 0; i < other.size(); i++) {
                new (_data + i) T(other[i]);
                copied++;
            }
        } catch (...) {
            for (size_t i = 0; i < copied; i++) {
                _data[i].~T();
            }
            operator delete (_data);
            _data = nullptr;
            throw;
        }
        
    } else {
        _data = nullptr;
    }

    _size = _capacity = other.size();
    //printf("copy other. new size: %lu, new cap: %lu\n", _size, _capacity);
}

template<typename T>
vector<T>::vector(const vector &other) {
    //printf("constructor vector(& other) called\n");
    if (this == &other) {
        return;
    }
    _data=nullptr; _size = _capacity = _cur_index = 0;
    copy(other);
}

template<typename T>
vector<T>::vector(vector &&other) {
    //printf("constructor vector(&& other) called\n");
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    other._size = 0;
    other._capacity = 0;
    other._data = nullptr;
}



  // O(N) strong
  template<typename T>
  vector<T>& vector<T>::operator=(const vector<T>& other) {
    //printf("copy assign called\n");
    if (this != &other) {
        if (!empty()) {
            clear();
            operator delete (_data);
            _capacity = 0;
        }
        copy(other);
    }
    return *this;
  }

  // O(1) strong
  template <typename T>
  vector<T>& vector<T>::operator=(vector<T>&& other) {
    // printf("move assign called\n");
    if (this != &other) {
      clear();
      operator delete(_data);

      _data = other._data;
      _size = other._size;
      _capacity = other._capacity;

      other._size = 0;
      other._capacity = 0;
      other._data = nullptr;
    }
    return *this;
  }

  template <typename T>
  vector<T>::~vector() noexcept {
    if (_size > 0) {
      for (size_t i = _size; i > 0; i--) {
        _data[i-1].~T();
      }

      operator delete(_data);
    }
  }

// O(1) nothrow
template<typename T>
T& vector<T>::operator[](size_t index) {
    //printf("operator[] called\n");
    return _data[index];
}

// O(1) nothrow
template<typename T>
const T& vector<T>::operator[](size_t index) const {
    //printf("const operator[] called\n");
    return _data[index];
}

template<typename T>
T* vector<T>::data() noexcept {
    return _data;
}

template<typename T>
const T* vector<T>::data() const noexcept {
    return _data;
}


template<typename T>
size_t vector<T>::size() const noexcept {
    return _size;
}


// O(1) nothrow
template<typename T>
T& vector<T>::front() {
    return _data[0];
}

// O(1) nothrow
template<typename T>
const T& vector<T>::front() const {
    return _data[0];
}

// O(1) nothrow
template<typename T>
T& vector<T>::back() {
    return _data[_size-1];
}

// O(1) nothrow
template<typename T>
const T& vector<T>::back() const {
    return _data[_size-1];
}

template<typename T>
void vector<T>::push_back(const T& value) {
    //printf("push_back\n");
    size_t first_alloc_size = 2;
    size_t new_capacity = 0;
    if (_capacity == 0) {
        new_capacity = first_alloc_size;
    } else if (_capacity < _size + 1) {
        new_capacity = _capacity*2;
    }
    if (new_capacity > 0) {
        //printf("start reserve %lu...\n", new_capacity);
        T* new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));
        // T* new_data = static_cast<T*>(malloc(new_capacity * sizeof(T)));
        if (_capacity > 0) {
            size_t copied = 0;
            try
            {
                for (size_t i = 0; i < _size; i++) {
                    new (new_data + i) T(_data[i]);
                    copied++;
                }
                
                new (new_data + _size) T(value);
                copied++;
            }
            catch(...)
            {
                if (copied > 0) {
                    for (size_t i = 0; i < copied; i++) {
                        new_data[i].~T();
                    }
                }
                operator delete(new_data);
                throw;
            }

            for (size_t i = 0; i < _size; i++) {
                _data[i].~T();
            }
            operator delete(_data);
            // free(_data);

            _size++;
        } else {
            new (new_data + _size) T(value);
            _size++;
        }
        //printf("reserved %lu\n", new_capacity);
        _capacity = new_capacity;
        _data = new_data;
    } else {
        new (_data + _size) T(value);
        _size++;
    }
    
    // new (_data + _size) T(value);
    // _size++;
    
}

template<typename T>
void vector<T>::pop_back() {
    if (_size > 0)
    {
        _data[_size-1].~T();
        _size--;
    }
}

template<typename T>
bool vector<T>::empty() const noexcept {
    return _size == 0;
}


template<typename T>
size_t vector<T>::capacity() const noexcept {
    return _capacity;
}

template<typename T>
void vector<T>::reserve(size_t new_capacity) {
    // trying to reserve 0 or less than already reserved
    if (new_capacity <= _capacity)
    {
        return;
    }
    
    //printf("start reserve %lu...\n", new_capacity);
    T* new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));
    if (_capacity > 0) {
        size_t copied = 0;
        try {
            for (size_t i = 0; i < _size; i++) {
                new (new_data + i) T(_data[i]);
                copied++;
            }
        } catch (...) {
            for (size_t i = 0; i < copied; i++) {
                new_data[i].~T();
            }
            operator delete(new_data);
            throw;
        }
        
        for (size_t i = 0; i < _size; i++) {
            _data[i].~T();
        }

        operator delete(_data);
    }
    //printf("reserved %lu\n", new_capacity);
    _capacity = new_capacity;
    _data = new_data;
}

// O(N) strong
template<typename T>
void vector<T>::shrink_to_fit() {
    if (_capacity > _size) {
        //printf("start reserve %lu...\n", new_capacity);
        T* new_data = static_cast<T*>(operator new(_size * sizeof(T)));

        size_t copied = 0;
        try {
            for (size_t i = 0; i < _size; i++) {
                new (new_data + i) T(_data[i]);
                copied++;
            }
        } catch (...) {
            for (size_t i = 0; i < copied; i++) {
                new_data[i].~T();
            }
            operator delete(new_data);
            throw;
        }
        
        for (size_t i = 0; i < _size; i++) {
            _data[i].~T();
        }

        operator delete(_data);
    
        //printf("reserved %lu\n", new_capacity);
        _capacity = _size;
        _data = new_data;
    }
    
}

// O(N) nothrow
template <typename T>
void vector<T>::clear() noexcept {
    for (size_t i = 0; i < _size; i++)
    {
        _data[i].~T();
    }

    _size = 0;
}

// O(1) nothrow
//   void swap(vector& other) noexcept;

// O(1) nothrow
template <typename T>
T* vector<T>::begin() noexcept {
    return _data;
}

template <typename T>
T* vector<T>::end() noexcept {
    return _data + _size;
}

template <typename T>
const T* vector<T>::begin() const noexcept {
    return _data;
}

template <typename T>
const T* vector<T>::end() const noexcept {
    return _data + _size;
}

template <typename T>
T* vector<T>::insert(const T* pos, const T& value) {
  if (empty()) {
    push_back(value);
    return begin();
  }

  size_t idx = pos - _data;

  size_t new_capacity = 0;
  if (_capacity < _size + 1) {
    new_capacity = _capacity * 2;
  }

  if (new_capacity > 0) {

    // reserve
    
    T* new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));

    size_t copied = 0;
    try {
        for (size_t i = 0; i < idx; i++) {
            new (new_data + i) T(_data[i]);
            copied++;
        }
        new (new_data + idx) T(value);
        copied++;
        for (size_t i = _size; i > idx; i--) {
            new (new_data + i) T(_data[i-1]);
            copied++;
        }

    } catch (...) {
        for (size_t i = 0; i < copied; i++) {
            new_data[i].~T();
        }
        operator delete(new_data);
        throw;
    }
    
    for (size_t i = 0; i < _size; i++) {
        _data[i].~T();
    }

    operator delete(_data);
    
    //printf("reserved %lu\n", new_capacity);
    _capacity = new_capacity;
    _data = new_data;

    // end reserve

  } else {

    new (_data + _size) T(value);

    for (size_t i = _size; i > idx; i--) {
        _data[i].~T();
        new (_data + i) T(_data[i - 1]);
    }

    _data[idx].~T();
    new (_data + idx) T(value);

  }

  _size++;
  return _data + idx;
}

template <typename T>
T* vector<T>::erase(const T* pos) {
    if (empty()) {
        return nullptr;
    }

    size_t idx = pos - _data;

    for (size_t i = idx; i < _size - 1; i++) {
        _data[i] = _data[i+1];
    }
    _data[_size-1].~T();

    _size--;

    return _data + idx;
}

template <typename T>
T* vector<T>::erase(const T* first, const T* last) {
    if (empty()) {
        return nullptr;
    }

    /*
    
    10   20   30   40   50   60   70   75   80
    21   22   23   24   25   26   27   28   29

    10   20    70    75   80
    21   22    23    24   25 

    size = 30

    first = 23
    last = 26
    EC (erase count) = last - first + 1 = 26-23+1 = 4
    to = size - EC = 30 - 4 = 26

    data[first] = data[first + EC]
          23             27
          24             28
          25             29

    for (i = to ... size):
        ~T()

    
    */

    size_t first_i = first - _data;
    size_t last_i = last - _data;

    size_t ec = last_i - first_i, erase_to = _size - ec;

    for (size_t i = first_i; i < erase_to; i++) {
        _data[i] = _data[i + ec];
    }

    for (size_t i = erase_to; i < _size; i++) {
        _data[i].~T();
    }

    _size -= ec;

    return _data + first_i;
}

