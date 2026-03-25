#pragma once

namespace infra::transport::error {

enum class TransportErrorCode
{
    Unknown,
    UnknownMessage,
    //client errors
    Timeout,
    ConnectionRefused,
    HostUnreachable,
    //http error
    HttpError,
    // json 
    SerializationFailed,
    DeserializationFailed,
    //response
    InvalidResponse
};

} // namespace infra::transport::error