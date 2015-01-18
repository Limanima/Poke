#ifndef _PK_LIBRARY_H_
#define _PK_LIBRARY_H_

#include "PK_Object.h"
#include "PK_Types.h"
#include "PK_List.h"
#include "PK_ObjectLoader.h"
#include "PK_Exceptions.h"
#include "PK_LibraryItem.h"

namespace PK {


/// Livraria de objectos.
/**
 * A Livraria mantem um reposit�rio de objectos do tipo PK_SceneControl. Este repositorio pode ser utilizado pela aplica��o
 * para criar c�pias de objectos que estejam no reposit�rio. Para utilizar a library, a aplica��o deve criar instancias de objectos
 * e adicionar na Library com AddItem(). Isto deve ser feito na fase de load das scenes, isto porque o Poke vai fazer o load dos objectos
 * que estiverem carregados na library no final da fase de load.
 * Na fase de update, a aplica��o pode requisitar na Library c�pias de objectos. A grande vantagem deste modelo � que se evita load de objectos
 * durante o update, isto porque a library faz uma c�pia do objecto e devolve a c�pia, portanto todos os resources que tenham sido carregados 
 * no original passam para a c�pia. Nem o m�todo OnLoad nem o m�todo OnInitialize s�o executados na c�pia.
 * No entanto os m�todos OnLoad e OnInitialize s�o executados no original no final da fase de loading da scene group.
 * Por raz�es de performance, a Library contem um array e n�o uma lista para guardar os objectos, sendo de tamanho limitado. O tamanho pode ser 
 * alterado atrav�s do m�todo SetSize().
*/
class PK_Library : public PK_Object
{
private:
	PK_Array<PK_LibraryItem *> m_Items;

public:
	PK_Library(const PK_String &sName = "");
	~PK_Library();

public:
    /// Altera o tamanho da library.
    void SetSize(unsigned int iSize);
    /// Adiciona um novo objecto � library - overloading 1.
    /** Caso o objecto j� esteja na library, � lan�ada uma excepcao. */  
    void AddItem(PK_eLibraryItemScope scope, PK_SceneControl &control, unsigned int iIndex, const PK_String &sName);
    /// Adiciona um item a library  - overloading 2.
    /** Caso o objecto j� esteja na library, � lan�ada uma excepcao. */  
    void AddItem(PK_LibraryItem &item, unsigned int iIndex);
    /// Verifica se o item ja esta na library.  
    bool Contains(PK_LibraryItem &item);
    /// Verifica se o Scene Control ja esta em algum item na library.
    bool Contains(PK_SceneControl &control);
    /// Remove todos os items.
    void RemoveAllItems();
    /// Remove os items no scope especificado.
    void RemoveItemsInScope(PK_eLibraryItemScope scope);
    /// Devolve uma instancia do objecto na posicao iIndex do array.
    template <class T> T & GetControlInstance(unsigned int iIndex)
    {
        // Verifica se o index esta dentro do array
        if ((int)iIndex >= m_Items.GetCount())
        {
            throw PK_SystemException("Cannot create control instance because the index '%d' of the bounds of the Library.", __FILE__, __LINE__, iIndex);
        }

        if (m_Items[iIndex] == NULL)
        {
        throw PK_SystemException("Cannot create control instance because there's no item in the Library at index '%d'", __FILE__, __LINE__, iIndex);
        }
         
        T *p = new T();
        p->Copy(m_Items[iIndex]->GetControl());
        p->InternalInitialize();
        return *p;
    }

    /// Devolve uma instancia do objecto por nome do item na Library.
    /** Aconselha-se a utilizacao do overloading GetControlInstance(int iIndex) por ser mais rapido.
    * Este metodo tem que percorrer a library e pesquisar por nome, o outro overloading vai directo a posicao do array*/
    template <class T> T & GetControlInstance(const PK_String &sItemName)
    {
     for(unsigned int  i = 0; i < m_Items.GetCount(); i++)
      {
        if (m_Items[i] != NULL && m_Items[i]->GetName() == sItemName)
        {
            T *p = new T();
            p->Copy(m_Items[i]->GetControl());
            p->InternalInitialize();
            return *p;
        }
      }

      throw PK_SystemException("Could not create control instance because the library item named '%s' does not exist.", __FILE__, __LINE__, sItemName.c_str());
    }

    /// Adicionar numa queue de loading todos os objectos que estejam por carregar.
    void AddItemsToLoader(PK_ObjectLoader &loader);
};

} // namespace

#endif