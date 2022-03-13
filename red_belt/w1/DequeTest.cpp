#include <iostream>

#include "Deque.h"
#include "test_runner.h"

void TestAt() {

    Deque<int> deq;

    deq.PushBack(5);
    try {
        deq.At(1);
        ASSERT_EQUAL(false, true);
    }
    catch (std::out_of_range &) {
        ASSERT_EQUAL(true, true);
    }
    ASSERT_EQUAL(deq.At(0), 5);
    auto &r = deq.At(0);
    r = 10;
    ASSERT_EQUAL(deq.At(0), 10);

    // const
    const auto &dref = deq;
    ASSERT_EQUAL(dref.At(0), 10);
}

void TestFrontBackEmpty() {
    Deque<std::string> deq;

    ASSERT_EQUAL(deq.Empty(), true);
    deq.PushBack("middle2");
    deq.PushBack("back");
    deq.PushFront("middle1");
    deq.PushFront("front");
    ASSERT_EQUAL(deq.Size(), 4);
    ASSERT_EQUAL(deq.At(1), "middle1");
    ASSERT_EQUAL(deq[2], "middle2");

    ASSERT_EQUAL(deq.Front(), "front");
    ASSERT_EQUAL(deq.Back(), "back");

    // const
    const auto& dref = deq;
    ASSERT_EQUAL(dref.Front(), "front");
    ASSERT_EQUAL(dref.Back(), "back");
}

void TestGetSet() {
    Deque<int> deq;

    deq.PushBack(3);
    deq.PushBack(4);
    deq.PushBack(5);
    deq.PushFront(2);
    deq.PushFront(1);

    ASSERT_EQUAL(deq.Size(), 5);

    std::stringstream ss;
    const auto& dref = deq;
    for (int i = 0; i < deq.Size(); ++i) {
        ss << dref[i];
    }
    ASSERT_EQUAL(ss.str(), "12345");

    const auto& dref2 = deq[2];
    ASSERT_EQUAL(dref2, 3);

    auto& dref3 = deq[2];
    dref3 = 0;
    ASSERT_EQUAL(dref3, 0);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestAt);
    RUN_TEST(tr, TestFrontBackEmpty);
    RUN_TEST(tr, TestGetSet);
}
