#ifndef _PK_DATAFILEFIELD_H_
#define _PK_DATAFILEFIELD_H_

#include <typeinfo>
#include "PK_Consts.h"
#include "PK_Object.h"
#include "PK_String.h"
#include "PK_Types.h"
#include "PK_tSize.h"
#include "PK_Color.h"
#include "PK_Vector3.h"
#include "PK_Vector2.h"
#include "PK_tAABoundingSquare.h"
#include "PK_Exceptions.h"
#include "PK_TypeConverters.h"

namespace PK {

// DataFileField ()
// Representa um campo num registo DataFileRecord
// Os campos t�m um valor predefinido definido pelo campo m_iValueType
// Caso se pretenda adicionar suporte para mais algum tipo (tipos compostos como Vector), � necess�rio alterar
// Apenas devem ser adicionados base types (int, bool, etc) e structs com base types
class PK_DataFileField : public PK_Object
{
  // Estruturas internas ao DataField, (wrappers para as estruturas do engine)
  struct dfSize
  {
    float w, h;
  };
  struct dfResolution
  {
    int w, h;
  };
  struct dfColor
  {
    float r, g, b, a;
  };
  struct dfVector3
  {
    float x, y, z;
  };
  struct dfVector2
  {
    float x, y;
  };
  struct dfRect
  {
    float x, y;
    float w, h;
  };

	PK_eDataFieldType m_valueType;
	union		
	{
		int			   intValue;
        int        enumValue;
		float		   floatValue;
		bool		   boolValue;
		dfSize		 sizeValue;
		dfColor		 colorValue;
		dfVector3  vector3Value;
		dfVector2  vector2Value;
        dfRect     rcValue;
        dfResolution resolutionValue;
	} m_Value;

	PK_String m_sValue;

public:
	PK_DataFileField();
  PK_DataFileField(PK_String sName);

    // Int
	inline void SetValue_Int(int value)
	{
		m_Value.intValue = value;
		m_valueType = DataFieldType_Int;
	}

    // Float
	inline void SetValue_Float(float value)
	{
		m_Value.floatValue = value;
		m_valueType = DataFieldType_Float;
	}

    // Str
	inline void SetValue_Str(const PK_String &sValue)
	{
		m_sValue = sValue;
		m_valueType = DataFieldType_Str;
	}

    // Size
    inline void SetValue_Size(const PK_tSize & size)
	{
		m_Value.sizeValue.w = size.w;
		m_Value.sizeValue.h = size.h;
		m_valueType = DataFieldType_Size;
	}

	// bool
	inline void SetValue_Bool(bool value)
	{
		m_Value.boolValue = value;
		m_valueType = DataFieldType_Bool;
	}
	
	// Color
	inline void SetValue_Color(const PK_Color &value)
	{
		m_Value.colorValue.r = value.r;
		m_Value.colorValue.g = value.g;
		m_Value.colorValue.b = value.b;
		m_Value.colorValue.a = value.a;
		m_valueType = DataFieldType_Color;
	}
		
	// Vector3
	inline void SetValue_Vector3(const PK_Vector3 &value)
	{
		m_Value.vector3Value.x = value.x;
		m_Value.vector3Value.y = value.y;
		m_Value.vector3Value.z = value.z;
		m_valueType = DataFieldType_Vector3;
	}

    // Vector2
	inline void SetValue_Vector2(const PK_Vector2 &value)
	{
		m_Value.vector2Value.x = value.x;
		m_Value.vector2Value.y = value.y;
		m_valueType = DataFieldType_Vector2;
	}
    		
	// BoundingSquare
	inline void SetValue_Rect(const PK_tAABoundingSquare &value)
	{
        m_Value.rcValue.x = value.vPosition.x;
        m_Value.rcValue.y = value.vPosition.y;
        m_Value.rcValue.w = value.size.w;
        m_Value.rcValue.h = value.size.h;
		m_valueType = DataFieldType_Rect;
	}
    
    // Resolution
	inline void SetValue_Resolution(PK_tResolution value)
	{
        m_Value.resolutionValue.w = value.w;
        m_Value.resolutionValue.h = value.h;
		m_valueType = DataFieldType_Resolution;
	}
    
    // Enum
	inline void SetValue_Enum(int value)
	{
        m_Value.enumValue =	value;
        m_valueType = DataFieldType_Enum;
	}

	inline PK_eDataFieldType GetDataFieldType() { return m_valueType; }

public:


    // Especializacoes para GetValue()

    template<typename T> T GetEnumValue()
    {
        switch(m_valueType)
        {
                // Se o tipo actual ja e int, so temos que devolver
            case DataFieldType_Enum:
                break;
                
                // Se for string temos que converter
            case DataFieldType_Str:
                SetValue_Enum(PK_TypeConverters::StrToEnum<T>(m_sValue));
                break;
                
            default:
                throw PK_DataFieldFormatException(m_valueType, DataFieldType_Enum, __FILE__, __LINE__);
                
        }
        return (T)m_Value.enumValue;
    }

    // Devolve o valor como int

    int GetValue_Int();
    bool GetValue_Bool();
    float GetValue_Float();
    inline PK_String GetValue_String() { return m_sValue; }
    PK_Color GetValue_Color();
    PK_Vector3 GetValue_Vector3();
    PK_Vector2 GetValue_Vector2();
    PK_tSize GetValue_Size();
    PK_tAABoundingSquare GetValue_AABoundingSquare();
    PK_tResolution GetValue_Resolution();

};

} // namespace PK
#endif
