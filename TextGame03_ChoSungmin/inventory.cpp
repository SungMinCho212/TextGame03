#include "inventory.h"
#include "item.h"   
#include <utility>
#include <new>


namespace 
{
    template <typename T>
    void CopyRange(T* dst, const T* src, int n) 
    {
        for (int i = 0; i < n; ++i) dst[i] = src[i];
    }

    // 기본 성장 정책: 2배 확장
    inline int DefaultDoubling(int c) 
    {
        return (c <= 0) ? 1 : c * 2;
    }
}

// 생성자들
template <typename T>
Inventory<T>::Inventory(int capacity)
    : capacity_(capacity > 0 ? capacity : 1), size_(0), grow_(DefaultDoubling) 
{
    pItems_ = new T[capacity_];
}

template <typename T>
Inventory<T>::Inventory(int capacity, GrowthPolicy policy)
    : capacity_(capacity > 0 ? capacity : 1), size_(0), grow_(policy ? policy : GrowthPolicy(DefaultDoubling)) 
{
    pItems_ = new T[capacity_];
}

// 소멸자
template <typename T>
Inventory<T>::~Inventory() 
{
    delete[] pItems_;
    pItems_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}

// 복사 생성자
template <typename T>
Inventory<T>::Inventory(const Inventory& other)
    : capacity_(other.capacity_), size_(other.size_), grow_(other.grow_) 
{
    pItems_ = new T[capacity_];
    CopyRange(pItems_, other.pItems_, size_);
}

// 대입 연산자
template <typename T>
Inventory<T>& Inventory<T>::operator=(const Inventory& other) 
{
    Assign(other);
    return *this;
}

// Assign
template <typename T>
void Inventory<T>::Assign(const Inventory& other) 
{
    if (this == &other) return;

    if (other.capacity_ != capacity_) {
        T* newBuf = new T[other.capacity_];
        delete[] pItems_;
        pItems_ = newBuf;
        capacity_ = other.capacity_;
    }
    size_ = other.size_;
    grow_ = other.grow_;
    CopyRange(pItems_, other.pItems_, size_);
}

// 접근자
template <typename T>
int Inventory<T>::GetSize() const { return size_; }

template <typename T>
int Inventory<T>::GetCapacity() const { return capacity_; }

template <typename T>
T& Inventory<T>::operator[](int idx) { return pItems_[idx]; }

template <typename T>
const T& Inventory<T>::operator[](int idx) const { return pItems_[idx]; }

// 반복자
template <typename T>
T* Inventory<T>::begin() { return pItems_; }

template <typename T>
T* Inventory<T>::end() { return pItems_ + size_; }

template <typename T>
const T* Inventory<T>::begin() const { return pItems_; }

template <typename T>
const T* Inventory<T>::end() const { return pItems_ + size_; }

template <typename T>
const T* Inventory<T>::cbegin() const { return pItems_; }

template <typename T>
const T* Inventory<T>::cend() const { return pItems_ + size_; }


template <typename T>
bool Inventory<T>::Resize(int newCapacity) 
{
    if (newCapacity < size_) return false;
    if (newCapacity == capacity_) return true;

    T* newBuf = new (std::nothrow) T[newCapacity];
    if (!newBuf) return false;

    for (int i = 0; i < size_; ++i) newBuf[i] = std::move(pItems_[i]);

    delete[] pItems_;
    pItems_ = newBuf;
    capacity_ = newCapacity;
    return true;
}


template <typename T>
void Inventory<T>::SetGrowthPolicy(GrowthPolicy policy) 
{
    grow_ = policy ? policy : GrowthPolicy(DefaultDoubling);
}

// AddItem
template <typename T>
void Inventory<T>::AddItem(const T& item) 
{
    if (size_ == capacity_) {
        int nextCap = grow_ ? grow_(capacity_) : DefaultDoubling(capacity_);
        if (nextCap < size_ + 1) nextCap = size_ + 1; // 안전 보정
        Resize(nextCap);
    }
    pItems_[size_++] = item;
}

// RemoveLastItem
template <typename T>
bool Inventory<T>::RemoveLastItem() 
{
    if (size_ == 0) return false;
    --size_;
    return true;
}

// SortItems 
template <typename T>
void Inventory<T>::SortItems() 
{
    std::sort(begin(), end());
}


template class Inventory<Item>;
template class Inventory<Weapon>;
template class Inventory<Potion>;
