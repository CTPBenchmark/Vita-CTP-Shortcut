# Changelog

## Version 0.7
* Add Card class
* Add Scroll class to manage scroll elements
* Improve RadioBoxes & Checkboxes functions with text to support changes (Text type & color)
* Remove UtilsTexts and revert all changes to UiTexts & UtilsIme to simplify logic
* Move applyTextHeightLimit & applyTextWidthLimit of TextFields into UiTexts
* Add possibility to choose a start value in PadTouchController
* Improve PadTouchController class to update value
* Increase size of the float button (without text)
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
