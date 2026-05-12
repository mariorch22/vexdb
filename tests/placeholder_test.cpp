#include <gtest/gtest.h>

#include "core/vexdb.h"

TEST(Scaffolding, VersionIsCorrect) {
    EXPECT_EQ(vexdb::version_major(), 0);
    EXPECT_EQ(vexdb::version_minor(), 1);
    EXPECT_EQ(vexdb::version_patch(), 0);
}