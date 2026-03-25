#include "TransportToReplication.h"

namespace app::cluster::mapping {

using TransportErrorCode   = infra::transport::error::TransportErrorCode;
using ReplicationErrorCode = domain::replication::error::ReplicationErrorCode;    

ReplicationErrorCode fromTransport(TransportErrorCode code)
{
    switch(code)
    {
        case TransportErrorCode::Timeout : return ReplicationErrorCode::NodeTimeout; 

        
        case TransportErrorCode::HttpError         :  
        case TransportErrorCode::HostUnreachable   :  
        case TransportErrorCode::ConnectionRefused : return ReplicationErrorCode::NodeUnreachable; 

        case TransportErrorCode::InvalidResponse   : return ReplicationErrorCode::NodeInvalidResponse;

        case TransportErrorCode::SerializationFailed   : 
        case TransportErrorCode::DeserializationFailed : return ReplicationErrorCode::InternalError;

        default : return ReplicationErrorCode::Unknown;
    }
}

} // namespace app::cluster::mapping