#ifndef _PK_FILECOPYCALLBACK_H_
#define _PK_FILECOPYCALLBACK_H_

#include "PK_Object.h"
#include "PK_Types.h"
#include "PK_Callback.h"

namespace PK {

class PK_IFileCopyCallback
{
public:
    virtual bool Execute(PK_String &sourceFile, PK_String &destination, bool bIsFolder) = 0;
};
    
template <class T>
class PK_FileCopyCallback : public PK_IFileCopyCallback
{
public:
   typedef bool (T::*PK_FileCopyCallbackMethod)(PK_String &sourceFile, PK_String &destination, bool bIsFolder);

private:
   T                  *m_pObject;
   PK_FileCopyCallbackMethod   m_callbackMethod;

public:
   PK_FileCopyCallback(T &object, PK_FileCopyCallbackMethod callback)
   {
      m_callbackMethod = callback;
      m_pObject = &object;
   }

   bool operator()(PK_String &sourceFile, PK_String &destination, bool bIsFolder)
   {
      return (m_pObject->*m_callbackMethod)(sourceFile, destination, bIsFolder);
   }

   bool Execute(PK_String &sourceFile, PK_String &destination, bool bIsFolder)
   {
      return operator()(sourceFile, destination, bIsFolder);
   }

};
    
} // namespace

#endif
