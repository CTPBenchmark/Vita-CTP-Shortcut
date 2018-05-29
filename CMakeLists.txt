cmake_minimum_required(VERSION 2.8)

# VitaSDK defines
if( NOT DEFINED CMAKE_TOOLCHAIN_FILE )
  if( DEFINED ENV{VITASDK} )
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

# Project start
set(SHORT_NAME ctp_shortcut)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)
set(VITA_APP_NAME "Custom Protocol")
set(VITA_TITLEID  "VCTP12345")
set(VITA_VERSION  "02.00")
set(PSVITAIP  "192.168.1.19")
set(VITA3K_PATH "/Applications/Vita3K.app/Contents/MacOS/Vita3K")
# Flags and includes
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -Wno-unused-variable -Wno-unused-but-set-variable -fno-lto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")
set(VITA_MAKE_FSELF_FLAGS "${VITA_MAKE_FSELF_FLAGS} -a 0x2800000000000001")

include_directories(
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

# Builds
FUNCTION(ADD_RESOURCES out_var)
  SET(result)
  FOREACH(in_f ${ARGN})
    SET(out_f "${CMAKE_CURRENT_BINARY_DIR}/${in_f}.o")
    GET_FILENAME_COMPONENT(out_dir ${out_f} DIRECTORY)
    ADD_CUSTOM_COMMAND(OUTPUT ${out_f}
      COMMAND ${CMAKE_COMMAND} -E make_directory ${out_dir}
      COMMAND ${CMAKE_LINKER} -r -b binary -o ${out_f} ${in_f}
      DEPENDS ${in_f}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      COMMENT "Building resource ${out_f}"
      VERBATIM
      )
    LIST(APPEND result ${out_f})
  ENDFOREACH()
  SET(${out_var} "${result}" PARENT_SCOPE)
ENDFUNCTION()

file(GLOB res_files RELATIVE
  ${CMAKE_SOURCE_DIR}
  img/*.png
)
add_resources(ctp_res ${res_files})

add_executable(${SHORT_NAME}
  ${ctp_res}
  src/main.cpp
  src/Menu.cpp
        src/Engine.cpp
        src/Background.cpp
        src/Buttons.cpp
        src/Checkbox.cpp
        src/Keyboard.cpp
        )

target_link_libraries(${SHORT_NAME}
    vita2d
    SceDisplay_stub
    SceGxm_stub
    SceSysmodule_stub
    SceCtrl_stub
    ScePgf_stub
    ScePvf_stub
    SceCommonDialog_stub
    SceHttp_stub
        SceIme_stub
        SceIofilemgr_stub
        SceNetCtl_stub
    SceAppMgr_Stub
    freetype
    png
    z
    m
    SceTouch_stub
        SceAppUtil_stub
        c
    stdc++
    gcc
    jansson
)

# Create Vita artifacts
vita_create_self(eboot.bin ${SHORT_NAME})
vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} eboot.bin
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE  sce_sys/icon0.png sce_sys/icon0.png
        sce_sys/livearea/pic0.png sce_sys/livearea/pic0.png
        sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
        sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
        sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)

add_custom_target(send
  COMMAND curl -T eboot.bin ftp://${PSVITAIP}:1337/ux0:/app/${VITA_TITLEID}/
  DEPENDS eboot.bin
)

add_custom_target(copy
  COMMAND cp eboot.bin F:/app/${VITA_TITLEID}/eboot.bin
  DEPENDS eboot.bin
)

add_custom_target(send_vpk
  COMMAND curl -T ${SHORT_NAME}.vpk ftp://${PSVITAIP}:1337/ux0:/data/
  DEPENDS ${SHORT_NAME}.vpk
)

add_custom_target(copy_vpk
  COMMAND cp ${SHORT_NAME}.vpk F:/data/${VITA_TITLEID}/${SHORT_NAME}.vpk
  DEPENDS ${SHORT_NAME}.vpk
)

add_custom_target(emulator
  COMMAND ${VITA3K_PATH} ${CMAKE_CURRENT_BINARY_DIR}/${SHORT_NAME}.vpk
  DEPENDS ${SHORT_NAME}.vpk
)

