#include <stdlib.h>
#include "PK_DataFileField.h"
#include "PK_Exceptions.h"
#include "PK_TypeConverters.h"

namespace PK {

PK_DataFileField::PK_DataFileField(PK_String sName)
{
	SetTypeName("PK_DataFileField");
	SetName(sName);
	m_valueType = DataFieldType_Undef;
    
  // Limpar todos os campos da union
  m_Value.intValue = 0;
  m_Value.boolValue = 0;
}


//----------------------------------------------
int PK_DataFileField::GetValue_Int()
{
  switch(m_valueType)
  {
      // Se o tipo actual ja e int, so temos que devolver
      case DataFieldType_Int:
          break;
          
      // Se for string temos que converter
      case DataFieldType_Str:
          SetValue_Int(atoi(m_sValue.c_str()));
          break;
          
      // Se for outro tipo, para ja devolvemos erro, mas no futuro pode-se implementar outras conversoes...
      default:
          throw PK_DataFieldFormatException(m_valueType, DataFieldType_Int, __FILE__, __LINE__);
          
  }
  
  return m_Value.intValue;
}


//----------------------------------------------
bool PK_DataFileField::GetValue_Bool()
{
  switch(m_valueType)
  {
      // Se o tipo actual ja e int, so temos que devolver
      case DataFieldType_Bool:
          break;
          
      // Se for string temos que converter
      case DataFieldType_Str:
          SetValue_Bool((m_sValue == PK_TRUE_STR));
          break;
          
      // Se for outro tipo, para ja devolvemos erro, mas no futuro pode-se implementar outras conversoes...
      default:
          throw PK_DataFieldFormatException(m_valueType, DataFieldType_Bool, __FILE__, __LINE__);
          
  }
  
  return m_Value.boolValue;
}

//----------------------------------------------
float PK_DataFileField::GetValue_Float()
{
  switch(m_valueType)
  {
      // Se o tipo actual ja e int, so temos que devolver
      case DataFieldType_Float:
          break;
          
      // Se for string temos que converter
      case DataFieldType_Str:
          SetValue_Float((float)atof(m_sValue.c_str()));
          break;
          
      // Se for outro tipo, para ja devolvemos erro, mas no futuro pode-se implementar outras conversoes...
      default:
          throw PK_DataFieldFormatException(m_valueType, DataFieldType_Float, __FILE__, __LINE__);
          
  }
  
  return m_Value.floatValue;
}

// ----------------------------------------------
PK_tSize PK_DataFileField::GetValue_Size()
{
  switch(m_valueType)
  {
      // Se o tipo actual ja e int, so temos que devolver
      case DataFieldType_Size:
          break;
          
      // Se for string temos que converter
      case DataFieldType_Str:
          SetValue_Size(PK_tSize::Parse(m_sValue));
          break;
          
      // Se for outro tipo, para ja devolvemos erro, mas no futuro pode-se implementar outras conversoes...
      default:
          throw PK_DataFieldFormatException(m_valueType, DataFieldType_Size, __FILE__, __LINE__);
  }
  
  return PK_tSize(m_Value.sizeValue.w, m_Value.sizeValue.h);
}


//----------------------------------------------
PK_Color PK_DataFileField::GetValue_Color()
{
  switch(m_valueType)
  {
      // Se o tipo actual ja e int, so temos que devolver
      case DataFieldType_Color:
          break;
          
      // Se for string temos que converter
      case DataFieldType_Str:
          SetValue_Color(PK_TypeConverters::StrToColor(m_sValue));
          break;
          
      // Se for outro tipo, para ja devolvemos erro, mas no futuro pode-se implementar outras conversoes...
      default:
          throw PK_DataFieldFormatException(m_valueType, DataFieldType_Color, __FILE__, __LINE__);
  }
  
  return PK_Color(m_Value.colorValue.r, m_Value.colorValue.g, m_Value.colorValue.b, m_Value.colorValue.a);
}

//----------------------------------------------
PK_Vector3 PK_DataFileField::GetValue_Vector3()
{
  switch(m_valueType)
  {
      // Se o tipo actual ja e int, so temos que devolver
      case DataFieldType_Vector3:
          break;
          
      // Se for string temos que converter
      case DataFieldType_Str:
          SetValue_Vector3(PK_TypeConverters::StrToVector3(m_sValue));
          break;
          
      // Se for outro tipo, para ja devolvemos erro, mas no futuro pode-se implementar outras conversoes...
      default:
          throw PK_DataFieldFormatException(m_valueType, DataFieldType_Vector3, __FILE__, __LINE__);
  }
  
  return PK_Vector3(m_Value.vector3Value.x, m_Value.vector3Value.y, m_Value.vector3Value.z);
}

//----------------------------------------------
PK_Vector2 PK_DataFileField::GetValue_Vector2()
{
  switch(m_valueType)
  {
      // Se o tipo actual ja e int, so temos que devolver
      case DataFieldType_Vector2:
          break;
          
      // Se for string temos que converter
      case DataFieldType_Str:
          SetValue_Vector2(PK_TypeConverters::StrToVector2(m_sValue));
          break;
          
      // Se for outro tipo, para ja devolvemos erro, mas no futuro pode-se implementar outras conversoes...
      default:
          throw PK_DataFieldFormatException(m_valueType, DataFieldType_Vector2, __FILE__, __LINE__);
  }
  
  return PK_Vector2(m_Value.vector2Value.x, m_Value.vector2Value.y);
}

//----------------------------------------------
PK_tAABoundingSquare PK_DataFileField::GetValue_AABoundingSquare()
{
  switch(m_valueType)
  {
      // Se o tipo actual ja e int, so temos que devolver
      case DataFieldType_Rect:
          break;
          
      // Se for string temos que converter
      case DataFieldType_Str:
          SetValue_Rect(PK_tAABoundingSquare::Parse(m_sValue));
          break;
          
      // Se for outro tipo, para ja devolvemos erro, mas no futuro pode-se implementar outras conversoes...
      default:
          throw PK_DataFieldFormatException(m_valueType, DataFieldType_Rect, __FILE__, __LINE__);
  }
  
  return PK_tAABoundingSquare(m_Value.rcValue.x, m_Value.rcValue.y, m_Value.rcValue.w, m_Value.rcValue.h);
}

//----------------------------------------------
PK_tResolution PK_DataFileField::GetValue_Resolution()
{
  switch(m_valueType)
  {
      // Se o tipo actual ja e int, so temos que devolver
      case DataFieldType_Resolution:
          break;
          
      // Se for string temos que converter
      case DataFieldType_Str:
          SetValue_Resolution(PK_tResolution::Parse(m_sValue));
          break;
          
      // Se for outro tipo, para ja devolvemos erro, mas no futuro pode-se implementar outras conversoes...
      default:
          throw PK_DataFieldFormatException(m_valueType, DataFieldType_Resolution, __FILE__, __LINE__);
          
  }
  
  return PK_tResolution(m_Value.resolutionValue.w, m_Value.resolutionValue.h);
}

} // namespace PK 