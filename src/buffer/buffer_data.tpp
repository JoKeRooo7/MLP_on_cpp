#include "buffer_data.h"

#include <mutex>
#include <queue>
#include <cstddef>
#include <iostream>
#include <stdexcept>


namespace s21 {

template <typename T>
void Buffer<T>::SetMaxBufferSize(USInt size) {
    if (size < 1) {
        throw std::invalid_argument("Not correct buffer size");
    }
    data_size_ = size;
}

template <typename T>
void Buffer<T>::SetData(const TypeData& var) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (close_ == true) {
        throw std::runtime_error("cant set buffer");
    }
    data_.push(var);
    cv_.notify_one();
}

template <typename T>
void Buffer<T>::Open() {
    close_ = false;
}

template <typename T>
void Buffer<T>::Close() {
    std::lock_guard<std::mutex> lock(mutex_);
    close_ = true;
    cv_.notify_all();
}

template <typename T>
void Buffer<T>::Clear() {
    while (data_.size() >= 1) {
        data_.pop();
    }
    close_ = false;
}

template <typename T>
bool Buffer<T>::IsOpen() {
    return (close_ == false) ? true : false;
}

template <typename T>
bool Buffer<T>::IsClose() {
    return close_;
}

template <typename T>
typename Buffer<T>::USInt Buffer<T>::GetMaxBufferSize() {
    return data_size_;
}

template <typename T>
std::size_t Buffer<T>::GetSize() {
    return data_.size();
}

template <typename T>
std::queue<T> Buffer<T>::GetData() {
    return data_;
}

template <typename T>
T Buffer<T>::TakeElement() {
    std::unique_lock<std::mutex> lock(mutex_);
    if (close_) {
        throw std::runtime_error("cant take buffer");
    }
    cv_.wait(lock, [this] { return !data_.empty(); });
    T var = data_.front();
    data_.pop();
    return var;
}


}  // namespace s21
