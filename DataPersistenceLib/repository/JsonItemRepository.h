#pragma once

#include "repository/IItemRepository.h"

#include <string>

class JsonItemRepository : public IItemRepository
{
    public:
        explicit JsonItemRepository(const std::string& file_path);

        Item save(const Item& item) override;
        std::optional<Item> findById(int id) override;
        std::vector<Item> findAll() override;
        bool remove(int id) override;

    private:
        std::vector<Item> loadAll() const;
        void saveAll(const std::vector<Item>& items) const;

        std::string file_path;
        int next_id = 1;
};
