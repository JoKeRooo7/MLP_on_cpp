#include <queue>
#include <stdexcept>
#include <gtest/gtest.h>


#include "../src/buffer/buffer_data.h"


class TestBuffer : public ::testing::Test {
    protected:
        int type_size = 3;
        int data_one[3]  = {1, 2, 3};
        float data_two[3] = {1.1, 2, 3};
};


TEST_F(TestBuffer, SetDataInt) {
    s21::Buffer<int> buffer_data;
    buffer_data.SetData(data_one[0]);
    buffer_data.SetData(data_one[1]);
    buffer_data.SetData(data_one[2]);

    std::queue<int> out_data = buffer_data.GetData();
    EXPECT_EQ(buffer_data.GetSize(), type_size);
    for (unsigned short int i = 0; i < type_size; ++i) {
        EXPECT_EQ(data_one[i], out_data.front());
        out_data.pop();
    }
}

TEST_F(TestBuffer, SetDataFloat) {
    s21::Buffer<float> buffer_data;
    buffer_data.SetData(data_two[0]);
    buffer_data.SetData(data_two[1]);
    buffer_data.SetData(data_two[2]);

    std::queue<float> out_data = buffer_data.GetData();
    EXPECT_EQ(buffer_data.GetSize(), type_size);
    for (unsigned short int i = 0; i < type_size; ++i) {
        EXPECT_NEAR(data_two[i], out_data.front(), 1e-5);
        out_data.pop();
    }
}

TEST_F(TestBuffer, GetEmptyData) {
    s21::Buffer<float> buffer_data;
    buffer_data.GetData();
}
