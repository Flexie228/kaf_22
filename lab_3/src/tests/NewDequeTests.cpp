#include <cassert>
#include <iostream>
#include "./include/Deque/NewDeque.hpp"

void testNewDeque() {
    // Тест конструкторов
    {
        NewDeque<int> d1;
        assert(d1.IsEmpty());
        
        int items[] = {1, 2, 3};
        NewDeque<int> d2(items, 3);
        assert(d2.GetSize() == 3);
        assert(d2.GetFront() == 1);
        assert(d2.GetBack() == 3);
        
        NewDeque<int> d3(d2);
        assert(d3.GetSize() == 3);
        
        NewDeque<int> d4(std::move(d2));
        assert(d4.GetSize() == 3);
        assert(d2.IsEmpty());
    }

    // Тест операций
    {
        NewDeque<int> d;
        
        // Добавление 100 элементов в начало
        for (int i = 0; i < 100; ++i) {
            d.PushFront(i);
            assert(d.GetFront() == i);
            assert(d.GetSize() == i + 1);
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

    // Тест операторов
    {
        NewDeque<int> d1;
        for (int i = 0; i < 10; ++i) {
            d1.PushBack(i);
        }
        
        NewDeque<int> d2 = d1;
        assert(d2.GetSize() == 10);
        
        NewDeque<int> d3 = std::move(d1);
        assert(d3.GetSize() == 10);
        assert(d1.IsEmpty());
    }

    // Тест граничных случаев
    {
        NewDeque<int> d;
        bool error = false;
        
        try { d.PopFront(); } 
        catch (...) { error = true; }
        assert(error);
        
        error = false;
        try { d.GetFront(); } 
        catch (...) { error = true; }
        assert(error);
    }

    std::cout << "All NewDeque tests passed!\n";
}