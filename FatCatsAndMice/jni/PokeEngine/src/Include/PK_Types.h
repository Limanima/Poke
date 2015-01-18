#ifndef _PK_TYPES_H_
#define _PK_TYPES_H_

#include "PK_String.h"
#include "PK_Vector2.h"
#include "PK_tBoundingSquare.h"
#include "PK_tBoundingCircle.h"
#include "PK_tSize.h"

namespace PK {

class PK_Body;
class PK_SceneControl;

enum PK_eAppType
{  
    AppType_Game,
    AppType_Console
};

enum PK_eMsgBoxResult
{
    MsgBoxResult_None,
    MsgBoxResult_Button1,
    MsgBoxResult_Button2,
    MsgBoxResult_Button3,
    MsgBoxResult_Yes = MsgBoxResult_Button2,
    MsgBoxResult_No =MsgBoxResult_Button1
    
};

    
enum PK_eGamerServicesProvider
{
	GamerServicesProvider_None,
	GamerServicesProvider_AppleGameCenter,
	GamerServicesProvider_GooglePlay
};

enum PK_eBuildType
{
    BuildType_Debug   = 0,
    BuildType_Release = 1
};

enum PK_eBlendMode
{
    BlendMode_None              = 0,
    BlendMode_AlphaTransparency = 1,
};

enum PK_ePivotAlignmentType
{
    PivotAlignment_Center       = 0,
    PivotAlignment_TopLeft      = 1,
    PivotAlignment_Top          = 2,
    PivotAlignment_TopRight     = 3,
    PivotAlignment_Right        = 4,
    PivotAlignment_BottomRight  = 5,
    PivotAlignment_Bottom       = 6,
    PivotAlignment_BottomLeft   = 7,
    PivotAlignment_Left         = 8,
    PivotAlignment_None         = 99
};

enum PK_eParentAlignmentFlags
{
    ParentAlignment_None         = 0x00,
    ParentAlignment_Horizontaly  = 0x01,
    ParentAlignment_Verticaly    = 0x02,
    ParentAlignment_Left         = 0x04,
    ParentAlignment_Top          = 0x08,
    ParentAlignment_Bottom       = 0x10,
    ParentAlignment_Right        = 0x20,
    ParentAlignment_Center = ParentAlignment_Horizontaly | ParentAlignment_Verticaly
};

enum PK_eDockStyleFlags
{
    DockStyle_None   = 0x00,
    DockStyle_Left   = 0x01,
    DockStyle_Top    = 0x02,
    DockStyle_Bottom = 0x04,
    DockStyle_Right  = 0x08,
    DockStyle_Fill   = 0x10
};

enum PK_eSceneControlRefreshFlags
{
  RefreshFlags_None                = 0x00000000,
  RefreshFlags_Alignment           = 0x00000001,
  RefreshFlags_Dock                = 0x00000001,
  RefreshFlags_Position            = 0x00000002,
  RefreshFlags_WorldPosition       = 0x00000004,
  RefreshFlags_WorldRotation       = 0x00000008,
  RefreshFlags_WorldScale          = 0x00000010,
  RefreshFlags_TransformMatrix     = 0x00000020,
  RefreshFlags_ClientRect          = 0x00000040,
  RefreshFlags_Pivot               = 0x00000080,
  RefreshFlags_BackgroundImage     = 0x00000100,
  RefreshFlags_ChildDocks          = 0x00000200,
  RefreshFlags_BlendedColor        = 0x00000400,
  RefreshFlags_BackgroundImageRect = 0x00000800,
  RefreshFlags_Size                = 0x00001000,
  RefreshFlags_PhysicsBody         = 0x00002000,
  RefreshFlags_CliRectPrimitiveData = 0x00004000,
  RefreshFlags_All                 = RefreshFlags_Alignment | 
                                     RefreshFlags_Position |
                                     RefreshFlags_WorldPosition |
                                     RefreshFlags_WorldRotation |
                                     RefreshFlags_WorldScale |
                                     RefreshFlags_TransformMatrix |
                                     RefreshFlags_ClientRect |
                                     RefreshFlags_Pivot |
                                     //RefreshFlags_BackgroundImage | -> Ha um bug com isto, isto limpa a imagem se nao esta setado o resource name
                                     RefreshFlags_ChildDocks |
                                     RefreshFlags_BlendedColor |
                                     RefreshFlags_BackgroundImageRect |
                                     RefreshFlags_Size |
                                     RefreshFlags_PhysicsBody |
									 RefreshFlags_CliRectPrimitiveData
};
    
enum PK_eAssetType
{
	AssetType_Texture,
	AssetType_SpriteSet,
	AssetType_Sprite,
	AssetType_SoundEffect,
	AssetType_Music,
	AssetType_Font,
	AssetType_ObjectProperties,
    AssetType_Settings,
	AssetType_Script,
    AssetType_File,
    AssetType_String
};
    
enum PK_eDataFieldType
{
  DataFieldType_Undef,
  DataFieldType_Int,
  DataFieldType_Str,
  DataFieldType_Size,
	DataFieldType_Bool,
	DataFieldType_Color,
	DataFieldType_Vector3,
	DataFieldType_Vector2,
	DataFieldType_Rect,
  DataFieldType_Float,
  DataFieldType_Resolution,
  DataFieldType_Enum
};

enum PK_eKeyCodeType
{
  KeyCode_Esc = 1,
  KeyCode_Back = 2,
};

enum PK_eInputActionType
{
  InputAction_None           = 0x0000,
  InputAction_Back           = 0x0001,
  InputAction_Clicked        = 0x0002,
  InputAction_LeftClicked    = 0x0004,
  InputAction_RightClicked   = 0x0008,
  InputAction_MiddleClicked  = 0x0010,
  InputAction_Flick          = 0x0080,
  InputAction_FlickEnded     = 0x0100,
};   

enum PK_eFlickActionType
{
  FlickAction_None           = 0x0000,
  FlickAction_Left           = 0x0001,
  FlickAction_Right          = 0x0002,
  FlickAction_Up             = 0x0004,
  FlickAction_Down           = 0x0008
};   

enum PK_ePlatformType
{
  Platform_Windows = 1,
  Platform_MacOS = 2,
  Platform_iOS = 3,
  Platform_Android = 4,
  Platform_WindowsPhone = 5,
};   

enum PK_eTransitionType
{
    TransitionType_None,
    TransitionType_Open,
    TransitionType_Close
};

enum PK_eSceneActionType
{
    SceneActionType_None,
    SceneActionType_PopUp,
    SceneActionType_Close,
    SceneActionType_NavigateTo,
    SceneActionType_GroupLoad,
    SceneActionType_OpenTransition,
    SceneActionType_CloseTransition,
    SceneActionType_RemoveTransition
};
    
enum PK_eDeviceOrientation
{
    DeviceOrientation_Portait,
    DeviceOrientation_Landscape
};

enum PK_eImageSizeMode
{
    ImageSizeMode_RealSize,   // Tamanho real da imagem
    ImageSizeMode_Fit,        // Fit o rect (pode alterar o aspect ratio
    ImageSizeMode_FitBigger,  // Fit o maior (altura ou largura). Mantem o aspect ratio
    ImageSizeMode_SizeControlToImage
};
    
enum PK_AdDock
{
    AdDock_Top,
    AdDock_Bottom
};
typedef enum PK_AdDock PK_tpAdDock;

enum PK_eBodyType
{
  BodyType_Static,
  BodyType_Dynamic,
  BodyType_UserControlable
};


enum PK_eLibraryItemScope
{
    LibraryItemScope_Global     = 0,
    LibraryItemScope_SceneGroup = 1,
    LibraryItemScope_Scene      = 2
};  

enum PK_eBodyPartShapeType
{
    BodyPartShape_None,
    BodyPartShape_Box,
    BodyPartShape_Circle
};

enum PK_eFileWriteOpenMode
{
    FileWriteOpenMode_CreateAlways,
    FileWriteOpenMode_Append
};

// Definicao de uma navegacao
struct PK_tSceneNavigation
{
    PK_String sName;  // Nome da nevegacao
    PK_String sGroupName; // Nome do grupo para onde navega
    PK_String sSceneName; // Nome da scene para onde navega
};

// Dados da scene dentro do grupo
struct PK_tSceneGroupItem
{
    PK_String sName;
};

// Dados do grupo
struct PK_tSceneGroup
{
    PK_String sName;
	unsigned int uiSceneCount;
    PK_tSceneGroupItem * scenes;

};
    
struct PK_tSceneAction
{
    PK_eSceneActionType actionType;
    PK_String sSceneName;
    void *param;
    bool bSyncronous; // In a sycronous action, the loop in PostQueuedScreenActions breaks in the action
};

// Representa um rectangulo dentro de uma textura
struct PK_tPrimitiveData;
struct PK_tTextureFrame
{
    PK_tBoundingSquare bsRect;
    PK_Vector2 textCoords[4];
	PK_tPrimitiveData  *FrameRenderData;
};

// Estrutura utilizada para o permitir ao utilizador associar dados a um SceneControl
struct PK_tSceneControlUserData
{
	union		
	{
		int			intValue;
	} value;
};
    
struct PK_tMargins
{
    float left, top, right, bottom;
    PK_tMargins() { }
    PK_tMargins(float l, float t, float r, float b)
    {
        Set(l, t, r, b);
    }
    inline void Set(float l, float t, float r, float b)
    {
        left = l;
        top = t;
        right = r;
        bottom = b;
    }
    inline bool operator!=(const PK_tMargins &margins)
    {
        return (left != margins.left || top != margins.top  || right != margins.right  || bottom != margins.bottom );
    }
    
