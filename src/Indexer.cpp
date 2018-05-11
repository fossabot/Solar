#include "Indexer.hpp"

Solar::Indexer::Indexer() : index(0) {}

Solar::Indexer::Indexer(const Indexer &other) : index(other.index), freeIndex(other.freeIndex) {}

Solar::Indexer &Solar::Indexer::operator=(const Indexer &other)
{
    index = other.index;
    freeIndex = other.freeIndex;
    return *this;
}

Solar::Indexer::indexType Solar::Indexer::next()
{
    indexType ret;
    if (freeIndex.empty())
    {
        ret = index;
        ++index;
        return ret;
    }
    ret = freeIndex[0];
    freeIndex.erase(freeIndex.begin());
    return ret;
}

void Solar::Indexer::reset()
{
    index = 0;
    freeIndex.clear();
}

void Solar::Indexer::free(indexType toFree)
{
    freeIndex.emplace_back(toFree);
}

Solar::Indexer::~Indexer()
{
    freeIndex.clear();
    freeIndex.shrink_to_fit();
}
