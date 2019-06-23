# Changelog

## Version 0.7
* Add UiCard class
* Add UtilsScroll class to manage scroll elements
* Add support for scroll in UtilsPadTouchCtrl
* Improve RadioBoxes & Checkboxes functions with text to support changes (Text type & color)
* Remove UtilsTexts and revert all changes to UiTexts & UtilsIme to simplify the logic
* Move applyTextHeightLimit & applyTextWidthLimit of TextFields into UiTexts
* Rename applyTextHeightLimit to applyTextHeightLimitCut and improve the function
* Add possibility to choose a start value in UtilsPadTouchCtrl
* Improve UtilsPadTouchCtrl class to update value
* Increase size of the float button (without text)
* Add PSVita Icons in UiIcons class (don't work with Vita3K)
* Improve CMakeLists for better readability and to download/update dependencies (material design icons, icons font cpp headers, unilib)
* Add Travis CI (thanks @gnuton for the Travis CI setup and the docker image for PSVita homebrews)
* Add debug function and mode (auto by default, ctrl, touch) for UtilsPadTouchCtrl
* Update Material Design Icons
* Fixes everywhere, every commit

## Version 0.6
* Add RadioBoxes class
* Improve Checkbox class
* Add simple PadTouchController class for menu
* Add mounted function in View
* Improve IME class
* Fix Pad (padButtons.clicking was not added)
* Fix uppercase to work with all unicode char thanks to unilib
* Add UtilsTexts class with uppercase, lowercase functions & utf8ToUtf16/utf16ToUtf8
* All functions in utils have been renamed (Pad to UtilsPad for example)

## Version 0.5.3
* Add TextFields class (filledDraw only)
* Improve theme (in all ui components) to match with Material Design
* Add dynamic font imports for texts (fix size issue & load only fonts needed)
* Add missing function in UiTexts class
* Improve IME functions
* Add beforeEnter and beforeExit functions in View triggered in view change
* Add text fields sample

## Version 0.5.2
* Add Checkbox class
* Improve Theme class
* Add checkbox sample

## Version 0.5.1

* Improve Texts, Buttons functions to use customs texts fonts
* Ui and Utils don't need to be override (problem with app system). You need to write you want to use directly in Ui and Utils class.

## Version  0.5

* Initial Release
