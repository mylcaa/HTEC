#include <gtest/gtest.h>
#include "LinkedList.h"

class LinkedListTest : public testing::Test {
 protected:
  LinkedList<int> l0_;
  LinkedList<float> l1_{1, 3, 5, 7, 9};

  LinkedListTest() {}
  
};


TEST_F(LinkedListTest, isEmptyInitially)
{
    EXPECT_EQ(l0_.getSize(), 0);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}