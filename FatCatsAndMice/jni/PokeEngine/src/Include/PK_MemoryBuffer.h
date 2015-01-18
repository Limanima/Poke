#ifndef _PK_MEMORYBUFFER_H_
#define _PK_MEMORYBUFFER_H_

#include "PK_Object.h"

namespace PK {

/// Buffer de dados em memória
/** Mantém um buffer de dados em memória (binário ou texto)
 */
class PK_MemoryBuffer : public PK_Object
{
private:
    char            * m_pBuffer;
    unsigned int      m_uiSize;
    unsigned int      m_uiUsedSize;
    
public:
	 PK_MemoryBuffer(unsigned int uiSize = 0);
	 PK_MemoryBuffer(const PK_String &str);
    ~PK_MemoryBuffer();
        
    inline char operator[] (unsigned int idx) 
    {
        if (idx >= m_uiSize)
        {
            throw PK_SystemException("Index '%d' is out of the bounds of the memory buffer named '%s' (buffer size is'%d') ",
                    __FILE__, __LINE__, idx, GetName().c_str(), m_uiSize);
        }
        return m_pBuffer[idx];
    }

    /// Esvazia o buffer e liberta a memoria associada.
    void Empty();
    /// Coloca o conteudo do buffer a zeros mas mantem a memoria associada.
    void Clear();
    /// Altera o tamanho do buffer. Nao limpa nem preserva o conteudo
    void SetSize(unsigned int uiSize);
    void SetLength(unsigned int uiLength);
    /// Altera o tamanho do buffer. Se bPreserve e verdadeiro, os dados sao mantidos podendo ficar truncados caso 
    /// o buffer seja alterado para um tamanho mais pequeno.
    void SetSize(unsigned int size, bool bClear, bool bPreserve);
	void SetData(const PK_String &str);
    /// Altera o conteudo do buffer.
    void SetData(void * pData, unsigned int uiDataLength, unsigned int uiIdx = 0);
    /// Altera o conteudo do buffer.
    void SetData(const PK_MemoryBuffer &source, unsigned int uiDataLength, unsigned int uiIdx = 0);
    /// Altera um char dentro do buffer.
    void SetChar(char ch, unsigned int uiPosition);
    /// Adiciona dados no final do buffer.
    void Append(void * data, unsigned int uiLength);
    void Append(const PK_String &sText);
    void Append(int iValue);
    /// Devolve o tamanho do buffer.
    inline unsigned int GetSize() const { return m_uiSize; }
    /// Devolve o tamanho do espaco utilizado.
    inline unsigned int GetLength() const { return m_uiUsedSize; }
    /// Devolve o buffer como string.
    char * GetAsStr();
    char * GetAsStr(unsigned int iStartIndex);
    /// Devolve o pointer da cabeça do buffer.
    inline void * GetData() const { return m_pBuffer; }
    inline void * GetData(unsigned int uiIndex) const 
    { 
        if (uiIndex >= m_uiSize)
        {
            throw PK_SystemException("Index '%d' is out of the bounds of the memory buffer named '%s' (buffer size is'%d') ",
                    __FILE__, __LINE__, uiIndex, GetName().c_str(), m_uiSize);
        }
        return (void *)&m_pBuffer[uiIndex]; 
    }
};

} // Namespace
#endif
