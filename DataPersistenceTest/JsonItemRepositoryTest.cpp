#include "repository/JsonItemRepository.h"

#include "gmock/gmock.h"

#include <cstdio>
#include <string>

using namespace testing;

class JsonItemRepositoryTest : public Test
{
    protected:
        void SetUp() override
        {
            std::remove(file_path.c_str());
        }

        void TearDown() override
        {
            std::remove(file_path.c_str());
        }

        std::string file_path = "test_repository.json";
};

TEST_F(JsonItemRepositoryTest, FindAllReturnsEmptyWhenFileDoesNotExist)
{
    JsonItemRepository repository(file_path);

    EXPECT_TRUE(repository.findAll().empty());
}

TEST_F(JsonItemRepositoryTest, SaveAssignsIdAndPersistsItem)
{
    JsonItemRepository repository(file_path);

    const Item saved = repository.save(Item{ 0, "Sample-A" });

    EXPECT_EQ(saved.id, 1);
    ASSERT_EQ(repository.findAll().size(), 1u);
    EXPECT_EQ(repository.findAll()[0].name, "Sample-A");
}

TEST_F(JsonItemRepositoryTest, DataSurvivesRepositoryRecreation)
{
    {
        JsonItemRepository repository(file_path);
        repository.save(Item{ 0, "Sample-B" });
    }

    JsonItemRepository reloaded(file_path);
    ASSERT_EQ(reloaded.findAll().size(), 1u);
    EXPECT_EQ(reloaded.findAll()[0].name, "Sample-B");
}

TEST_F(JsonItemRepositoryTest, NextIdContinuesAfterRecreation)
{
    {
        JsonItemRepository repository(file_path);
        repository.save(Item{ 0, "Sample-C" });
    }

    JsonItemRepository reloaded(file_path);
    const Item second = reloaded.save(Item{ 0, "Sample-D" });

    EXPECT_EQ(second.id, 2);
}

TEST_F(JsonItemRepositoryTest, FindByIdReturnsNulloptWhenMissing)
{
    JsonItemRepository repository(file_path);

    EXPECT_FALSE(repository.findById(999).has_value());
}

TEST_F(JsonItemRepositoryTest, UpdateExistingItemOverwritesName)
{
    JsonItemRepository repository(file_path);
    const Item saved = repository.save(Item{ 0, "Original" });

    repository.save(Item{ saved.id, "Updated" });

    const std::optional<Item> found = repository.findById(saved.id);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->name, "Updated");
}

TEST_F(JsonItemRepositoryTest, RemoveDeletesItemAndReturnsTrue)
{
    JsonItemRepository repository(file_path);
    const Item saved = repository.save(Item{ 0, "ToRemove" });

    EXPECT_TRUE(repository.remove(saved.id));
    EXPECT_FALSE(repository.findById(saved.id).has_value());
}

TEST_F(JsonItemRepositoryTest, RemoveReturnsFalseWhenIdNotFound)
{
    JsonItemRepository repository(file_path);

    EXPECT_FALSE(repository.remove(123));
}

int main(int argc, char** argv)
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
