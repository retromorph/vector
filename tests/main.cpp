#include "../src/vector.hpp"
#include <iostream>
#include <cassert>
#include <string>

void test_default_constructor() {
    Vector<int> vec;
    assert(vec.size() == 0);
    assert(vec.capacity() == 0);
    assert(vec.empty());
    std::cout << "Default constructor test passed" << std::endl;
}

void test_push_back_and_resize() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    assert(vec.size() == 3);
    assert(vec[0] == 1);
    assert(vec[1] == 2);
    assert(vec[2] == 3);

    vec.resize(5, 10);
    assert(vec.size() == 5);
    assert(vec[3] == 10);
    assert(vec[4] == 10);

    vec.resize(2);
    assert(vec.size() == 2);

    std::cout << "Push back and resize test passed" << std::endl;
}

void test_pop_back() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    vec.pop_back();
    assert(vec.size() == 1);
    assert(vec[0] == 1);

    vec.pop_back();
    assert(vec.empty());

    std::cout << "Pop back test passed" << std::endl;
}

void test_copy_constructor() {
    Vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);

    Vector<int> vec2 = vec1;
    assert(vec2.size() == vec1.size());
    assert(vec2[0] == 1);
    assert(vec2[1] == 2);

    vec2.push_back(3);
    assert(vec1.size() == 2);

    std::cout << "Copy constructor test passed" << std::endl;
}

void test_move_constructor() {
    Vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);

    Vector<int> vec2 = std::move(vec1);
    assert(vec2.size() == 2);
    assert(vec2[0] == 1);
    assert(vec2[1] == 2);
    assert(vec1.size() == 0);

    std::cout << "Move constructor test passed" << std::endl;
}

void test_operator_assignment() {
    Vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);

    Vector<int> vec2;
    vec2 = vec1;
    assert(vec2.size() == vec1.size());
    assert(vec2[0] == 1);
    assert(vec2[1] == 2);

    Vector<int> vec3;
    vec3 = std::move(vec1);
    assert(vec3.size() == 2);
    assert(vec3[0] == 1);
    assert(vec3[1] == 2);
    assert(vec1.size() == 0);

    std::cout << "Operator assignment test passed" << std::endl;
}

void test_accessors() {
    Vector<int> vec = {10, 20, 30};
    assert(vec.front() == 10);
    assert(vec.back() == 30);
    vec[1] = 50;
    assert(vec[1] == 50);

    try {
        vec.at(10);
    } catch (const std::out_of_range& e) {
        std::cout << "Accessors test passed" << std::endl;
        return;
    }

    assert(false);
}

void test_iterator() {
    Vector<int> vec = {1, 2, 3, 4, 5};
    int sum = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
    }
    assert(sum == 15);

    std::cout << "Iterator test passed" << std::endl;
}

void test_clear_and_empty() {
    Vector<int> vec = {1, 2, 3};
    vec.clear();
    assert(vec.empty());
    assert(vec.size() == 0);

    std::cout << "Clear and empty test passed" << std::endl;
}

void test_reserve_and_capacity() {
    Vector<int> vec;
    vec.reserve(10);
    assert(vec.capacity() >= 10);

    vec.push_back(1);
    vec.push_back(2);
    assert(vec.capacity() >= 10);

    std::cout << "Reserve and capacity test passed" << std::endl;
}

void test_string_vector() {
    Vector<std::string> vec;
    vec.push_back("hello");
    vec.push_back("world");

    assert(vec.size() == 2);
    assert(vec[0] == "hello");
    assert(vec[1] == "world");

    std::cout << "String vector test passed" << std::endl;
}

int main() {
    test_default_constructor();
    test_push_back_and_resize();
    test_pop_back();
    test_copy_constructor();
    test_move_constructor();
    test_operator_assignment();
    test_accessors();
    test_iterator();
    test_clear_and_empty();
    test_reserve_and_capacity();
    test_string_vector();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}