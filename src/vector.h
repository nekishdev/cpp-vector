#pragma once

#include <cstddef>

template <typename T>
struct vector {
  using iterator = T*;
  using const_iterator = const T*;

  vector();                                                  // O(1) nothrow
  vector(const vector&);                                     // O(N) strong
  vector& operator=(const vector& other);                    // O(N) strong

  ~vector();                                                 // O(N) nothrow

  T& operator[](size_t index);                               // O(1) nothrow
  const T& operator[](size_t index) const;                   // O(1) nothrow

  T* data();                                                 // O(1) nothrow
  const T* data() const;                                     // O(1) nothrow
  size_t size() const;                                       // O(1) nothrow

  T& front();                                                // O(1) nothrow
  const T& front() const;                                    // O(1) nothrow

  T& back();                                                 // O(1) nothrow
  const T& back() const;                                     // O(1) nothrow
  void push_back(const T&);                                  // O(1)* strong
  void pop_back();                                           // O(1) nothrow

  bool empty() const;                                        // O(1) nothrow

  size_t capacity() const;                                   // O(1) nothrow
  void reserve(size_t);                                      // O(N) strong
  void shrink_to_fit();                                      // O(N) strong

  void clear();                                              // O(N) nothrow

  void swap(vector&);                                        // O(1) nothrow

  iterator begin();                                          // O(1) nothrow
  iterator end();                                            // O(1) nothrow

  const_iterator begin() const;                              // O(1) nothrow
  const_iterator end() const;                                // O(1) nothrow

  iterator insert(const_iterator pos, const T&);             // O(N) strong

  iterator erase(const_iterator pos);                        // O(N) nothrow(swap)

  iterator erase(const_iterator first, const_iterator last); // O(N) nothrow(swap)
};
