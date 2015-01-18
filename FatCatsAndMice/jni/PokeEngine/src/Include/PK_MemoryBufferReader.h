#ifndef _PK_MEMORYBUFFERREADER_H_
#define _PK_MEMORYBUFFERREADER_H_

#include "PK_Object.h"
#include "PK_MemoryBuffer.h"

namespace PK {


class PK_MemoryBufferReader : PK_Object
{
private:
    PK_MemoryBuffer *m_pMemoryBuffer;
    PK_MemoryBuffer  m_AuxBuffer;
    unsigned int     m_iPointerPosition;
    
public:
	PK_MemoryBufferReader(PK_MemoryBuffer &buffer);
    ~PK_MemoryBufferReader();

    PK_String ReadLine(); 
    inline bool IsAtEOB() { return (m_iPointerPosition + 1 >= m_pMemoryBuffer->GetLength()); };
};

} // Namespace
#endif
