include $(CLEAR_VARS)
LOCAL_MODULE := pandorykey
LOCAL_LDLIBS := -llog -lm
LOCAL_CFLAGS := -O3 -UNDEBUG
LOCAL_CPPFLAGS := -std=c++17
LOCAL_SRC_FILES := main.cpp
include $(BUILD_EXECUTABLE)