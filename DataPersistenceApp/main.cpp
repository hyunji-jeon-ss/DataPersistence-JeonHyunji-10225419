#include "repository/JsonItemRepository.h"

#include <windows.h>

#include <iostream>

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    JsonItemRepository repository("items.json");

    std::cout << "저장된 항목 수: " << repository.findAll().size() << std::endl;

    const Item saved = repository.save(Item{ 0, "샘플-테스트" });
    std::cout << "새 항목 저장: id=" << saved.id << ", name=" << saved.name << std::endl;

    std::cout << "전체 목록:" << std::endl;
    for (const Item& item : repository.findAll())
    {
        std::cout << "  " << item.id << " | " << item.name << std::endl;
    }

    std::cout << "프로그램을 다시 실행하면 이전 데이터가 유지되는지 확인하세요 (items.json)." << std::endl;

    return 0;
}
