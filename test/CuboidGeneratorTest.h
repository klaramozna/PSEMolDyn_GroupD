//
// Created by klara on 15.11.23.
//

#ifndef PSEMOLDYN_GROUPD_CUBOIDGENERATORTEST_H
#define PSEMOLDYN_GROUPD_CUBOIDGENERATORTEST_H

#include <gtest/gtest.h>
#include "../src/utils/CuboidGenerator.h"

class CuboidGeneratorTest : public testing::Test {
protected:
    CuboidGenerator generator{std::array<double, 3>{0, 0, 0}, 2, 2, 3, 1, 1, std::array<double, 3>{0}};
};


#endif //PSEMOLDYN_GROUPD_CUBOIDGENERATORTEST_H
