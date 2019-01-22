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
set(SHORT_NAME CTP_Shortcut)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)
set(VITA_APP_NAME "Custom Protocol")
set(VITA_TITLEID  "VCTP12345")
set(VITA_VERSION  "02.00")

set(PSVITAIP  "192.168.1.37")

#Vita3K PATHS
set(VITA3K_APP_PATH "/Applications/Vita3K.app/Contents/MacOS/Vita3K")
set(VITA3K_FOLDER_PATH "/Users/Applelo/Library/Application\ Support/Vita3K/Vita3K/ux0/app/${VITA_TITLEID}")


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
        assets/img/*.png
)
add_resources(ctp_res ${res_files})

add_executable(${SHORT_NAME}
  ${ctp_res}
        src/kit/core/App.cpp
        src/kit/core/ViewsController.cpp
        src/kit/core/View.cpp
        src/kit/core/UiEvent.cpp

        src/kit/Ui.cpp
        src/kit/Utils.cpp

        src/kit_override/core/CustomApp.cpp

        src/kit/ui/UiTheme.cpp
        src/kit/ui/UiIcons.cpp
        src/kit/ui/UiButtons.cpp
        src/kit/ui/UiTexts.cpp

        src/kit/utils/I18n.cpp
        src/kit/utils/IME.cpp
        src/kit/utils/Pad.cpp
        src/kit/utils/Touch.cpp

        src/ui/Background.cpp

        src/views/Welcome.cpp

        src/main.cpp
        src/ui/LayoutTheme.cpp src/ui/LayoutTheme.hh src/utils/Config.cpp src/utils/Config.hh)

target_link_libraries(${SHORT_NAME}
        vita2d
        SceDisplay_stub
        SceGxm_stub
        SceSysmodule_stub
        SceCtrl_stub
        SceTouch_stub
        SceCommonDialog_stub
        SceAppUtil_stub
        SceRegistryMgr_stub
        jansson
        freetype
        png
        jpeg
        z
        m
        c
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

        assets/fonts/mdi/materialdesignicons-webfont.ttf assets/fonts/mdi/materialdesignicons-webfont.ttf
        assets/fonts/Roboto/Roboto-Black.ttf        assets/fonts/Roboto/Roboto-Black.ttf
        assets/fonts/Roboto/Roboto-BlackItalic.ttf  assets/fonts/Roboto/Roboto-BlackItalic.ttf
        assets/fonts/Roboto/Roboto-Bold.ttf         assets/fonts/Roboto/Roboto-Bold.ttf
        assets/fonts/Roboto/Roboto-BoldItalic.ttf   assets/fonts/Roboto/Roboto-BoldItalic.ttf
        assets/fonts/Roboto/Roboto-Italic.ttf       assets/fonts/Roboto/Roboto-Italic.ttf
        assets/fonts/Roboto/Roboto-Light.ttf        assets/fonts/Roboto/Roboto-Light.ttf
        assets/fonts/Roboto/Roboto-LightItalic.ttf  assets/fonts/Roboto/Roboto-LightItalic.ttf
        assets/fonts/Roboto/Roboto-Medium.ttf       assets/fonts/Roboto/Roboto-Medium.ttf
        assets/fonts/Roboto/Roboto-MediumItalic.ttf assets/fonts/Roboto/Roboto-MediumItalic.ttf
        assets/fonts/Roboto/Roboto-Regular.ttf      assets/fonts/Roboto/Roboto-Regular.ttf
        assets/fonts/Roboto/Roboto-Thin.ttf         assets/fonts/Roboto/Roboto-Thin.ttf
        assets/fonts/Roboto/Roboto-ThinItalic.ttf   assets/fonts/Roboto/Roboto-ThinItalic.ttf

        i18n/en_us.json i18n/en_us.json
        i18n/fr.json i18n/fr.json
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

add_custom_target(emulate
        COMMAND cp eboot.bin ${VITA3K_FOLDER_PATH}/eboot.bin
        COMMAND ${VITA3K_APP_PATH} -r ${VITA_TITLEID}
        DEPENDS eboot.bin
        )

add_custom_target(emulate_vpk
        COMMAND ${VITA3K_APP_PATH} ${CMAKE_CURRENT_BINARY_DIR}/${SHORT_NAME}.vpk
        DEPENDS ${SHORT_NAME}.vpk
        )
