#include "pch.h"
#include "ForwardList.h"
#include <iostream>

TEST(List, List)
{
	ForwardList<int> list;
	ASSERT_TRUE(list.size() == 0);
	ASSERT_THROW(list.first(), std::runtime_error);
}

TEST(List, last)
{
	ForwardList<int> list;
	ASSERT_THROW(list.last(), std::runtime_error);
	list.push_front(5);
	list.push_front(7);
	list.push_front(9);
	ASSERT_TRUE(list.last() != nullptr);
}

TEST(List, first)
{
	ForwardList<int> list;
	ASSERT_THROW(list.first(), std::runtime_error);
	list.push_front(5);
	list.push_front(7);
	list.push_front(9);
	ASSERT_TRUE(list.first() != nullptr);
}

TEST(List, push_front)
{
	ForwardList<int> list;
	list.push_front(5);
	list.push_front(7);
	list.push_front(9);
	ASSERT_TRUE(list.size() == 3);
	ASSERT_NO_THROW(list.first());
	ASSERT_EQ(list.get(0), 9);
	ASSERT_EQ(list.get(1), 7);
	ASSERT_EQ(list.get(2), 5);
}

TEST(List, insert_after)
{
	ForwardList<int> list;
	list.push_front(5);
	list.push_front(7);
	list.push_front(9);
	list.insert_after(list.first(), 11);
	ASSERT_EQ(list.get(0), 9);
	ASSERT_EQ(list.get(1), 11);
	ASSERT_EQ(list.get(2), 7);
	ASSERT_EQ(list.get(3), 5);
}

TEST(List, push_back)
{
	ForwardList<int> list;
	list.push_back(5);
	list.push_back(7);
	list.push_back(9);
	ASSERT_TRUE(list.size() == 3);
	ASSERT_NO_THROW(list.first());
	ASSERT_EQ(list.get(0), 5);
	ASSERT_EQ(list.get(1), 7);
	ASSERT_EQ(list.get(2), 9);
}

TEST(List, remove)
{
	ForwardList<int> list;
	list.push_back(5);
	list.push_back(7);
	list.push_back(9);

	list.remove(1);
	ASSERT_EQ(list.get(0), 5);
	ASSERT_EQ(list.get(1), 7);
	ASSERT_EQ(list.get(2), 9);

	list.remove(7);
	ASSERT_EQ(list.size(), 2);
	ASSERT_EQ(list.get(0), 5);
	ASSERT_EQ(list.get(1), 9);

	list.remove(9);
	ASSERT_EQ(list.size(), 1);
	ASSERT_EQ(list.get(0), 5);

	list.remove(5);
	ASSERT_EQ(list.size(), 0);
	ASSERT_TRUE(list.empty());
}


TEST(List, pop_front)
{
	ForwardList<int> list;
	list.push_front(5);
	list.push_front(7);
	list.push_front(9);
	list.pop_front();
	ASSERT_TRUE(list.size() == 2);
	ASSERT_NO_THROW(list.first());
	ASSERT_EQ(list.get(0), 7);
	ASSERT_EQ(list.get(1), 5);
}

TEST(List, clear)
{
	ForwardList<int> list;
	list.push_front(5);
	list.push_front(7);
	list.push_front(9);
	list.clear();
	ASSERT_EQ(list.size(), 0);
	ASSERT_TRUE(list.empty());
}

TEST(List, reverse)
{
	ForwardList<int> list;
	list.push_front(5);
	list.push_front(7);
	list.push_front(9);
	list.reverse();
	ASSERT_EQ(list.size(), 3);
	ASSERT_EQ(list.get(0), 5);
	ASSERT_EQ(list.get(1), 7);
	ASSERT_EQ(list.get(2), 9);
}


TEST(List, Copy)
{
	ForwardList<int> list;
	list.push_front(5);
	list.push_front(7);
	list.push_front(9);
	ForwardList<int> list1(list);
	ASSERT_EQ(list.size(), 3);
	ASSERT_EQ(list1.get(0), 5);
	ASSERT_EQ(list1.get(1), 7);
	ASSERT_EQ(list1.get(2), 9);
}

TEST(List, OperatorEqual)
{
	ForwardList<int> list;
	list.push_front(5);
	list.push_front(7);
	list.push_front(9);
	ForwardList<int> list1;
	list1.push_front(5);
	list1.push_front(7);
	list1.push_front(9);
	ASSERT_TRUE(list == list1);
}
TEST(List, NewOperator)
{
	ForwardList<int> list1;
	list1.push_front(5);
	list1.push_front(7);
	list1.push_front(9);
	ForwardList<int> list2;
	list2.push_front(4);
	list2.push_front(3);
	list1 += list2;
	ASSERT_EQ(5, list1.size());
	ASSERT_TRUE(list2.empty());

}