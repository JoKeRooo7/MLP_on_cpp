## class CSVReader

Класс для чтения файла в отдельном потоке.
```cpp
    s21::CSVReader my_reader;
```

#### Получение количество строк. 
Он ожидает, пока отдельный поток , не посчитает полностью количество строк.
```cpp
    unsigned int GetNumLines();
```

#### Чтение с файла.
Оставляет считывать файл в потоке, и подает данные в буфер([s21::Buffer\<T\>](../buffer/README_RUS.md)), и ожидает пока он не освободиться в течение 5 секунд.
```cpp
    void LoadFile(const std::string& file_name);
```

#### Получение самого буфера.
Возращает ссылочный тип, на тот [буфер](../buffer/README_RUS.md), который использует.
```cpp
    Buffer<T>& GetBuffer();
```