    inline bool operator==(const PK_tMargins &margins)
    {
        return (left == margins.left && top == margins.top  && right == margins.right  && bottom == margins.bottom );
    }
};
  
// 
struct PK_tResolution
{
    int w, h;
    PK_tResolution() { }
    PK_tResolution(int width, int height)
    {
        Set(width, height);
    }
    inline void Set(int width, int height)
    {
        w = width;
        h = height;
    }
    static PK_tResolution Parse(const PK_String &str);
    bool IsZero() { return (w == 0 && h == 0); }
};


struct PK_tNamedResolution
{
    PK_String sName;
    PK_tResolution resolution;
};

struct PK_tBodyShapeCircle
{
    float xCenter, yCenter; // Nao usar PK_Vector porque e usado numa union
    float fRadius;
};

struct PK_tBodyShapeBox
{
     float width, height; // Nao usar PK_Vector porque e usado numa union
};


struct PK_tIPAddress
{
    union
    {
        unsigned char nibble[4];
        unsigned int ipv4;
    };
        
    PK_String ToStr() const
    {
        PK_String str;
        str.Format("%d.%d.%d.%d", nibble[0], nibble[1], nibble[2], nibble[3]);
        return str;
    }
};
    

enum PK_eControlBodyShapeMode
{
    ControlBodyShapeMode_UserDefined,
    ControlBodyShapeMode_Autoadjust
};

struct PK_t2DBodyPartDefinition
{
    union      
    {
        PK_tBodyShapeBox    box;
        PK_tBodyShapeCircle circle;
    } shape;

