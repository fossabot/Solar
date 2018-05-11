#ifndef SOLAR_INDEXER_HPP
#define SOLAR_INDEXER_HPP

#include <vector>

namespace Solar
{
    class Indexer final
    {
    public:
        typedef unsigned long long indexType;

    private:
        indexType index;
        std::vector<indexType> freeIndex;

    public:
        Indexer();
        Indexer(const Indexer &);
        Indexer &operator=(const Indexer &);
        indexType next();
        void reset();
        void free(indexType);
        ~Indexer();
    };
}

#endif
