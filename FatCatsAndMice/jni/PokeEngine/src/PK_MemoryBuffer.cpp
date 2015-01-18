#include "PK_MemoryBuffer.h"
#include "PK_Exceptions.h"

namespace PK
{

//   
PK_MemoryBuffer::PK_MemoryBuffer(unsigned int uiSize)
{
    m_pBuffer = NULL;
    m_uiSize = uiSize;
    if (uiSize != 0)
    {
        SetSize(uiSize, true, false);
    }
    m_uiUsedSize = 0;
}

//
PK_MemoryBuffer::PK_MemoryBuffer(const PK_String &str)
{
    m_pBuffer = NULL;
    m_uiUsedSize = 0;
    m_uiSize = 0;
	SetData(str);
}

PK_MemoryBuffer::~PK_MemoryBuffer()
{
   Empty();
}

// Esvazia o buffer libertando a memoria associada
void PK_MemoryBuffer::Empty()
{
    if (m_pBuffer != NULL)
    {
        delete [] m_pBuffer;
        m_uiSize = 0;
        m_uiUsedSize = 0;
        m_pBuffer = NULL;
    }
}
    
// Limpa o buffer a zeros
void PK_MemoryBuffer::Clear()
{
    if (m_pBuffer == NULL)
    {
        return;
    }
    
    memset(m_pBuffer, 0, m_uiSize);
    m_uiUsedSize = 0;
}

//
void PK_MemoryBuffer::SetSize(unsigned int uiSize)
{
    SetSize(uiSize, false, false);
}

//
void PK_MemoryBuffer::SetLength(unsigned int uiLength)
{
    if (uiLength > m_uiSize)
    {
        throw PK_SystemException("Trying to set memory buffer length outside of MemoryBuffer. Buffer size is %d, desired length was %d.", __FILE__, __LINE__, m_uiSize, uiLength);
    }
    m_uiUsedSize = uiLength;
}

// Seta o tamanho do buffer e aloca a memoria
void PK_MemoryBuffer::SetSize(unsigned int uiSize, bool bClear, bool bPreserve)
{
    if (uiSize == 0)
    {
        throw PK_SystemException("Memory buffer cannot have a size of 0", __FILE__, __LINE__);
    }
                                 
    // Tamanho e o mesmo? Nao faz nada...
    if (uiSize == m_uiSize)
    {
        if (bClear)
        {
            Clear();
        }
        return;
    }
    
    char * m_pAux = new char[uiSize + 1]; // Adicionamos um para o metodo GetAsStr() poder fazer append do '\0'
    if (m_pAux == NULL)
    {
        throw PK_OutOfMemoryException("char", uiSize, __FILE__, __LINE__);
    }

    if (m_uiUsedSize > uiSize)
    {
        m_uiUsedSize = uiSize;
    }

    if (bPreserve)
    {
        memcpy(m_pAux, m_pBuffer, m_uiUsedSize); 
    }
    delete [] m_pBuffer;
    m_pBuffer = m_pAux;
    m_uiSize = uiSize;
}

//
void PK_MemoryBuffer::SetData(const PK_String &str)
{
	SetData((char *)str.c_str(), (unsigned int)str.length(), 0);
}

//
void PK_MemoryBuffer::SetData(void * pData, unsigned int uiDataLength, unsigned int uiIdx)
{
    if (uiDataLength + uiIdx > m_uiSize)
    {
        SetSize(uiDataLength + uiIdx, false, true);
    }
    memcpy(&m_pBuffer[uiIdx], pData, uiDataLength);
    m_uiUsedSize = uiDataLength + uiIdx;
}

//
void PK_MemoryBuffer::SetData(const PK_MemoryBuffer &source, unsigned int uiDataLength, unsigned int uiIdx)
{
    SetData((char *)source.GetData(), uiDataLength, uiIdx);
}
    
// Seta um valor char dentro do buffer
void PK_MemoryBuffer::SetChar(char ch, unsigned int uiPosition)
{
    if (uiPosition >= m_uiSize)
    {
        throw PK_SystemException("Trying to set a value outside of MemoryBuffer. Buffer size is %d, accessed position was %d.", __FILE__, __LINE__, m_uiSize, uiPosition);
    }
    
    m_pBuffer[uiPosition] = ch;
}

// 
void PK_MemoryBuffer::Append(void * data, unsigned int uiLength)
{
    // Vai ficar fora do buffer? Altera-se o tamanho para caber
    if (m_uiUsedSize + uiLength > m_uiSize)
    {
        SetSize(m_uiUsedSize + uiLength, false, true);
    }
    SetData((char*)data, uiLength, m_uiUsedSize);
}

// 
void PK_MemoryBuffer::Append(const PK_String &sText)
{
    Append((void *) sText.c_str(), (unsigned int)sText.length());
}

// 
void PK_MemoryBuffer::Append(int iValue)
{
    Append((void *) &iValue, sizeof(iValue));
}

// Devolve o pointer e faz append de '\0' no final
char * PK_MemoryBuffer::GetAsStr()
{ 
    m_pBuffer[m_uiUsedSize] = '\0';
    return m_pBuffer; 
}

// Devolve o pointer e faz append de '\0' no final
char * PK_MemoryBuffer::GetAsStr(unsigned int iStartIndex)
{ 
    if (iStartIndex >= m_uiSize)
    {
        throw PK_SystemException("Trying to get a value outside of MemoryBuffer. Buffer size is %d, accessed position was %d.", __FILE__, __LINE__, m_uiSize, iStartIndex);
    }

    m_pBuffer[m_uiUsedSize] = '\0';
    return &m_pBuffer[iStartIndex]; 
}

} // namespace