  PK_Vector2 vPivot;
  float fRotation;
  float fDensity;
  float fFriction;
  float fRestitution;
  unsigned short usCollisionBit;
  unsigned short usCollisionMask;
  unsigned short usCollisionGroup;
  PK_eBodyPartShapeType shapeType;

  PK_t2DBodyPartDefinition()
  {
    fRotation = 0.0f;
    shapeType = BodyPartShape_None;
    fDensity = 0.0f;
    fFriction = 0.2f;
    fRestitution = 0.5f;
    usCollisionBit = 0x0001;
    usCollisionMask = 0xFFFF;
    usCollisionGroup = 0;
    vPivot = PK_Vector2(0.0f, 0.0f);
  }

  void SetToBox(const PK_tSize &vSize)
  {
    SetToBox(vSize, PK_Vector2(0.0f, 0.0f));
  }

  void SetToBox(const PK_tSize &vSize, const PK_Vector2 &pivot)
  {
    shapeType = BodyPartShape_Box;
    shape.box.width = vSize.w;
    shape.box.height = vSize.h;
    vPivot = pivot;
  }

  void SetToCircle(float fRadius)
  {
    SetToCircle(fRadius, PK_Vector2(0.0f, 0.0f));
  }
  void SetToCircle(float fRadius, const PK_Vector2 pivot)
  {
    shapeType = BodyPartShape_Circle;
    shape.circle.xCenter = 0.0f;
    shape.circle.yCenter = 0.0f;
    shape.circle.fRadius = fRadius;
    vPivot = pivot;
  }
};

struct PK_tBodyDefinition
{
    PK_List<PK_t2DBodyPartDefinition> bodyParts;
    PK_eBodyType bodyType;
    PK_eControlBodyShapeMode shapeMode;

    PK_tBodyDefinition()
    {
        bodyType = BodyType_Dynamic;
        shapeMode = ControlBodyShapeMode_Autoadjust;
    }

    PK_tBodyDefinition(PK_eBodyType bodyType)
    {
        bodyType = bodyType;
        shapeMode = ControlBodyShapeMode_Autoadjust;
    }

    PK_tBodyDefinition(PK_eBodyType bodyType, PK_eControlBodyShapeMode mode)
    {
        bodyType = bodyType;
        shapeMode = mode;
    }
};

struct PK_tBodyCollisionMessage
{
    PK_Body *pBodyA;
    PK_Body *pBodyB;
};

struct PK_tRemoveControlMessage
{
    PK_SceneControl *pControl;
};

struct PK_tAddControlMessage
{
    PK_SceneControl *pControlToAdd;
    PK_SceneControl *pParent;
};

class PK_Object;
struct PK_tMessage1
{
	PK_Object *m_pSender;
	unsigned int uiMsg;
	unsigned int uiCode;
	unsigned long uiParam;
	PK_tMessage1() 
	{
		m_pSender = NULL;
	}
};

struct PK_tMessage
{
    union
    {
        PK_tBodyCollisionMessage bodyCollision;
        PK_tRemoveControlMessage removeControl;
        PK_tAddControlMessage    addControl;
   } detail;

    unsigned int uiType;
};


struct PK_tTimestamp
{
    unsigned short year;
    unsigned char  month;
    unsigned char  day;
    unsigned char  hour;
    unsigned char  minute;
    unsigned char  second;
    unsigned char  hundreths;
};

} // namespace

#endif
