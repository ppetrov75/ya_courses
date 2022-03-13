#ifndef RED_BELT_DEQUE_H
#define RED_BELT_DEQUE_H

#include <cstddef>
#include <vector>
//#include <deque>

template<typename T>
class Deque {
    std::vector<T> front_vec_;
    std::vector<T> back_vec_;

    const T &at_(size_t index) const {
        range_check_(index);
        return (*this)[index];
    }

    const T &front_() const {
        return front_vec_.empty() ? back_vec_.front() : front_vec_.back();
    }

    const T &back_() const {
        return back_vec_.empty() ? front_vec_.front() : back_vec_.back();
    }

    const T &operator_get(size_t index) const {
        if (index < front_vec_.size())
            return *(front_vec_.rbegin() + index);
        else {
            return back_vec_[index - front_vec_.size()];
        }
    }

protected:
    void range_check_(size_t index) const {
        if (index >= Size())
            throw std::out_of_range("index out of range: " + index);
    }

public:
    Deque() = default;

    bool Empty() const {
        return front_vec_.empty() && back_vec_.empty();
    }

    size_t Size() const {
        return front_vec_.size() + back_vec_.size();
    }

    T &operator[](size_t index) {
        return const_cast<T &>(operator_get(index));
    }

    const T &operator[](size_t index) const {
        return operator_get(index);
    }

    T &At(size_t index) {
        return const_cast<T &>(at_(index));
    }

    const T &At(size_t index) const {
        return at_(index);;
    }

    T &Front() {
        return const_cast<T &>(front_());
    }

    const T &Front() const {
        return front_();
    }

    T &Back() {
        return const_cast<T &>(back_());
    }

    const T &Back() const {
        return back_();
    }

    void PushFront(T x) {
        front_vec_.push_back(x);
    }

    void PushBack(T x) {
        back_vec_.push_back(x);
    }
};

#endif //RED_BELT_DEQUE_H
