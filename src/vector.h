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
  // O(1) nothrow
  vector() noexcept;

  // O(N) strong
  vector(const vector& other);

  // O(N) strong
  vector& operator=(const vector& other);

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

  // O(N) strong
  void shrink_to_fit();

  // O(N) nothrow
  void clear() noexcept;

  // O(1) nothrow
  void swap(vector& other) noexcept;

  // O(1) nothrow
  iterator begin() noexcept;

  // O(1) nothrow
  iterator end() noexcept;

  // O(1) nothrow
  const_iterator begin() const noexcept;

  // O(1) nothrow
  const_iterator end() const noexcept;

  // O(N) strong
  iterator insert(const_iterator pos, const T& value);

  // O(N) nothrow(swap)
  iterator erase(const_iterator pos);

  // O(N) nothrow(swap)
  iterator erase(const_iterator first, const_iterator last);
};
