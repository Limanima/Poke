#ifndef _PK_OBJECT_H_
#define _PK_OBJECT_H_

#include <assert.h>
#include "PK_Consts.h"
#include "PK_String.h"
#include "PK_SystemException.h"

namespace PK { 

class PK_DataFileRecord;

// Base de todas as classes do engine. Faz reference counting de objectos
// Quando um cliente necessita de guardar uma referencia para alem do scope de uma funcao, deve fazer Grab() que faz incrementar
// o contador de referencias. Quando já nao precisar, deve fazer Release(). Na altura de release, se o contador chegar a 0, o 
// objecto e automaticamente destruido.
class PK_Object
{
private:
    mutable int m_iRefCount;
	PK_String   m_sTypeName; // As classes devem setar este name no construtor
	PK_String   m_sName;
    int         m_iTag;   // Pode ser utilizada pelos utilizadores a vontade

public:
	PK_Object();
	PK_Object(const PK_String &sName);
    virtual void FreeResources() { }
    virtual void InitFromDataFileRecord(PK_DataFileRecord &record);
	virtual ~PK_Object();
	
    inline void Grab() 
    {
        ++m_iRefCount;
    }
    
    inline void Release() 
    {
#ifdef POKE_DEBUG
        if (m_iRefCount <= 0)
        {
            throw PK_SystemException("Trying to release object with a reference count <= 0. Object Name is '%s', type is '%s'.",
            		 __FILE__, __LINE__, GetName().c_str(), GetTypeName().c_str());
        }
#endif
	    --m_iRefCount;
	    if(m_iRefCount == 0) 
	    {
            FreeResources();
		    delete (PK_Object *) this;
	    }
    }

    inline void SetName(const PK_String &sName) { m_sName = sName; }
	inline PK_String GetName() const { return m_sName; }
	inline PK_String GetTypeName() const { return m_sTypeName; }
    inline int GetRefCount() { return m_iRefCount; }
    inline void SetTag(int iValue) { m_iTag = iValue; }
    inline int GetTag() { return m_iTag; }

protected:
	inline void SetTypeName(const PK_String &sTypeName) { m_sTypeName = sTypeName; }
};

}

#endif
