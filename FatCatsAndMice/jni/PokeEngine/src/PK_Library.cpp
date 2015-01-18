#include "PK_Library.h"
#include "PK_LibraryItem.h"
#include "PK_SceneControl.h"
#include "PK_Globals.h"

namespace PK {

//
PK_Library::PK_Library(const PK_String &sName) :
  PK_Object(sName)
{
    SetTypeName("PK_Library");
    SetSize(50);
    for(int i = 0; i < m_Items.GetCount(); i++)
    {
        m_Items[i] = NULL;
    }
}

//
PK_Library::~PK_Library()
{
  RemoveAllItems();
}

//
void PK_Library::SetSize(unsigned int iSize)
{
  m_Items.SetSize(iSize);
}

//
void PK_Library::AddItem(PK_eLibraryItemScope scope, PK_SceneControl &control, unsigned int iIndex, const PK_String &sName)
{
  PK_LibraryItem *pItem = new PK_LibraryItem(scope, control, sName);
  AddItem(*pItem, iIndex);
}

//
void PK_Library::AddItem(PK_LibraryItem &item, unsigned int iIndex)
{
  // Verifica se o index esta dentro do array
  if ((int)iIndex >= m_Items.GetCount())
  {
    throw PK_SystemException("The index of the item to be added to the Library is out of the Library size. Use Library.SetSize() to change the library size.'%s'.", __FILE__, __LINE__);
  }

  // Verifica se ja existe um objecto nessa posicao
  if (m_Items[iIndex] != NULL)
  {
    throw PK_SystemException("Cannot add item at index '%d' because there's already an item in that position.", __FILE__, __LINE__, iIndex);
  }

  // Verifica se o item ja esta na library
  if (Contains(item))
  {
    throw PK_SystemException("Scene Control Library already contains the item named '%s'.", __FILE__, __LINE__, item.GetName().c_str());
  }

  // Verifica se o controlo ja esta na library
  if (Contains(item.GetControl()))
  {
    throw PK_SystemException("Scene Control Library already contains the Scene Control named '%s'.", __FILE__, __LINE__, item.GetControl().GetName().c_str());
  }

  m_Items[iIndex] =&item;
  item.Grab();
}

//
bool PK_Library::Contains(PK_LibraryItem &item)
{
    for(int i = 0;  i < m_Items.GetCount(); i++)
    {
        if (&item == m_Items[i])
        {
            return true;
        }
    }

    return false;
}

//
bool PK_Library::Contains(PK_SceneControl &control)
{
  for(int i = 0;  i < m_Items.GetCount(); i++)
  {
    if (m_Items[i] != NULL && (&control == &m_Items[i]->GetControl()))
    {
        return true;
    }
  }

  return false;
}

//
void PK_Library::RemoveAllItems()
{
  // Faz o release de todos os items
  for(int  i = 0; i < m_Items.GetCount(); i++)
  {
    if (m_Items[i] != NULL)
    {
        m_Items[i]->Release();
        m_Items[i] = NULL;
    }
  }
}
 
//
void PK_Library::RemoveItemsInScope(PK_eLibraryItemScope scope)
{  
  for(int  i = 0; i < m_Items.GetCount(); i++)
  {
    if (m_Items[i] != NULL && m_Items[i]->GetScope() == scope)
    {
      m_Items[i]->Release();
      m_Items[i] = NULL;
    }
  }
}

//
void PK_Library::AddItemsToLoader(PK_ObjectLoader &loader)
{
    for(int  i = 0; i < m_Items.GetCount(); i++)
    {
        if (m_Items[i] != NULL && !m_Items[i]->IsLoaded())
        {
            loader.AddToQueue(*m_Items[i]);
        }
    }
}

} // namespace