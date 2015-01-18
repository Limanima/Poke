#include "PK_MemoryBufferReader.h"
#include "PK_Exceptions.h"

namespace PK
{
    
PK_MemoryBufferReader::PK_MemoryBufferReader(PK_MemoryBuffer &buffer)
{
    SetTypeName("PK_MemoryBufferReader");
    m_pMemoryBuffer = &buffer;
    m_iPointerPosition = 0;
    m_AuxBuffer.SetSize(1024);
}
  
//
PK_MemoryBufferReader::~PK_MemoryBufferReader()
{
}

//
PK_String PK_MemoryBufferReader::ReadLine()
{
    if (IsAtEOB())
    {
        throw PK_SystemException("Cannot read past the end of the buffer.", __FILE__, __LINE__);
    }

    unsigned int i;
    for(i = m_iPointerPosition; i < m_pMemoryBuffer->GetLength(); i++)
    {
        if ((*m_pMemoryBuffer)[i] == '\n' ||
            (*m_pMemoryBuffer)[i] == '\r')
        {
            break;
        }
    }
    if (i >= m_pMemoryBuffer->GetLength())
    {
        i = m_pMemoryBuffer->GetLength() - 1;
    }
    m_AuxBuffer.SetData(m_pMemoryBuffer->GetData(m_iPointerPosition), i - m_iPointerPosition, 0);
    if ((*m_pMemoryBuffer)[i] == '\n' || (*m_pMemoryBuffer)[i] == '\r')
    {
        i++;
    }
    if (i <  m_pMemoryBuffer->GetLength() && ((*m_pMemoryBuffer)[i] == '\r' || (*m_pMemoryBuffer)[i] == '\n'))
    {
        i++;
    }

    m_iPointerPosition = i;

    return m_AuxBuffer.GetAsStr();
}

} // namespace