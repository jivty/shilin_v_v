#include "dynarray.h"
#include <iostream>

DynArray::DynArray(const DynArray& arr)
  : size_(arr.size_)
  , capacity_(arr.capacity_)
  , data_ (new float[capacity_]) {
  for (ptrdiff_t i = 0; i < size_; ++i) {
    data_[i] = arr.data_[i];
  }
}

DynArray::DynArray(const ptrdiff_t size) {
  if (size < 0) {
    throw std::invalid_argument("size < 0");
  } else {
    size_ = size;
    capacity_ = size;
    data_ = new float[size];
  }
}

DynArray& DynArray::operator=(const DynArray& rhs) {
  if (this != &rhs) {
    if (size_ <= rhs.size_) {
      for (ptrdiff_t i = 0; i < size_; ++i) {
        data_[i] = rhs.data_[i];
      }
      size_ = rhs.size_;
    } else {
      float* tmpdata_ = new float[rhs.size_];
      for (ptrdiff_t i = 0; i < rhs.size_; ++i) {
        tmpdata_[i] = rhs.data_[i];
      }
      size_ = rhs.size_;
      capacity_ = rhs.capacity_;
      delete[] data_;
      data_ = tmpdata_;
    }
  }
  return *this;
}

DynArray::~DynArray() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

ptrdiff_t DynArray::size() const{
  return size_;
}

ptrdiff_t DynArray::capacity() const{
  return capacity_;
}

float& DynArray::operator[] (const ptrdiff_t index) {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("index is out of range");
  }
  return data_[index];
}

const float& DynArray::operator[] (const ptrdiff_t index) const {
  if (index < 0 || index >= size_) {
    throw std::out_of_range("index is out of range");
  }
  return data_[index];
}

void DynArray::resize(const ptrdiff_t nsize) {
  if (nsize < 0) {
    throw std::invalid_argument("new size is < 0");
  } else {
    if (nsize <= capacity_) {
      size_ = nsize;
    } else {
      float* tmpdata = new float[nsize];
      for (ptrdiff_t i = 0; i < size_; ++i) {
        tmpdata[i] = data_[i];
      }
      delete[] data_;
      data_ = tmpdata;
      size_ = nsize;
      capacity_ = nsize;
    }
  }
}
