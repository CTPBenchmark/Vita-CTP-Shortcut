cmake_minimum_required(VERSION 3.11)

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


set(PSVITAIP  "192.168.0.192")

#Download and install externals dependencies only the first cmake load
include(FetchContent)
FetchContent_Declare(
        unilib
        GIT_REPOSITORY https://github.com/ufal/unilib.git
        GIT_TAG        v3.1.1
)
FetchContent_Declare(
        icon-font-cpp-headers
        GIT_REPOSITORY https://github.com/juliettef/IconFontCppHeaders
)

FetchContent_Declare(
        materialdesign-webfont
        GIT_REPOSITORY https://github.com/Templarian/MaterialDesign-Webfont.git
        GIT_TAG        v3.6.95
)

FetchContent_Populate(unilib)
FetchContent_Populate(icon-font-cpp-headers)
FetchContent_Populate(materialdesign-webfont)

FetchContent_GetProperties(unilib)
FetchContent_GetProperties(icon-font-cpp-headers)
FetchContent_GetProperties(materialdesign-webfont)

#Unilib
if(NOT unilib_POPULATED)
    set(UNILIB_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/src/kit/lib/unilib/)
    file(REMOVE_RECURSE ${UNILIB_LOCATION}*)
    file(COPY
            ${unilib_SOURCE_DIR}/unilib/unicode.cpp
            DESTINATION ${UNILIB_LOCATION}
    )
    file(COPY
            ${unilib_SOURCE_DIR}/unilib/unicode.h
            DESTINATION ${UNILIB_LOCATION}
            )
    file(COPY
            ${unilib_SOURCE_DIR}/unilib/utf8.cpp
            DESTINATION ${UNILIB_LOCATION}
            )
    file(COPY
            ${unilib_SOURCE_DIR}/unilib/utf8.h
            DESTINATION ${UNILIB_LOCATION}
            )
    file(COPY
            ${unilib_SOURCE_DIR}/LICENSE
            DESTINATION ${UNILIB_LOCATION}
            )
endif()

#IconFontCppHeaders
if(NOT icon-font-cpp-headers_POPULATED)
    set(IFCH_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/src/kit/lib/IconFontCppHeaders)
    file(REMOVE_RECURSE ${IFCH_LOCATION}*)
    file(COPY
            ${icon-font-cpp-headers_SOURCE_DIR}/IconsMaterialDesignIcons.h
            DESTINATION ${IFCH_LOCATION}
            )
    file(COPY
            ${icon-font-cpp-headers_SOURCE_DIR}/licence.txt
            DESTINATION ${IFCH_LOCATION}
            )
endif()

#MaterialDesign Webfont
if(NOT materialdesignicons-webfont_POPULATED)
    set(MDI_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/mdi/)
    file(REMOVE_RECURSE ${MDI_LOCATION}*)
    file(COPY
            ${materialdesign-webfont_SOURCE_DIR}/fonts/materialdesignicons-webfont.ttf
            DESTINATION ${MDI_LOCATION}
    )
    file(COPY
            ${materialdesign-webfont_SOURCE_DIR}/license.md
            DESTINATION ${MDI_LOCATION}
            )
endif()


#Vita3K PATHS
set(VITA3K_APP_PATH "/Applications/Vita3K.app/Contents/MacOS/Vita3K")
set(VITA3K_FOLDER_PATH "/Users/Applelo/Library/Application\ Support/Vita3K/Vita3K/ux0/app/${VITA_TITLEID}")

set(ENV{PKG_CONFIG_PATH} "$ENV{VITASDK}/arm-vita-eabi/lib/pkgconfig")
include(FindPkgConfig)

find_package(Git)
if(NOT Git_FOUND)
    message(WARNING "Git not found, using unknown as tag...")
    add_definitions(-DGIT_COMMIT="unknown")
else()
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            OUTPUT_VARIABLE DGIT_COMMIT
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
    )

    add_definitions(-DGIT_COMMIT="${DGIT_COMMIT}")
endif()

# Flags and includes
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fpermissive -std=gnu11 -Wall ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -std=c++11 -Wall ")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")
set(VITA_MAKE_FSELF_FLAGS "${VITA_MAKE_FSELF_FLAGS} -a 0x2800000000000001")

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
pkg_check_modules(CURLPP REQUIRED curlpp)

include_directories(
        src/
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

        src/kit/lib/unilib/unicode.cpp
        src/kit/lib/unilib/utf8.cpp

        src/app/Ui.cpp
        src/app/Utils.cpp

        src/app/kit_override/core/CustomApp.cpp

        src/kit/ui/UiTheme.cpp
        src/kit/ui/UiIcons.cpp
        src/kit/ui/UiButtons.cpp
        src/kit/ui/UiTexts.cpp
        src/kit/ui/parent/UiParentBoxes.cpp
        src/kit/ui/UiCheckboxes.cpp
        src/kit/ui/UiTextFields.cpp
        src/kit/ui/UiCards.cpp

        src/kit/utils/UtilsI18n.cpp
        src/kit/utils/UtilsIME.cpp
        src/kit/utils/UtilsPad.cpp
        src/kit/utils/UtilsTouch.cpp
        src/kit/utils/UtilsPadTouchCtrl.cpp
        src/kit/utils/UtilsScroll.cpp

        src/app/ui/Background.cpp
        src/app/ui/LayoutTheme.cpp
        src/app/ui/LayoutTheme.hh

        src/app/utils/Config.cpp
        src/app/utils/WebModal.cpp
        src/app/utils/CTPApi.cpp
        src/app/utils/Singleton.cpp
        src/app/utils/CTPApiThread.cpp

        src/app/views/Welcome.cpp
        src/app/views/settings/Settings.cpp
        src/app/views/settings/Customization.cpp

        src/main.cpp
        )

target_link_libraries(${SHORT_NAME}
        vita2d
        SceDisplay_stub
        SceGxm_stub
        ScePvf_stub
        SceCtrl_stub
        SceTouch_stub
        SceCommonDialog_stub
        SceAppUtil_stub
        SceAppMgr_stub
        SceRegistryMgr_stub
        SceSysmodule_stub
        jansson
        freetype
        png
        jpeg
        z
        m
        c
        SceNet_stub
        SceNetCtl_stub
        SceHttp_stub
        SceSsl_stub
        ${CURLPP_LDFLAGS}
        ${CURL_LIBRARIES}
        ${OPENSSL_LIBRARIES}
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
