#include "inventory.h"
#include "item.h"
#include <iostream>

int main() {
    std::cout << "[Inventory<Item>]\n";
    Inventory<Item> inv(2);
    inv.AddItem(Item{ "포션", 15 });
    inv.AddItem(Item{ "해독제", 25 });
    inv.AddItem(Item{ "폭탄", 40 }); // 자동 확장

    std::cout << "Size: " << inv.GetSize() << ", Cap: " << inv.GetCapacity() << "\n";

    std::cout << "\n[가격 오름차순 정렬]\n";
    inv.SortItems(compareItemsByPrice);
    inv.ForEach([](const Item& it) { it.PrintInfo(); });

    std::cout << "\n[RemoveLastItem]\n";
    if (!inv.RemoveLastItem()) std::cout << "비어 있음\n";
    inv.ForEach([](const Item& it) { it.PrintInfo(); });

    std::cout << "\n[복사/대입]\n";
    Inventory<Item> copied(inv);
    Inventory<Item> another(1);
    another = inv;
    copied.ForEach([](const Item& it) { it.PrintInfo(); });
    another.ForEach([](const Item& it) { it.PrintInfo(); });

    std::cout << "\n[Inventory<Weapon>]\n";
    Inventory<Weapon> wInv;
    wInv.AddItem(Weapon{ "롱소드", 15, 120 });
    wInv.AddItem(Weapon{ "활", 8, 80 });
    wInv.AddItem(Weapon{ "대검", 25, 300 });
    wInv.SortItems(); // operator< 사용
    wInv.ForEach([](const Weapon& w) { w.PrintInfo(); });

    std::cout << "\n[Inventory<Potion>]\n";
    Inventory<Potion> pInv(1);
    pInv.AddItem(Potion{ "하이포션", 50, 120 });
    pInv.AddItem(Potion{ "메가포션", 100, 300 });
    pInv.ForEach([](const Potion& p) { p.PrintInfo(); });

    return 0;
}
