#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template<typename T>
class SimpleVector {
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size) : m_data(new T[size]),
                                         m_size(size), m_capacity(size) {
    }

    ~SimpleVector() {
        if (m_capacity == 1)
            // never happened. unification
            delete m_data;
        else
            delete[] m_data;
    }

    T &operator[](size_t index) {
        return m_data[index];
    }

    T *begin() {
        return m_data;
    }

    const T *begin() const {
        return m_data;
    }

    T *end() {
        return m_data + m_size;
    }

    const T *end() const {
        return m_data + m_size;
    }

    size_t Size() const {
        return m_size;
    }

    size_t Capacity() const {
        return m_capacity;
    }

    void PushBack(const T &value) {
        if (m_data == nullptr) {
            // 2 - unification
            m_data = new T[2];
            m_capacity = 2;
        }

        if (m_size == m_capacity) {
            m_capacity *= 2;
            auto new_data_place = new T[m_capacity];
            for (int i = 0; i < m_size; ++i) {
                new_data_place[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data_place;
        }

        m_data[m_size++] = value;
    }

    // swap ?
    SimpleVector &operator=(const SimpleVector &other) {
        if (this != &other) {
            if (m_data && (m_capacity < other.m_capacity) ||
               (m_data == nullptr)) {
                if (m_data)
                    delete[] m_data;
                m_data = new T(other.m_capacity);
                m_capacity = other.m_capacity;
            }
            std::copy(other.begin(), other.end(), begin());
            m_size = other.m_size;
        }
        return *this;
    }

private:
    T *m_data{nullptr};
    size_t m_capacity{0};
    size_t m_size{0};
};
