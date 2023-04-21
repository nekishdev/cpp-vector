#pragma once

#include <cstddef>

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

public:
  vector();                                                  // O(1) nothrow
  vector(const vector& other);                               // O(N) strong
  vector& operator=(const vector& other);                    // O(N) strong

  ~vector();                                                 // O(N) nothrow

  reference operator[](size_t index);                        // O(1) nothrow
  const_reference operator[](size_t index) const;            // O(1) nothrow

  pointer data();                                            // O(1) nothrow
  const_pointer data() const;                                // O(1) nothrow

  size_t size() const;                                       // O(1) nothrow

  reference front();                                         // O(1) nothrow
  const_reference front() const;                             // O(1) nothrow

  reference back();                                          // O(1) nothrow
  const_reference back() const;                              // O(1) nothrow

  void push_back(const T& value);                            // O(1)* strong

  void pop_back();                                           // O(1) nothrow

  bool empty() const;                                        // O(1) nothrow

  size_t capacity() const;                                   // O(1) nothrow
  void reserve(size_t new_capacity);                         // O(N) strong
  void shrink_to_fit();                                      // O(N) strong

  void clear();                                              // O(N) nothrow

  void swap(vector& other);                                  // O(1) nothrow

  iterator begin();                                          // O(1) nothrow
  iterator end();                                            // O(1) nothrow

  const_iterator begin() const;                              // O(1) nothrow
  const_iterator end() const;                                // O(1) nothrow

  iterator insert(const_iterator pos, const_iterator value); // O(N) strong

  iterator erase(const_iterator pos);                        // O(N) nothrow(swap)

  iterator erase(const_iterator first, const_iterator last); // O(N) nothrow(swap)
};
