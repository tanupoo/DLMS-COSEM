#pragma once

#include <functional>
#include "ISerial.h"
#include "ISimpleTimer.h"
#include "hdlc/HDLCMAC.h"
#include "hdlc/HDLCOptions.h"
#include "Callback.h"

namespace EPRI
{
    class HDLCLLC : public Callback<HDLCErrorCode, uint16_t>
	{
	public:
    	HDLCLLC() = delete;
    	HDLCLLC(HDLCMAC * pMAC);
    	virtual ~HDLCLLC();
    	
    	virtual HDLCRunResult Process();

    	HDLCAddress MyAddress() const;
    	const HDLCStatistics& Statistics() const;
    	void ClearStatistics();
    	//
        // DL-DATA Service
        //
    	virtual HDLCRunResult DataRequest(const DataRequestParameter& Parameters) = 0;
    	virtual void RegisterDataIndication(CallbackFunction Callback) = 0;
    	
	private:
    	static constexpr uint8_t LLC_HEADER[] = { 0xE6, 0xE6, 0x00 };
    	HDLCMAC *				 m_pMAC;
	};
    
    class HDLCClientLLC : public HDLCLLC
    {
    public:
        HDLCClientLLC(const HDLCAddress& MyAddress, 
            ISerial * pSerial, 
            const HDLCOptions& Options,
            uint8_t MaxPreallocatedPacketBuffers = 10);
        virtual ~HDLCClientLLC();
        //
        // DL-CONNECT Service
        //
        HDLCRunResult ConnectRequest(const ConnectRequestOrIndication& Parameters);
        void RegisterConnectConfirm(CallbackFunction Callback);
        //
        // DL-DATA Service
        //
        HDLCRunResult DataRequest(const DataRequestParameter& Parameters);
        void RegisterDataIndication(CallbackFunction Callback);

    protected:
        HDLCErrorCode MACConnectConfirm(const BaseCallbackParameter& Paramters);
        HDLCErrorCode MACDataIndication(const BaseCallbackParameter& Parameters);
        
    private:
        HDLCClient              m_MAC;
        
    };
    
    class HDLCServerLLC : public HDLCLLC
    {
    public:
        HDLCServerLLC(const HDLCAddress& MyAddress, 
            ISerial * pSerial, 
            const HDLCOptions& Options,
            uint8_t MaxPreallocatedPacketBuffers = 10);
        virtual ~HDLCServerLLC();
        //
        // DL-CONNECT Service
        //
        void RegisterConnectIndication(CallbackFunction Callback);
        HDLCRunResult ConnectResponse(const ConnectConfirmOrResponse& Parameters);
        //
        // DL-DATA Service
        //
        HDLCRunResult DataRequest(const DataRequestParameter& Parameters);
        void RegisterDataIndication(CallbackFunction Callback);
        
    protected:
        HDLCErrorCode MACConnectIndication(const BaseCallbackParameter& Parameters);
        HDLCErrorCode MACDataIndication(const BaseCallbackParameter& Parameters);
        
    private:
        HDLCServer              m_MAC;
        
    };

	
} /* namespace EPRI */
