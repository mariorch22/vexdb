#pragma once

#include <cstddef>
#include <vector>

#include "core/types.h"
#include "store/concept.h"

namespace vexdb {

class InMemoryStore {
   public:
    explicit InMemoryStore(Dim dim);

    // Append a vector and return its offset.
    Offset add_vector(const float* data);

    // Read access.
    const float* get_vector(Offset offset) const;
    std::size_t size() const;
    Dim dimensions() const;

   private:
    Dim dim_;
    std::vector<float> data_;
};

static_assert(VectorStore<InMemoryStore>);

}  // namespace vexdb