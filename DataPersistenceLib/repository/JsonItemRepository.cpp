#include "repository/JsonItemRepository.h"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <fstream>

using nlohmann::json;

namespace
{
    Item fromJson(const json& element)
    {
        return Item{ element.at("id").get<int>(), element.at("name").get<std::string>() };
    }

    json toJson(const Item& item)
    {
        return json{ {"id", item.id}, {"name", item.name} };
    }
}

JsonItemRepository::JsonItemRepository(const std::string& file_path)
    : file_path(file_path)
{
    for (const Item& item : loadAll())
    {
        if (item.id >= next_id) next_id = item.id + 1;
    }
}

Item JsonItemRepository::save(const Item& item)
{
    std::vector<Item> items = loadAll();

    Item saved_item = item;
    if (saved_item.id == 0)
    {
        saved_item.id = next_id;
        next_id++;
        items.push_back(saved_item);
    }
    else
    {
        auto it = std::find_if(items.begin(), items.end(),
            [&saved_item](const Item& existing) { return existing.id == saved_item.id; });

        if (it == items.end())
        {
            items.push_back(saved_item);
        }
        else
        {
            *it = saved_item;
        }
    }

    saveAll(items);
    return saved_item;
}

std::optional<Item> JsonItemRepository::findById(int id)
{
    const std::vector<Item> items = loadAll();
    auto it = std::find_if(items.begin(), items.end(),
        [id](const Item& item) { return item.id == id; });

    if (it == items.end()) return std::nullopt;
    return *it;
}

std::vector<Item> JsonItemRepository::findAll()
{
    return loadAll();
}

bool JsonItemRepository::remove(int id)
{
    std::vector<Item> items = loadAll();
    const size_t original_size = items.size();

    items.erase(
        std::remove_if(items.begin(), items.end(), [id](const Item& item) { return item.id == id; }),
        items.end());

    if (items.size() == original_size) return false;

    saveAll(items);
    return true;
}

std::vector<Item> JsonItemRepository::loadAll() const
{
    std::ifstream input(file_path);
    if (!input.is_open()) return {};

    input.seekg(0, std::ios::end);
    if (input.tellg() == 0) return {};
    input.seekg(0, std::ios::beg);

    json root;
    input >> root;

    std::vector<Item> items;
    items.reserve(root.size());
    for (const json& element : root)
    {
        items.push_back(fromJson(element));
    }
    return items;
}

void JsonItemRepository::saveAll(const std::vector<Item>& items) const
{
    json root = json::array();
    for (const Item& item : items)
    {
        root.push_back(toJson(item));
    }

    std::ofstream output(file_path);
    output << root.dump(4);
}
