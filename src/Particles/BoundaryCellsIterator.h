//
// Created by rodff on 04.12.23.
//

#pragma once

#include <iterator>
#include "Cell.h"

class BoundaryCellIterator : public std::iterator<std::input_iterator_tag, Cell*> {
public:
    BoundaryCellIterator(std::vector<Cell*>& boundaryCells, size_t index) : boundaryCells(boundaryCells), index(index) {}

    BoundaryCellIterator& operator++() {
        ++index;
        return *this;
    }

    BoundaryCellIterator operator++(int) {
        BoundaryCellIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const BoundaryCellIterator& rhs) const {
        return index == rhs.index;
    }

    bool operator!=(const BoundaryCellIterator& rhs) const {
        return index != rhs.index;
    }

    Cell* operator*() {
        return boundaryCells[index];
    }

private:
    std::vector<Cell*>& boundaryCells;
    size_t index;
};
