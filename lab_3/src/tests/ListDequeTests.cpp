#include <cassert>
#include <iostream>
#include "./include/Deque/ListDeque.hpp"

void testListDeque() {
    // Тест конструкторов
    {
        ListDeque<int> d1;
        assert(d1.IsEmpty());
        
        int items[] = {1, 2, 3};
        ListDeque<int> d2(items, 3);
        assert(d2.GetSize() == 3);
        assert(d2.GetFront() == 1);
        assert(d2.GetBack() == 3);
        
        ListDeque<int> d3(d2);
        assert(d3.GetSize() == 3);
        
        ListDeque<int> d4(std::move(d2));
        assert(d4.GetSize() == 3);
        assert(d2.IsEmpty());
    }

    // Тест операций
    {
        ListDeque<int> d;
        
        // Добавление 1000 элементов в начало
        for (int i = 0; i < 1000; ++i) {
            d.PushFront(i);
            assert(d.GetFront() == i);
        }
        
        // Проверка порядка
        for (int i = 999; i >= 0; --i) {
            assert(d.PopFront() == i);
        }
        assert(d.IsEmpty());
        
        // Добавление 1000 элементов в конец
        for (int i = 0; i < 1000; ++i) {
            d.PushBack(i);
            assert(d.GetBack() == i);
        }
        
        // Проверка порядка
        for (int i = 0; i < 1000; ++i) {
            assert(d.PopFront() == i);
        }
        assert(d.IsEmpty());
    }

    // Тест операторов
    {
        ListDeque<int> d1;
        for (int i = 0; i < 100; ++i) {
            d1.PushBack(i);
        }
        
        ListDeque<int> d2 = d1;
        assert(d2.GetSize() == 100);
        
        ListDeque<int> d3 = std::move(d1);
        assert(d3.GetSize() == 100);
        assert(d1.IsEmpty());
    }

    std::cout << "All ListDeque tests passed!\n";
}