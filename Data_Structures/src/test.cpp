//
// Created by Alex Shockley on 1/23/23.
//
//
// Created by Alex Shockley on 1/30/2022.
//
#include "catch.hpp"
using namespace std;
#include <string>

#include "Linked_List.h"
#include <iostream>
/*
 * Catch tests to make sure that Data Structures function as intended.
 */
TEST_CASE("Linked List") {
    Linked_List<int> int_list;
    Linked_List<string> string_list;
    Linked_List<int *> int_ptr_list;
    for(int i =0; i < 10; i ++) {
        int_list.push_back(i);
        int_ptr_list.push_back(new int(i));
    }
    string_list.push_back("Hello World");
    string_list.push_back("Hello");
    string_list.push_back("World");
    SECTION("Basic construction") {
        CHECK(int_list.get_size() == 10);
        CHECK(string_list.get_size() == 3);
        CHECK(int_ptr_list.get_size() == 10);
        auto a = int_list.pop_back();
        CHECK(a == 9);
        CHECK(int_list.get_size() == 9);

    }
    SECTION("Copy and Assignment Operators") {
        auto b(int_list);
        auto c = int_list;
        //Copy Constructor
        CHECK(b.get_size() == 10);
        CHECK(b.at(0) == 0);
        b.pop_back();
        CHECK(b.get_size() == 9);
        CHECK(b.at(8) == 8);
        //Assignment Operator
        CHECK(int_list.get_size() == 10);
        CHECK(c.get_size() == 10);
        CHECK(c.at(0) == 0);
        c.pop_back();
        CHECK(c.get_size() == 9);
        CHECK(c.at(8) == 8);
        CHECK(int_list.get_size() == 10);

    }
    SECTION("List Traversal") {
        CHECK(int_list.at(0) == 0);
        CHECK(int_list.at(9) == 9);
        CHECK_THROWS(int_list.at(1000));
        CHECK(int_list.at(int_list.get_size() -1) == 9);
        int_list.at(0) = 5000;
        CHECK(int_list.at(0) == 5000);

    }

    SECTION("Removing elements") {
        CHECK(int_list.pop_back() == 9);
        CHECK(int_list.get_size() == 9);
        int_list.remove_at(5);
        CHECK(int_list.get_size() == 8);

    }
    SECTION("Custom Iterator") {
        int val = 0;
        while(int_list.has_next()) {
            CHECK(int_list.get_next() == val);
            val++;
        }

    }
}
