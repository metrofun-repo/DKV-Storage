#pragma once

#include <vector>
#include <string>
#include <stdint.h>

namespace infra::serialization {

struct SerializedMessage
{
    std::vector<uint8_t> bytes;
    std::string contentType;
};

}