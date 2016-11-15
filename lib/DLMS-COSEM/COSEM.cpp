#include "COSEM.h"
#include "APDU/AARQ.h"
#include "APDU/AARE.h"
#include "APDU/GET-Request.h"
#include "APDU/GET-Response.h"

namespace EPRI
{
    
    const ASNObjectIdentifier COSEM::ContextLNRNoCipher({ 2, 16, 756, 5, 8, 1, 1 });
    const ASNObjectIdentifier COSEM::ContextSNRNoCipher({ 2, 16, 756, 5, 8, 1, 2 });
    const ASNObjectIdentifier COSEM::MechanismNameLowLevelSecurity({ 2, 16, 756, 5, 8, 2, 1 }, 
                                                                   ASN::IMPLICIT);
    const ASNObjectIdentifier COSEM::MechanismNameHighLevelSecurity({ 2, 16, 756, 5, 8, 2, 5 }, 
                                                                    ASN::IMPLICIT);

    COSEM::COSEM() :
        StateMachine(ST_MAX_STATES)
    {
        //
        // State Machine
        //
        BEGIN_STATE_MAP
            STATE_MAP_ENTRY(ST_INACTIVE, COSEM::ST_Inactive_Handler)
            STATE_MAP_ENTRY(ST_IDLE, COSEM::ST_Idle_Handler)
            STATE_MAP_ENTRY(ST_ASSOCIATION_PENDING, COSEM::ST_Association_Pending_Handler)
            STATE_MAP_ENTRY(ST_ASSOCIATION_RELEASE_PENDING, COSEM::ST_Association_Release_Pending_Handler)
            STATE_MAP_ENTRY(ST_ASSOCIATED, COSEM::ST_Associated_Handler)
        END_STATE_MAP
    }
    
    COSEM::~COSEM()
    {
    }
    	
    COSEM::TRANSPORT_HANDLE COSEM::RegisterTransport(Transport * pXPort)
    {
        static TRANSPORT_HANDLE HANDLE_COUNTER = 0;
        if (m_Transports.size() == MaxTransports())
        {
            return -1;
        }
        ++HANDLE_COUNTER;
        m_Transports[HANDLE_COUNTER] = pXPort;
        
        pXPort->RegisterTransportEventHandler(
            std::bind(&COSEM::TransportEventHandler, this, std::placeholders::_1));
        //
        // APDU Handler Registration
        //
        pXPort->RegisterAPDUHandler(AARQ::Tag,
            std::bind(&COSEM::AARQ_Handler, this, std::placeholders::_1));
        pXPort->RegisterAPDUHandler(AARE::Tag,
            std::bind(&COSEM::AARE_Handler, this, std::placeholders::_1));
        pXPort->RegisterAPDUHandler(Get_Request_Base::Tag,
            std::bind(&COSEM::GET_Request_Handler, this, std::placeholders::_1));
        pXPort->RegisterAPDUHandler(Get_Response_Base::Tag,
            std::bind(&COSEM::GET_Response_Handler, this, std::placeholders::_1));
        
        return HANDLE_COUNTER;
    }
    
    bool COSEM::IsOpen() const
    {
        return m_CurrentState == ST_ASSOCIATED;
    }
    
    size_t COSEM::MaxTransports()
    {
        return 1;
    }
    
    bool COSEM::TransportEventHandler(const Transport::TransportEvent& Event)
    {
        bool bAllowed = false;
        BEGIN_TRANSITION_MAP
            TRANSITION_MAP_ENTRY(ST_INACTIVE, ST_IDLE)
            TRANSITION_MAP_ENTRY(ST_IDLE, EVENT_IGNORED)
            TRANSITION_MAP_ENTRY(ST_ASSOCIATION_PENDING, EVENT_IGNORED)
            TRANSITION_MAP_ENTRY(ST_ASSOCIATION_RELEASE_PENDING, EVENT_IGNORED)
            TRANSITION_MAP_ENTRY(ST_ASSOCIATED, ST_INACTIVE)
        END_TRANSITION_MAP(bAllowed, new TransportEventData(Event));
        return bAllowed;
    }

}