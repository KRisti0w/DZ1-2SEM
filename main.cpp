#include <iostream>
#include "BSTree.h"

int main() {
    using namespace BST;

    // Создание дерева
    BSTree<int> tree;

    // Добавление элементов
    std::cout << "Adding elements: 50, 30, 70, 20, 40, 60, 80\n";
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Вывод дерева (симметричный обход)
    std::cout << "\nTree (in-order): " << tree << std::endl;

    // Другие обходы
    std::cout << "Pre-order: ";
    tree.printPreOrder();

    std::cout << "Post-order: ";
    tree.printPostOrder();

    // Поиск
    std::cout << "\nSearch 40: " << (tree.search(40) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 100: " << (tree.search(100) ? "Found" : "Not found") << std::endl;

    // Удаление
    std::cout << "\nRemoving 30\n";
    tree.remove(30);
    std::cout << "Tree after removal: " << tree << std::endl;

    // Конструктор копирования
    BSTree<int> tree2 = tree;
    std::cout << "\nCopied tree: " << tree2 << std::endl;

    // Конструктор перемещения
    BSTree<int> tree3 = std::move(tree2);
    std::cout << "Moved tree: " << tree3 << std::endl;
    std::cout << "Original after move: " << tree2 << std::endl;

    // Сохранение в файл
    tree3.save("tree.txt");
    std::cout << "\nTree saved to 'tree.txt'\n";

    // Загрузка из файла
    BSTree<int> tree4;
    tree4.load("tree.txt");
    std::cout << "Tree loaded from file: " << tree4 << std::endl;

    // Очистка
    tree4.clear();
    std::cout << "After clear: " << tree4 << std::endl;

    return 0;
}