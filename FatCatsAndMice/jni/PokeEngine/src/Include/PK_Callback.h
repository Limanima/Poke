#ifndef _PK_CALLBACK_H_
#define _PK_CALLBACK_H_

#include <stdlib.h>

namespace PK {

template <class T>
class PK_Callback
{
    T *m_p;

public:
    PK_Callback() 
    {
        m_p = NULL;
    }
    ~PK_Callback()
    {
       Set(NULL);
    }

    void Set(T *pCallback) 
    { 
        if (m_p == pCallback)
        {
          return;
        }
        if (m_p != NULL)
        {
            delete m_p;
        }
        m_p = pCallback;
    }
   
    T* operator->() const 
    {
      if(m_p == NULL)
      {
        return NULL;
      }
      return m_p;
    }

    inline bool HasCallback() { return (m_p != NULL); }
};

    
} // namespace

#endif
