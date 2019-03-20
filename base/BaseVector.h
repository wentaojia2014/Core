#pragma once

#include "../common/types.h"

namespace Core {

    template <typename T, UInt32 componentCount>
    class BaseVector {
    public:
        static const UInt32 ComponentCount = componentCount;
        typedef T ComponentType;
    };
}
