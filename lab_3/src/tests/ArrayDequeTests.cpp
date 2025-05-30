#include <cassert>
#include <iostream>
#include "./include/Deque/ArrayDeque.hpp"

void testArrayDeque() {
    // Тест конструкторов
    {
        ArrayDeque<int> d1;
        assert(d1.IsEmpty());
        
        int items[] = {1, 2, 3};
        ArrayDeque<int> d2(items, 3);
        assert(d2.GetSize() == 3);
        assert(d2.GetFront() == 1);
        assert(d2.GetBack() == 3);
        
        ArrayDeque<int> d3(d2);
        assert(d3.GetSize() == 3);
        
        ArrayDeque<int> d4(std::move(d2));
        assert(d4.GetSize() == 3);
        assert(d2.IsEmpty());
    }

    // Тест операций
    {
        ArrayDeque<int> d;
        
        // Добавление 100 элементов в начало
        for (int i = 0; i < 100; ++i) {
            d.PushFront(i);
            assert(d.GetFront() == i);
        }
        
        // Проверка порядка
        for (int i = 99; i >= 0; --i) {
            assert(d.PopFront() == i);
        }
        assert(d.IsEmpty());
        
        // Добавление 100 элементов в конец
        for (int i = 0; i < 100; ++i) {
            d.PushBack(i);
            assert(d.GetBack() == i);
        }
        
        // Проверка порядка
        for (int i = 0; i < 100; ++i) {
            assert(d.PopFront() == i);
        }
        assert(d.IsEmpty());
    }

    std::cout << "All ArrayDeque tests passed!\n";
}