#include "UiTextFields.hh"
#include <psp2/kernel/clib.h>

UiTextFields::UiTextFields(UiTheme *theme) : theme(theme) {
    this->texts = new UiTexts();
    this->icons = new UiIcons();
    this->init();
}

UiTextFields::UiTextFields(UiTheme *theme, UiTexts *texts) : theme(theme), texts(texts) {
    this->icons = new UiIcons();
    this->init();
}

UiTextFields::UiTextFields(UiTheme *theme, UiTexts *texts, UiIcons *icons) : theme(theme), texts(texts), icons(icons) {
    this->init();
}

void UiTextFields::init() {
    bottomTextStyleData.size = 18;
    bottomTextStyleData.offset = 0;
    bottomTextStyleData.uppercase = false;
    bottomTextStyleData.type = "Regular";

    mainTextStyleData.size = 26;
    mainTextStyleData.offset = 0;
    mainTextStyleData.uppercase = false;
    mainTextStyleData.type = "Regular";
}

//#region filledDraw


ZoneEventTextField UiTextFields::filledDraw(
        int x,
        int y,
        bool selector,
        std::string label,
        std::string text,
        TextFieldMode textFieldMode,
        int width,
        int height,
        TypeTheme typeTheme,
        std::string helperText,
        std::string errorText,
        unsigned int charCounter,
        const char *leadingIcon,
        const char *trailingIcon,
        std::string prefixText,
        std::string suffixText,
        TextFieldSuffixPosition suffixPosition
 ) {

    if (height == 0) {
        height = textFieldMode == TEXTFIELD_MODE_TEXTAREA ? TEXTFIELD_DEFAULT_TEXTAREA_HEIGHT : TEXTFIELD_DEFAULT_HEIGHT;
    }
    prefixIconPos = TEXTFIELD_PADDING;
    suffixIconPos = 0;
    prefixTextPos = 2;
    suffixTextPos = 2;

    //draw background
    vita2d_draw_rectangle(x, y, width, height, selector ? TEXTFIELD_BACKGROUND_FOCUS_COLOR : TEXTFIELD_BACKGROUND_NOFOCUS_COLOR);

    //draw bar status
    if (!errorText.empty()) {
        vita2d_draw_rectangle(x, y + (height - TEXTFIELD_FOCUSBAR_SIZE), width, TEXTFIELD_FOCUSBAR_SIZE, TEXTFIELD_ERROR_COLOR);
    }
    else if (selector) {
        vita2d_draw_rectangle(x, y + (height - TEXTFIELD_FOCUSBAR_SIZE), width, TEXTFIELD_FOCUSBAR_SIZE, typeTheme == THEME_PRIMARY ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal);
    }
    else {
        vita2d_draw_rectangle(x, y + (height - TEXTFIELD_NOFOCUSBAR_SIZE), width, TEXTFIELD_NOFOCUSBAR_SIZE, TEXTFIELD_NOFOCUSBAR_COLOR);
    }

    //prefixIcon
    if (strlen(leadingIcon) > 0) {
        icons->draw(leadingIcon, x + TEXTFIELD_PADDING, y + 20, TEXTFIELD_HELPER_COLOR, TEXTFIELD_ICONS_SIZE);
        prefixIconPos += TEXTFIELD_ICONS_SIZE + TEXTFIELD_PADDING;
        zoneEventTextField.leadingIcon.x = x + TEXTFIELD_PADDING;
        zoneEventTextField.leadingIcon.y = y + 20;
        zoneEventTextField.leadingIcon.width = TEXTFIELD_ICONS_SIZE;
        zoneEventTextField.leadingIcon.height = TEXTFIELD_ICONS_SIZE;
    }
    else {
        zoneEventTextField.leadingIcon.x = 0;
        zoneEventTextField.leadingIcon.y = 0;
        zoneEventTextField.leadingIcon.width = 0;
        zoneEventTextField.leadingIcon.height = 0;
    }
    zoneEventTextField.leadingIcon.selector = false;

    //suffixIcon
    if (strlen(trailingIcon) > 0) {
        icons->draw(trailingIcon, x + width - TEXTFIELD_PADDING - TEXTFIELD_ICONS_SIZE, y + 20, TEXTFIELD_HELPER_COLOR, TEXTFIELD_ICONS_SIZE);
        zoneEventTextField.leadingIcon.x = x + width - TEXTFIELD_PADDING - TEXTFIELD_ICONS_SIZE;
        zoneEventTextField.leadingIcon.y = y + 20;
        zoneEventTextField.leadingIcon.width = width;
        zoneEventTextField.leadingIcon.height = height;

        suffixIconPos = TEXTFIELD_ICONS_SIZE + TEXTFIELD_PADDING;
    }
    else {
        zoneEventTextField.leadingIcon.x = 0;
        zoneEventTextField.leadingIcon.y = 0;
        zoneEventTextField.leadingIcon.width = 0;
        zoneEventTextField.leadingIcon.height = 0;
    }
    zoneEventTextField.trailingIcon.selector = false;

    //prefix
    if (!prefixText.empty()) {
        textDataText = texts->getTextData(prefixText, mainTextStyleData);
        texts->draw(x + prefixIconPos, y + 30, mainTextStyleData, TEXTFIELD_HELPER_COLOR, prefixText);
        prefixTextPos += textDataText.width;
    }

    //suffix
    if (!suffixText.empty()) {
        textDataText = texts->getTextData(suffixText, mainTextStyleData);
        suffixTextPos = width - textDataText.width - TEXTFIELD_PADDING;
        texts->draw(x + suffixTextPos, y + 30, mainTextStyleData, TEXTFIELD_HELPER_COLOR, suffixText);
    }

    //adjust text
    if (!text.empty()) {
        textDataText = texts->getTextData(text, mainTextStyleData);

        //adjust showed text
        if (textFieldMode == TEXTFIELD_MODE_SINGLE && textDataText.width > (width - TEXTFIELD_PADDING - prefixIconPos - suffixIconPos)) {
            showedText = text.substr(textDataText.width / (mainTextStyleData.size - 10), text.size());
        }
        else if (textFieldMode == TEXTFIELD_MODE_TEXTAREA && textDataText.width > (width - TEXTFIELD_PADDING - prefixIconPos - suffixIconPos)) {
            showedText = texts->applyTextWidthLimit(text, width - TEXTFIELD_PADDING - prefixIconPos - suffixIconPos, mainTextStyleData);
            showedText = texts->applyTextHeightLimit(showedText, height - 32, mainTextStyleData);
        }
        else {
            showedText = text;
        }
    }

    //label
    if (!text.empty() || !prefixText.empty() || !suffixText.empty()) {
        if (selector) {
            texts->draw(x + prefixIconPos, y + 4, bottomTextStyleData, typeTheme == THEME_PRIMARY ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal, std::move(label));
        }
        else {
            texts->draw(x + prefixIconPos, y + 4, bottomTextStyleData, std::move(label));
        }
    }
    else {
        //label
        if (selector) {
            texts->draw(x + prefixIconPos, y + 4, bottomTextStyleData, typeTheme == THEME_PRIMARY ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal, std::move(label));
        }
        else {
            texts->draw(x + prefixIconPos, y + 26, Body1, errorText.length() > 0 ? TEXTFIELD_ERROR_COLOR : (typeTheme == THEME_PRIMARY ? theme->getPrimaryRGBA().normal : theme->getSecondaryRGBA().normal), std::move(label));
        }
    }


    //text
    if (!text.empty()) {

        if (suffixText.length() > 0 && suffixPosition == TEXTFIELD_SP_STICK) {//suffix case
            texts->draw(x + suffixTextPos - textDataText.width - 4, y + 30, mainTextStyleData, showedText);
        }
        else {
            texts->draw(x + prefixIconPos + prefixTextPos, y + 30, mainTextStyleData, showedText);
        }
    }


    //draw helper
    if (!errorText.empty()) {
        texts->draw(x + prefixIconPos, y + height + 2, bottomTextStyleData, TEXTFIELD_ERROR_COLOR, errorText);
    }
    else if (helperText.length() > 0) {
        texts->draw(x + prefixIconPos, y + height + 2, bottomTextStyleData, TEXTFIELD_HELPER_COLOR, helperText);
    }

    //draw char counter
    if (charCounter > 0) {
        charCounterText = std::to_string(text.length()) + "/" + std::to_string(charCounter);
        textDataText = texts->getTextData(charCounterText, bottomTextStyleData);
        texts->draw(x + width - TEXTFIELD_PADDING - textDataText.width, y + height, bottomTextStyleData, TEXTFIELD_HELPER_COLOR, charCounterText);
    }


    //vita2d_draw_rectangle(x + prefixIconPos, y, width - TEXTFIELD_PADDING - prefixIconPos - suffixIconPos, height, RGBA8(255, 0, 0, 150));


    zoneEventTextField.x = x + prefixIconPos;
    zoneEventTextField.y = y;
    zoneEventTextField.width = width - TEXTFIELD_PADDING - prefixIconPos - suffixIconPos;
    zoneEventTextField.height = height;
    zoneEventTextField.selector = selector;

    return zoneEventTextField;
}

