add_library (
    ${PROJECT_NAME}
    JoyShockLibrary.cpp    JoyShockLibrary.h
        jscontroller/JoyShockController.h helpers/CRC32.cpp helpers/CRC32.h jscontroller/controllers/JSDualShock4.cpp jscontroller/controllers/JSDualShock4.h jscontroller/controllers/JSSwitch.cpp jscontroller/controllers/JSSwitch.h jscontroller/controllers/JSDualSense.cpp jscontroller/controllers/JSDualSense.h jscontroller/JoyShockController.cpp jscontroller/ControllerExceptions.h)

target_include_directories (
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries (
    ${PROJECT_NAME} ${JSL_PLATFORM_DEPENDENCY_VISIBILITY}
    JSL_Platform::Dependencies
)
