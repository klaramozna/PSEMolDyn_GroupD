//
// Created by klara on 30.11.23.
//

#ifndef PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
#define PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H

#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Particles/CuboidBoundary.h"


class LinkedCellContainerTest {
public:
    LinkedCellContainer container{CuboidBoundary(3, 3, 3), 1};
};


#endif //PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
