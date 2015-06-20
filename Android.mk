LOCAL_PATH := $(call my-dir)

oneiroi_src_files := \
	main.cpp \
	oneiroi.cpp \
	helpers.cpp

include $(CLEAR_VARS)
LOCAL_MODULE := oneiroi

LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := $(oneiroi_src_files)

include external/stlport/libstlport.mk

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include

LOCAL_CPPFLAGS += -std=c++11

LOCAL_SHARED_LIBRARIES := libc libstdc++ libstlport

LOCAL_MODULE_PATH := $(TARGET_OUT_OPTIONAL_EXECUTABLES)
include $(BUILD_EXECUTABLE)
