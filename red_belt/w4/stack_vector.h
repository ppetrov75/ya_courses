#pragma once

#include <array>
#include <stdexcept>

using namespace std;

template<typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0) : m_size(a_size) {
        if (a_size > N)
            throw invalid_argument("max size exceeded");
    }

    T &operator[](size_t index) {
        return m_data[index];
    }

    const T &operator[](size_t index) const {
        return m_data[index];
    }

    T *begin() {
        return m_data;
    }

    T *end() {
        return m_data[m_size];
    }

    const T *begin() const {
        return m_data;
    }

    const T *end() const {
        return m_data[m_size];
    }

    size_t Size() const {
        return m_size;
    }

    size_t Capacity() const {
        return N;
    }

    void PushBack(const T &value) {
        if (m_size == N) {
            throw overflow_error("no more memory");
        }
        m_data[m_size++] = value;
    }

    T PopBack() {
        if (!m_size) {
            throw underflow_error("no data");
        }
        return m_data[--m_size];
    }

private:
    array<T, N> m_data;
    size_t m_size;
};