#include "repository/IItemRepository.h"
#include "repository/JsonItemRepository.h"

#define NOMINMAX
#include <windows.h>

#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <vector>

namespace
{
    void printMenu()
    {
        std::cout << "==============================" << std::endl;
        std::cout << "[1] 등록  [2] 전체 조회  [3] 단건 조회  [4] 수정  [5] 삭제  [0] 종료" << std::endl;
        std::cout << "선택 > ";
    }

    void printItem(const Item& item)
    {
        std::cout << "  " << item.id << " | " << item.name << std::endl;
    }

    int readId()
    {
        int id = 0;
        std::cin >> id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return id;
    }

    void handleCreate(IItemRepository& repository)
    {
        std::cout << "등록할 이름 > ";
        std::string name;
        std::getline(std::cin, name);

        const Item saved = repository.save(Item{ 0, name });
        std::cout << "등록 완료: id=" << saved.id << std::endl;
    }

    void handleReadAll(IItemRepository& repository)
    {
        const std::vector<Item> items = repository.findAll();
        if (items.empty())
        {
            std::cout << "등록된 항목이 없습니다." << std::endl;
            return;
        }

        for (const Item& item : items)
        {
            printItem(item);
        }
    }

    void handleReadOne(IItemRepository& repository)
    {
        std::cout << "조회할 id > ";
        const int id = readId();

        const std::optional<Item> found = repository.findById(id);
        if (!found.has_value())
        {
            std::cout << "해당 id의 항목이 없습니다." << std::endl;
            return;
        }

        printItem(*found);
    }

    void handleUpdate(IItemRepository& repository)
    {
        std::cout << "수정할 id > ";
        const int id = readId();

        if (!repository.findById(id).has_value())
        {
            std::cout << "해당 id의 항목이 없습니다." << std::endl;
            return;
        }

        std::cout << "새 이름 > ";
        std::string name;
        std::getline(std::cin, name);

        repository.save(Item{ id, name });
        std::cout << "수정 완료." << std::endl;
    }

    void handleDelete(IItemRepository& repository)
    {
        std::cout << "삭제할 id > ";
        const int id = readId();

        if (repository.remove(id))
        {
            std::cout << "삭제 완료." << std::endl;
        }
        else
        {
            std::cout << "해당 id의 항목이 없습니다." << std::endl;
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    JsonItemRepository repository("items.json");

    bool running = true;
    while (running)
    {
        printMenu();

        std::string command;
        std::getline(std::cin, command);

        if (command == "0") running = false;
        else if (command == "1") handleCreate(repository);
        else if (command == "2") handleReadAll(repository);
        else if (command == "3") handleReadOne(repository);
        else if (command == "4") handleUpdate(repository);
        else if (command == "5") handleDelete(repository);
        else std::cout << "알 수 없는 명령입니다." << std::endl;
    }

    return 0;
}
