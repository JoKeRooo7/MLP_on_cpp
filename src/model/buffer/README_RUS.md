
### class Buffer

Шаблонный класс, принимает тип данных, который будет храниться в очереди.

```cpp
    s21::Buffer<int> my_buffer;
```

Ограничение размера буфера. (размера очереди):
```cpp
    void SetMaxBufferSize(USInt size);
    ...
    my_buffer.SetMaxBufferSize(15);
```

Функция для вставки значений в буфер, вызывает исключение, если буфер переполнен:
```cpp
    void SetData(const TypeData& var);
    ...
    my_buffer.SetData(var);
```

Открытие, закрытие и очистка буфера:
```cpp
    void Open();
    void Close();
    void Clear();
```

Проверка на открытие и закрытие буфера:
```cpp
    bool IsOpen();
    bool IsClose();
```

Возращает максимальное значение данных в очереди(в буфере):
```cpp
    unsigned short int GetMaxBufferSize();
```

Возращает текущий размер буфера:
```cpp
    std::size_t GetSize();
```

Полное получение коопии очереди:
```cpp
    template<typenameT>
    std::queue<T> GetData();

```

Получение копии елемента у буфера и его удаление:
```cpp
    template <typename T>
    T TakeElement();
    ...
    typedef int MyType;
    MyType var_one;
    var_one = my_buffer.TakeElement();
```
