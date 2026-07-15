#pragma once

#include "model/Item.h"

#include <optional>
#include <vector>

class IItemRepository
{
    public:
        virtual ~IItemRepository() = default;

        virtual Item save(const Item& item) = 0;
        virtual std::optional<Item> findById(int id) = 0;
        virtual std::vector<Item> findAll() = 0;
        virtual bool remove(int id) = 0;
};
