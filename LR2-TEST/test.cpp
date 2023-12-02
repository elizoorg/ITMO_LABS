#include "pch.h"
#include "Array.h"
#include <gtest/gtest.h>

TEST(TestCaseName, CreateArray) {
	Array<int> array(5);
	EXPECT_EQ(array.size(), 5);
}
TEST(TestCaseName, ArrayExpansion) {
	Array<int> array(5);
	array.insert(1);
	array.insert(1);
	array.insert(1);
	array.insert(1);
	array.insert(1);
	array.insert(1);
	EXPECT_EQ(array.size(),10);
}
TEST(TestCaseName, ForwardIterator) {
	Array<int> array(5);
	array.insert(1);
	array.insert(1);
	array.insert(1);
	array.insert(1);
	array.insert(1);
	auto it = array.iterator();
	int a = *it;
	EXPECT_EQ(a,1);
}
TEST(TestCaseName, ForwardIterator2) {
	Array<int> array(5);
	array.insert(1);
	array.insert(2);
	array.insert(3);
	array.insert(4);
	array.insert(5);
	auto it = array.iterator();
	it++;
	int a = *it;
	EXPECT_EQ(a, 2);
}

TEST(TestCaseName, ReverseIterator) {
	Array<int> array(5);
	array.insert(1);
	array.insert(2);
	array.insert(3);
	array.insert(4);
	array.insert(5);
	auto itr2 = array.reverseIterator();
	itr2.next();
	itr2.next();
	itr2.next();
	itr2.next();
	EXPECT_EQ(*itr2, 1);
}

TEST(TestCaseName, CreateArrayString) {
	Array<std::string> array(5);
	EXPECT_EQ(array.size(), 5);
}
TEST(TestCaseName, ArrayExpansionString) {
	Array<std::string> array(5);
	array.insert("a");
	array.insert("b");
	array.insert("c");
	array.insert("d");
	array.insert("e");
	array.insert("f");
	EXPECT_EQ(array.size(), 10);
}

TEST(TestCaseName, ForwardIteratorString) {
	Array<std::string> array(5);
	array.insert("a");
	array.insert("b");
	array.insert("c");
	array.insert("d");
	array.insert("e");
	auto it = array.iterator();
	std::string a = *it;
	EXPECT_EQ(a, "a");
}
TEST(TestCaseName, ForwardIteratorString2) {
	Array<std::string> array(5);
	array.insert("a");
	array.insert("b");
	array.insert("c");
	array.insert("d");
	array.insert("e");
	auto it = array.iterator();
	it++;
	std::string a = *it;
	EXPECT_EQ(a, "b");
}

TEST(TestCaseName, ReverseIteratorString) {
	Array<std::string> array(5);
	array.insert("a");
	array.insert("b");
	array.insert("c");
	array.insert("d");
	array.insert("e");
	Array<std::string>::Iterator itr2 = array.reverseIterator();
	itr2.next();
	itr2.next();
	itr2.next();
	itr2.next();
	EXPECT_EQ(*itr2, "a");
}

TEST(TestCaseName, InitializerListString) {
	Array<std::string> array{"a","b","c","d","e"};
	Array<std::string>::Iterator itr2 = array.reverseIterator();
	itr2.next();
	itr2.next();
	itr2.next();
	itr2.next();
	EXPECT_EQ(*itr2, "a");
}

TEST(TestCaseName, CopyCtor) {

	Array<std::string> array{ "a","b","c","d","e" };
	Array<std::string> array2(array);
	EXPECT_EQ(array2.size(), 5);
}

TEST(TestCaseName,MoveCtor) {

	Array<std::string> array{ "a","b","c","d","e" };
	Array<std::string> array2(std::move(array));
	EXPECT_EQ(array2.size(), 5);
}

TEST(TestCaseName, CopyAssign) {

	Array<std::string> array{ "a","b","c","d","e" };
	Array<std::string> array2;
	array2 = array;
	EXPECT_EQ(array2.size(), 5);
}

TEST(TestCaseName, MoveAssign) {

	Array<std::string> array{ "a","b","c","d","e" };
	Array<std::string> array2;
	array2 = std::move(array);
	EXPECT_EQ(array2.size(), 5);
}


TEST(TestCaseName, ArrayExpandString) {
	Array<std::string> array(5);
	array.insert("a");
	array.insert("b");
	array.insert("c");
	array.insert("d");
	array.insert("e");
	array.insert("f");
	Array<std::string>::Iterator itr2 = array.reverseIterator();
	itr2.next();
	itr2.next();
	itr2.next();
	itr2.next();
	itr2.next();
	EXPECT_EQ(*itr2, "a");
	EXPECT_EQ(array.size(),10);
}