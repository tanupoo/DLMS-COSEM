#include "COSEM.h"

namespace EPRI
{
    COSEMServer::COSEMServer()
    {
    }
    
    COSEMServer::~COSEMServer()
    {
    }
    //
    // COSEM-OPEN Service
    //
    void COSEMServer::RegisterConnectIndication(CallbackFunction Callback)
    {
    }
    
    bool COSEMServer::ConnectResponse(const APPOpenConfirmOrResponse& Parameters)
    {
    }
    //
	// State Machine Handlers
    //
    void COSEMServer::ST_Inactive_Handler(EventData * pData)
    {
    }
    
    void COSEMServer::ST_Idle_Handler(EventData * pData)
    {
    }
    
    void COSEMServer::ST_Association_Pending_Handler(EventData * pData)
    {
    }
    
    void COSEMServer::ST_Association_Release_Pending_Handler(EventData * pData)
    {
    }
    
    void COSEMServer::ST_Associated_Handler(EventData * pData)
    {
    }
    //
    // APDU Handlers
    //
    bool COSEMServer::AARE_Handler(const IAPDUPtr& pAPDU)
    {
        return false;
    }
    
    bool COSEMServer::AARQ_Handler(const IAPDUPtr& pAPDU)
    {
        return false;
    }
    
    bool COSEMServer::GET_Request_Handler(const IAPDUPtr& pAPDU)
    {
        return false;
    }
    
    bool COSEMServer::GET_Response_Handler(const IAPDUPtr& pAPDU)
    {
        return false;
    }

}