#include <gtest/gtest.h>

#include "segment/id_mapping.h"

TEST(IdMapping, InsertAndLookupBothDirections) {
    vexdb::IdMapping mapping;

    vexdb::Offset o0 = mapping.insert(100);
    vexdb::Offset o1 = mapping.insert(200);
    vexdb::Offset o2 = mapping.insert(300);

    EXPECT_EQ(o0, 0);
    EXPECT_EQ(o1, 1);
    EXPECT_EQ(o2, 2);
    EXPECT_EQ(mapping.size(), 3);

    EXPECT_EQ(mapping.get_user_id(0), 100);
    EXPECT_EQ(mapping.get_user_id(1), 200);
    EXPECT_EQ(mapping.get_user_id(2), 300);

    EXPECT_EQ(mapping.get_offset(100), 0);
    EXPECT_EQ(mapping.get_offset(200), 1);
    EXPECT_EQ(mapping.get_offset(300), 2);
}

TEST(IdMapping, GetOffsetReturnsNulloptForUnknownId) {
    vexdb::IdMapping mapping;
    mapping.insert(42);

    EXPECT_EQ(mapping.get_offset(999), std::nullopt);
}

TEST(IdMapping, DuplicateIdThrows) {
    vexdb::IdMapping mapping;
    mapping.insert(42);

    EXPECT_THROW(mapping.insert(42), std::invalid_argument);
}

TEST(IdMapping, ManyInserts) {
    vexdb::IdMapping mapping;

    for (vexdb::VectorId id = 1000; id < 2000; id++) {
        vexdb::Offset offset = mapping.insert(id);
        EXPECT_EQ(offset, id - 1000);
    }

    EXPECT_EQ(mapping.size(), 1000);

    for (vexdb::VectorId id = 1000; id < 2000; id++) {
        EXPECT_EQ(mapping.get_user_id(static_cast<vexdb::Offset>(id - 1000)), id);
        EXPECT_EQ(mapping.get_offset(id), static_cast<vexdb::Offset>(id - 1000));
    }
}

TEST(IdMapping, OffsetToIdAccessor) {
    vexdb::IdMapping mapping;
    mapping.insert(10);
    mapping.insert(20);
    mapping.insert(30);

    const auto& ids = mapping.offset_to_id();
    ASSERT_EQ(ids.size(), 3);
    EXPECT_EQ(ids[0], 10);
    EXPECT_EQ(ids[1], 20);
    EXPECT_EQ(ids[2], 30);
}