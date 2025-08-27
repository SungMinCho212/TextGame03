#pragma once
#include <string>
#include <iostream>
#include <utility>

class Item {
    std::string name_;
    int price_;
public:
    Item() : name_("Unknown"), price_(0) {}
    Item(std::string name, int price) : name_(std::move(name)), price_(price) {}

    int GetPrice() const { return price_; }
    const std::string& GetName() const { return name_; }

    void PrintInfo() const {
        std::cout << "[이름: " << name_ << ", 가격: " << price_ << "G]\n";
    }

    bool operator<(const Item& rhs) const {
        if (name_ != rhs.name_) return name_ < rhs.name_;
        return price_ < rhs.price_;
    }
};

class Weapon 
{
    std::string name_;
    int damage_;
    int price_;
public:
    Weapon() : name_("Basic Sword"), damage_(1), price_(10) {}
    Weapon(std::string name, int damage, int price)
        : name_(std::move(name)), damage_(damage), price_(price)  { }

    int GetPrice() const { return price_; }
    int GetDamage() const { return damage_; }

    void PrintInfo() const 
    {
        std::cout << "[무기: " << name_ << ", 공격력: " << damage_
            << ", 가격: " << price_ << "G]\n";
    }

    bool operator<(const Weapon& rhs) const 
    {
        if (damage_ != rhs.damage_) return damage_ < rhs.damage_;
        return price_ < rhs.price_;
    }
};

class Potion
{
    std::string name_;
    int heal_;
    int price_;
public:
    Potion() : name_("Small Potion"), heal_(10), price_(5) {}
    Potion(std::string name, int heal, int price)
        : name_(std::move(name)), heal_(heal), price_(price) {}

    int GetPrice() const { return price_; }
    int GetHeal() const { return heal_; }

    void PrintInfo() const 
    {
        std::cout << "[포션: " << name_ << ", 회복: " << heal_
            << ", 가격: " << price_ << "G]\n";
    }

    bool operator<(const Potion& rhs) const 
    {
        if (heal_ != rhs.heal_) return heal_ < rhs.heal_;
        return price_ < rhs.price_;
    }
};

// 과제 지시안: 가격 오름차순 비교 함수
inline bool compareItemsByPrice(const Item& a, const Item& b) 
{
    return a.GetPrice() < b.GetPrice();
}