//#region simple

ZoneEventTextField UiTextFields::filledDraw(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, std::string text, std::string helper, std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            TEXTFIELD_DEFAULT_WIDTH,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter
            );
}

ZoneEventTextField UiTextFields::filledDraw(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label, std::string text, std::string helper, std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter
    );
}

ZoneEventTextField UiTextFields::filledDraw(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector, std::string label, std::string text, std::string helper, std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            height,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter
    );
}


//#endregion

//#region with leading icon


ZoneEventTextField UiTextFields::filledDrawLeadingIcon(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, const char *leadingIcon, std::string text, std::string helper, std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            TEXTFIELD_DEFAULT_WIDTH,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            leadingIcon
    );
}

ZoneEventTextField UiTextFields::filledDrawLeadingIcon(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label,
                                            const char *leadingIcon, std::string text, std::string helper, std::string error, unsigned int charCounter,
                                            TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            leadingIcon
    );
}

ZoneEventTextField UiTextFields::filledDrawLeadingIcon(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector,
                                            std::string label, const char *leadingIcon, std::string text, std::string helper,
                                            std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            height,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            leadingIcon
    );
}

//#endregion

//#region with trailing icon

ZoneEventTextField UiTextFields::filledDrawTrailingIcon(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, std::string text, const char *trailingIcon, std::string helper, std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            TEXTFIELD_DEFAULT_WIDTH,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            trailingIcon
    );
}

