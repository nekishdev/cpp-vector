#pragma once

#include <gtest/gtest.h>

template <typename T>
struct element {
  element() {
    add_instance();
  }

  element(const T& val) : val(val) {
    add_instance();
  }

  element(const element& rhs) : val(rhs.val) {
    copy();
    add_instance();
  }

  element& operator=(const element& rhs) {
    assert_exists();
    rhs.assert_exists();
    copy();
    val = rhs.val;
    return *this;
  }

  ~element() {
    delete_instance();
  }

  static std::unordered_set<const element*>& instances() {
    static std::unordered_set<const element*> instances;
    return instances;
  }

  static void expect_no_instances() {
    if (!instances().empty()) {
      FAIL() << "not all instances are destroyed";
      instances().clear();
    }
  }

  static void set_throw_countdown(size_t val) {
    throw_countdown = val;
  }

  friend bool operator==(const element& a, const element& b) {
    return a.val == b.val;
  }

  friend bool operator!=(const element& a, const element& b) {
    return a.val != b.val;
  }

private:
  void add_instance() {
    auto p = instances().insert(this);
    if (!p.second) {
      FAIL() << "a new object is created at the address " << static_cast<void*>(this)
             << " while the previous object at this address was not destroyed";
    }
  }

  void delete_instance() {
    size_t erased = instances().erase(this);
    if (erased != 1) {
      FAIL() << "attempt of destroying non-existing object at address " << static_cast<void*>(this);
    }
  }

  void assert_exists() const {
    const std::unordered_set<const element*>& inst = instances();
    bool exists = inst.find(this) != inst.end();
    if (!exists) {
      FAIL() << "accessing an non-existsing object at address " << static_cast<const void*>(this);
    }
  }

  void copy() {
    if (throw_countdown != 0) {
      --throw_countdown;
      if (throw_countdown == 0) {
        throw std::runtime_error("copy failed");
      }
    }
  }

private:
  T val;
  inline static size_t throw_countdown = 0;
};
