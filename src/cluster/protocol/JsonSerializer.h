#pragma once

#include "ReplicationMessage.h"

#include <nlohmann/json.hpp>

nlohmann::json toJson(ReplicationMessage msg);
ReplicationMessage fromJson(const nlohmann::json& json);
