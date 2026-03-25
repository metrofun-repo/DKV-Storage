#include "HttplibClient.h"

#include "third-party/httplib.h"

namespace infra::http::adapters::httplib::client {

using Error     = http::client::HttpClientError;
using ErrorCode = http::client::HttpClientErrorCode;
using Payload   = http::client::HttpClientResponsePayload;

using libError  = ::httplib::Error;
using libClient = ::httplib::Client;

using ::httplib::to_string;

HttplibClient::PostResult HttplibClient::post(
    std::string_view host,
    int port,
    std::string_view path,
    std::string_view body,
    std::size_t size,
    std::string_view contentType) const
{
    libClient client(host.data(), port);
    auto result = client.Post(path.data(), body.data(), size, contentType.data());

    if(!result)
    {
        const std::string message = to_string(result.error());
        switch(result.error())
        {
            case libError::Connection :
                return PostResult::makeFailure(Error {
                        ErrorCode::Connection,
                        message
                    });
            case libError::Read :
                return PostResult::makeFailure(Error {
                        ErrorCode::Read,
                        message
                    });
            case libError::Write :
                return PostResult::makeFailure(Error {
                        ErrorCode::Write,
                        message
                    });
            case libError::Timeout :
                return PostResult::makeFailure(Error {
                        ErrorCode::Timeout,
                        message
                    });
            default :
                return PostResult::makeFailure(Error {
                        ErrorCode::Unknown,
                        message
                    });
        }
    }

    return PostResult::makeSuccess({ result->status, std::move(result->body) });
}

} // namespace infra::http::adapters::httplib::client