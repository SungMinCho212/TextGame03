#pragma once
#include <functional>
#include <cstddef>
#include <algorithm>


template <typename T>
class Inventory
{
public:
    using GrowthPolicy = std::function<int(int)>;

    // ������
    explicit Inventory(int capacity = 10);
    Inventory(int capacity, GrowthPolicy policy);


    ~Inventory();
    Inventory(const Inventory& other);
    Inventory& operator=(const Inventory& other);
    void Assign(const Inventory& other);

    // ũ��/�뷮
    int GetSize() const;
    int GetCapacity() const;

    // �ε��� 
    T& operator[](int idx);
    const T& operator[](int idx) const;

    // �ݺ���
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
    const T* cbegin() const;
    const T* cend() const;

    // �뷮 ����
    bool Resize(int newCapacity);

    // ���� ��å ����
    void SetGrowthPolicy(GrowthPolicy policy);

    // ���� ����
    void AddItem(const T& item);
    bool RemoveLastItem();

    // ����
    void SortItems();

    // ����
    template <typename Compare>
    void SortItems(Compare comp)
    {
        std::sort(begin(), end(), comp);
    }

    // ��ȸ
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