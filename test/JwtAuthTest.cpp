#include "gtest/gtest.h"

TEST(JwtAuthTest, Auth) {
    ASSERT_FALSE(0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}