ZoneEventTextField UiTextFields::filledDrawTrailingIcon(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label,
                                            std::string text, const char *trailingIcon, std::string helper, std::string error, unsigned int charCounter,
                                            TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            trailingIcon
    );
}

ZoneEventTextField UiTextFields::filledDrawTrailingIcon(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector,
                                            std::string label, std::string text, const char *trailingIcon, std::string helper,
                                            std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            height,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            trailingIcon
    );
}

//#endregion

//#region with both icons

ZoneEventTextField UiTextFields::filledDrawBothIcons(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label,
                                            const char *leadingIcon, std::string text, const char *trailingIcon,
                                            std::string helper, std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            TEXTFIELD_DEFAULT_WIDTH,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            leadingIcon,
            trailingIcon
    );
}

ZoneEventTextField UiTextFields::filledDrawBothIcons(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label,
                                            const char *leadingIcon, std::string text, const char *trailingIcon, std::string helper,
                                            std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            leadingIcon,
            trailingIcon
    );
}

ZoneEventTextField UiTextFields::filledDrawBothIcons(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector,
                                            std::string label, const char *leadingIcon, std::string text, const char *trailingIcon,
                                            std::string helper, std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            height,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            leadingIcon,
            trailingIcon
    );
}

//#endregion

//#region with prefix text

ZoneEventTextField UiTextFields::filledDrawPrefixText(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label,
                                                      std::string prefixText, std::string text, std::string helper, std::string error,
                                                      unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            TEXTFIELD_DEFAULT_WIDTH,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            "",
            std::move(prefixText)
    );
}

ZoneEventTextField UiTextFields::filledDrawPrefixText(int x, int y, TextFieldMode textFieldMode, int width, bool selector,
                                                      std::string label, std::string prefixText, std::string text, std::string helper,
                                                      std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            "",
            std::move(prefixText)
    );
}

ZoneEventTextField UiTextFields::filledDrawPrefixText(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector,
                                                      std::string label, std::string prefixText, std::string text, std::string helper,
                                                      std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            height,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            "",
            std::move(prefixText)
    );
}
//#endregion

