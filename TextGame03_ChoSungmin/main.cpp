#include "inventory.h"
#include "item.h"
#include <iostream>

int main() {
    std::cout << "[Inventory<Item>]\n";
    Inventory<Item> inv(2);
    inv.AddItem(Item{ "����", 15 });
    inv.AddItem(Item{ "�ص���", 25 });
    inv.AddItem(Item{ "��ź", 40 }); // �ڵ� Ȯ��

    std::cout << "Size: " << inv.GetSize() << ", Cap: " << inv.GetCapacity() << "\n";

    std::cout << "\n[���� �������� ����]\n";
    inv.SortItems(compareItemsByPrice);
    inv.ForEach([](const Item& it) { it.PrintInfo(); });

    std::cout << "\n[RemoveLastItem]\n";
    if (!inv.RemoveLastItem()) std::cout << "��� ����\n";
    inv.ForEach([](const Item& it) { it.PrintInfo(); });

    std::cout << "\n[����/����]\n";
    Inventory<Item> copied(inv);
    Inventory<Item> another(1);
    another = inv;
    copied.ForEach([](const Item& it) { it.PrintInfo(); });
    another.ForEach([](const Item& it) { it.PrintInfo(); });

    std::cout << "\n[Inventory<Weapon>]\n";
    Inventory<Weapon> wInv;
    wInv.AddItem(Weapon{ "�ռҵ�", 15, 120 });
    wInv.AddItem(Weapon{ "Ȱ", 8, 80 });
    wInv.AddItem(Weapon{ "���", 25, 300 });
    wInv.SortItems(); // operator< ���
    wInv.ForEach([](const Weapon& w) { w.PrintInfo(); });

    std::cout << "\n[Inventory<Potion>]\n";
    Inventory<Potion> pInv(1);
    pInv.AddItem(Potion{ "��������", 50, 120 });
    pInv.AddItem(Potion{ "�ް�����", 100, 300 });
    pInv.ForEach([](const Potion& p) { p.PrintInfo(); });

    return 0;
}
