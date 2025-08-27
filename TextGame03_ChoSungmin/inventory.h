#pragma once
#include <functional>
#include <cstddef>
#include <algorithm>


template <typename T>
class Inventory
{
public:
    using GrowthPolicy = std::function<int(int)>;

    // 생성자
    explicit Inventory(int capacity = 10);
    Inventory(int capacity, GrowthPolicy policy);


    ~Inventory();
    Inventory(const Inventory& other);
    Inventory& operator=(const Inventory& other);
    void Assign(const Inventory& other);

    // 크기/용량
    int GetSize() const;
    int GetCapacity() const;

    // 인덱싱 
    T& operator[](int idx);
    const T& operator[](int idx) const;

    // 반복자
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
    const T* cbegin() const;
    const T* cend() const;

    // 용량 조정
    bool Resize(int newCapacity);

    // 성장 정책 주입
    void SetGrowthPolicy(GrowthPolicy policy);

    // 수정 연산
    void AddItem(const T& item);
    bool RemoveLastItem();

    // 정렬
    void SortItems();

    // 정렬
    template <typename Compare>
    void SortItems(Compare comp)
    {
        std::sort(begin(), end(), comp);
    }

    // 순회
    template <typename Func>
    void ForEach(Func f) const
    {
        for (int i = 0; i < size_; ++i) f(pItems_[i]);
    }

private:
    T* pItems_ = nullptr;
    int capacity_ = 0;
    int size_ = 0;
    GrowthPolicy grow_;
};