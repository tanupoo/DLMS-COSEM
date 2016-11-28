#pragma once

#include "ICOSEMInterface.h"

namespace EPRI
{
    class IData_0 : public ICOSEMInterface
    {
        COSEM_DEFINE_SCHEMA(Data_Schema)
            
    public:
        IData_0();
        virtual ~IData_0();
        
        enum Attributes : ObjectAttributeIdType
        {
            ATTR_VALUE = 2
        };
        
        COSEMAttribute<ATTR_VALUE, Data_Schema, 0x08> value;
        
    };
    
    class IDataObject : public IData_0, public ICOSEMObject
    {
    public:
        IDataObject(const COSEMObjectInstanceCriteria& OIDCriteria, 
            uint16_t ShortNameBase = std::numeric_limits<uint16_t>::max());
        virtual ~IDataObject();

    };

}