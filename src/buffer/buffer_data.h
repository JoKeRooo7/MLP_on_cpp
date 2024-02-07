#ifndef CPP7_MLP_1_BUFFER_BUFFER_DATA_H_
#define CPP7_MLP_1_BUFFER_BUFFER_DATA_H_


#include <queue>
#include <mutex>
#include <cstddef>


namespace s21 {

template <typename T>
class Buffer {
    public:
        using USInt = unsigned short int;
        using TypeData = T;

        Buffer() = default;
        ~Buffer() = default;

        void SetMaxBufferSize(USInt size);
        void SetData(const TypeData& var);
        void Open();
        void Close();
        void Clear();

        bool IsOpen();
        bool IsClose();
        USInt GetMaxBufferSize();

        std::size_t GetSize();
        std::queue<TypeData> GetData();
        
        TypeData TakeElement();

    private:
        std::mutex mutex_;
        std::condition_variable cv_; 
        bool close_ = false;
        USInt data_size_ = 5;
        std::queue<TypeData> data_;
};

}  // namespace s21


#include "buffer_data.tpp"


#endif  // CPP7_MLP_1_BUFFER_BUFFER_DATA_H_
