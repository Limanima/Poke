
LOCAL_PATH := $(call my-dir)

 
include $(CLEAR_VARS)

LOCAL_MODULE := Box2D

BOX2D_PATH := ./src/Box2D

LOCAL_C_INCLUDES := $(NDK_ROOT)/sources/cxx-stl/stlport/stlport \
                    $(LOCAL_PATH)/src
					 
# Add your application source files here...
LOCAL_SRC_FILES := $(BOX2D_PATH)/Collision/b2BroadPhase.cpp \
                   $(BOX2D_PATH)/Collision/b2CollideCircle.cpp \
                   $(BOX2D_PATH)/Collision/b2CollideEdge.cpp \
                   $(BOX2D_PATH)/Collision/b2CollidePolygon.cpp \
                   $(BOX2D_PATH)/Collision/b2Collision.cpp \
                   $(BOX2D_PATH)/Collision/b2Distance.cpp \
                   $(BOX2D_PATH)/Collision/b2DynamicTree.cpp \
                   $(BOX2D_PATH)/Collision/b2TimeOfImpact.cpp \
                   $(BOX2D_PATH)/Collision/Shapes/b2ChainShape.cpp \
                   $(BOX2D_PATH)/Collision/Shapes/b2CircleShape.cpp \
                   $(BOX2D_PATH)/Collision/Shapes/b2EdgeShape.cpp \
                   $(BOX2D_PATH)/Collision/Shapes/b2PolygonShape.cpp \
                   $(BOX2D_PATH)/Common/b2BlockAllocator.cpp \
                   $(BOX2D_PATH)/Common/b2Draw.cpp \
                   $(BOX2D_PATH)/Common/b2Math.cpp \
                   $(BOX2D_PATH)/Common/b2Settings.cpp \
                   $(BOX2D_PATH)/Common/b2StackAllocator.cpp \
                   $(BOX2D_PATH)/Common/b2Timer.cpp \
                   $(BOX2D_PATH)/Dynamics/b2Body.cpp \
                   $(BOX2D_PATH)/Dynamics/b2ContactManager.cpp \
                   $(BOX2D_PATH)/Dynamics/b2Fixture.cpp \
                   $(BOX2D_PATH)/Dynamics/b2Island.cpp \
                   $(BOX2D_PATH)/Dynamics/b2World.cpp \
                   $(BOX2D_PATH)/Dynamics/b2WorldCallbacks.cpp \
                   $(BOX2D_PATH)/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
                   $(BOX2D_PATH)/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
                   $(BOX2D_PATH)/Dynamics/Contacts/b2CircleContact.cpp \
                   $(BOX2D_PATH)/Dynamics/Contacts/b2Contact.cpp \
                   $(BOX2D_PATH)/Dynamics/Contacts/b2ContactSolver.cpp \
                   $(BOX2D_PATH)/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
                   $(BOX2D_PATH)/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
                   $(BOX2D_PATH)/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
                   $(BOX2D_PATH)/Dynamics/Contacts/b2PolygonContact.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2DistanceJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2FrictionJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2GearJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2Joint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2MotorJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2MouseJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2PrismaticJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2PulleyJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2RevoluteJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2RopeJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2WeldJoint.cpp \
                   $(BOX2D_PATH)/Dynamics/Joints/b2WheelJoint.cpp \
                   $(BOX2D_PATH)/Rope/b2Rope.cpp \
                   $(BOX2D_PATH)/b2pk_Settings.cpp
	               
LOCAL_SHARED_LIBRARIES := 

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

LOCAL_CFLAGS += -D_STLP_USE_NEWALLOC -DDEBUG -fexceptions

APP_CFLAGS += -g -ggdb 

include $(BUILD_SHARED_LIBRARY)