//#region with suffix text

ZoneEventTextField UiTextFields::filledDrawSuffixText(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label,
                                                      std::string text, std::string suffixText, TextFieldSuffixPosition suffixPosition,
                                                      std::string helper, std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            TEXTFIELD_DEFAULT_WIDTH,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            "",
            "",
            std::move(suffixText),
            suffixPosition
    );
}

ZoneEventTextField UiTextFields::filledDrawSuffixText(int x, int y, TextFieldMode textFieldMode, int width, bool selector,
                                                      std::string label, std::string text, std::string suffixText,
                                                      TextFieldSuffixPosition suffixPosition, std::string helper, std::string error,
                                                      unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            "",
            "",
            std::move(suffixText),
            suffixPosition
    );
}

ZoneEventTextField UiTextFields::filledDrawSuffixText(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector,
                                                      std::string label, std::string text, std::string suffixText,
                                                      TextFieldSuffixPosition suffixPosition, std::string helper, std::string error,
                                                      unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            height,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            "",
            "",
            std::move(suffixText),
            suffixPosition
    );
}
//#endregion

//#region with leading icon and suffix text

ZoneEventTextField UiTextFields::filledDrawLeadingIconAndSuffixText(int x, int y, TextFieldMode textFieldMode, bool selector,
                                                                    std::string label, const char *leadingIcon, std::string text,
                                                                    std::string suffixText, TextFieldSuffixPosition suffixPosition,
                                                                    std::string helper, std::string error, unsigned int charCounter,
                                                                    TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            TEXTFIELD_DEFAULT_WIDTH,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            leadingIcon,
            "",
            "",
            std::move(suffixText),
            suffixPosition
    );
}

ZoneEventTextField UiTextFields::filledDrawLeadingIconAndSuffixText(int x, int y, TextFieldMode textFieldMode, int width, bool selector,
                                                                    std::string label, const char *leadingIcon, std::string text,
                                                                    std::string suffixText, TextFieldSuffixPosition suffixPosition,
                                                                    std::string helper, std::string error, unsigned int charCounter,
                                                                    TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            leadingIcon,
            "",
            "",
            std::move(suffixText),
            suffixPosition
    );
}

ZoneEventTextField UiTextFields::filledDrawLeadingIconAndSuffixText(int x, int y, TextFieldMode textFieldMode, int width, int height,
                                                                    bool selector, std::string label, const char *leadingIcon,
                                                                    std::string text, std::string suffixText,
                                                                    TextFieldSuffixPosition suffixPosition, std::string helper,
                                                                    std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            height,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            leadingIcon,
            "",
            "",
            std::move(suffixText),
            suffixPosition
    );
}
//#endregion

//#region with prefix text and trailing icon

ZoneEventTextField UiTextFields::filledDrawPrefixTextAndTrailingIcon(int x, int y, TextFieldMode textFieldMode, bool selector,
                                                                    std::string label, std::string prefixText, std::string text,
                                                                    const char *trailingIcon, std::string helper, std::string error,
                                                                    unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            TEXTFIELD_DEFAULT_WIDTH,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            trailingIcon,
            std::move(prefixText)
    );
}

ZoneEventTextField UiTextFields::filledDrawPrefixTextAndTrailingIcon(int x, int y, TextFieldMode textFieldMode, int width, bool selector,
                                                                    std::string label, std::string prefixText, std::string text,
                                                                    const char *trailingIcon, std::string helper, std::string error,
                                                                    unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            0,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            trailingIcon,
            std::move(prefixText)
    );
}

ZoneEventTextField UiTextFields::filledDrawPrefixTextAndTrailingIcon(int x, int y, TextFieldMode textFieldMode, int width, int height,
                                                                    bool selector, std::string label, std::string prefixText,
                                                                    std::string text, const char *trailingIcon, std::string helper,
                                                                    std::string error, unsigned int charCounter, TypeTheme typeTheme) {
    return this->filledDraw(
            x,
            y,
            selector,
            std::move(label),
            std::move(text),
            textFieldMode,
            width,
            height,
            typeTheme,
            std::move(helper),
            std::move(error),
            charCounter,
            "",
            "",
            std::move(prefixText)
    );
}
//#endregion


