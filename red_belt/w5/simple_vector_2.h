#pragma once

#include <cstdint>
#include <algorithm>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template<typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size) : m_data(new T[size]), m_capacity(size), m_size(size) {}

    ~SimpleVector() {
        if (m_data)
            delete[] m_data;
    }

    T &operator[](size_t index) {
        return m_data[index];
    }

    T *begin() {
        return m_data;
    }

    T *end() {
        return m_data + m_size;
    }

    size_t Size() const {
        return m_size;
    }

    size_t Capacity() const {
        return m_capacity;
    }

    void PushBack(T value) {
        if (m_data == nullptr) {
            // 2 - unification
            m_data = new T[2];
            m_capacity = 2;
        }

        if (m_size == m_capacity) {
            m_capacity *= 2;
            auto new_data_place = new T[m_capacity];
            std::move(begin(), end(), new_data_place);
            delete[] m_data;
            m_data = new_data_place;
        }

        m_data[m_size++] = std::move(value);
    }

    // При необходимости перегрузите
    // существующие публичные методы

private:
    T* m_data{nullptr};
    size_t m_capacity{0};
    size_t m_size{0};
};
