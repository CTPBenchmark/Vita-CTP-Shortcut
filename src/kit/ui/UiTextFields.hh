#ifndef VITAMATERIALKIT_UITEXTFIELDS_HH
#define VITAMATERIALKIT_UITEXTFIELDS_HH

#include "../core/UiEvent.hh"
#include "UiTheme.hpp"
#include "UiIcons.hpp"
#include "UiTexts.hpp"
#include <string>

//https://material.io/design/components/text-fields.html

//positions / dimensions
#define TEXTFIELD_DEFAULT_WIDTH 400
#define TEXTFIELD_DEFAULT_HEIGHT 76
#define TEXTFIELD_DEFAULT_TEXTAREA_HEIGHT TEXTFIELD_DEFAULT_HEIGHT * 3
#define TEXTFIELD_PADDING 20

//size
#define TEXTFIELD_ICONS_SIZE 35
#define TEXTFIELD_FOCUSBAR_SIZE 4
#define TEXTFIELD_NOFOCUSBAR_SIZE 2

//colors
#define TEXTFIELD_BACKGROUND_NOFOCUS_COLOR (unsigned int) RGBA8(242, 242, 242, 120)
#define TEXTFIELD_BACKGROUND_FOCUS_COLOR (unsigned int) RGBA8(212, 212, 212, 120)
#define TEXTFIELD_NOFOCUSBAR_COLOR (unsigned int) RGBA8(122, 122, 122, 255)
#define TEXTFIELD_ERROR_COLOR (unsigned int) RGBA8(159, 0, 25, 255)
#define TEXTFIELD_HELPER_COLOR (unsigned int) RGBA8(91, 91, 91, 255)

typedef enum TextFieldSuffixPosition {
    TEXTFIELD_SP_INDICATOR,
    TEXTFIELD_SP_STICK
} TextFieldSuffixPosition;

typedef struct ZoneEventTextField : public ZoneEvent {
    ZoneEvent leadingIcon;
    ZoneEvent trailingIcon;
    std::string text;
} ZoneEventTextField;

typedef enum TextFieldMode {
    TEXTFIELD_MODE_SINGLE,
    TEXTFIELD_MODE_TEXTAREA
} TextFieldMode;

class UiTextFields : public UiEvent {
private:
    UiTheme *theme;
    UiTexts *texts;
    UiIcons *icons;
    ZoneEventTextField zoneEventTextField;
    TextStyleData bottomTextStyleData, mainTextStyleData;
    TextData textDataText;
    int prefixIconPos, suffixIconPos, prefixTextPos, suffixTextPos;
    std::string charCounterText, showedText;
    unsigned int posBreak;

    void init();
    int keySearch(const std::string& s, const std::string& key);
    std::string applyTextWidthLimit(std::string text, int width);
    std::string applyTextHeightLimit(std::string text, int height);
public:
    UiTextFields(UiTheme *theme);
    UiTextFields(UiTheme *theme, UiTexts *texts);
    UiTextFields(UiTheme *theme, UiTexts *texts, UiIcons *icons);

    ZoneEventTextField filledDraw(
            int x,
            int y,
            bool selector,
            std::string label,
            std::string text = "",
            TextFieldMode textFieldMode = TEXTFIELD_MODE_SINGLE,
            int width = TEXTFIELD_DEFAULT_WIDTH,
            int height = 0,
            TypeTheme typeTheme = THEME_PRIMARY,
            std::string helperText = "",
            std::string errorText = "",
            unsigned int charCounter = 0,
            const char *leadingIcon = "",
            const char *trailingIcon = "",
            std::string prefixText = "",
            std::string suffixText = "",
            TextFieldSuffixPosition suffixPosition = TEXTFIELD_SP_INDICATOR
    );

    //simple
    ZoneEventTextField filledDraw(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, std::string text, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDraw(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label, std::string text, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDraw(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector, std::string label, std::string text, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);

    //with leading icon
    ZoneEventTextField filledDrawLeadingIcon(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, const char *leadingIcon, std::string text = "", std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawLeadingIcon(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label, const char *leadingIcon, std::string text = "", std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawLeadingIcon(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector, std::string label, const char *leadingIcon, std::string text = "", std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);

    //with trailing icon
    ZoneEventTextField filledDrawTrailingIcon(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, std::string text, const char *trailingIcon, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawTrailingIcon(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label, std::string text, const char *trailingIcon, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawTrailingIcon(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector, std::string label, std::string text, const char *trailingIcon, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);

    //with both icons
    ZoneEventTextField filledDrawBothIcons(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, const char *leadingIcon, std::string text, const char *trailingIcon, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawBothIcons(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label, const char *leadingIcon, std::string text, const char *trailingIcon, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawBothIcons(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector, std::string label, const char *leadingIcon, std::string text, const char *trailingIcon, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);

    //with prefix text
    ZoneEventTextField filledDrawPrefixText(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, std::string prefixText, std::string text, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawPrefixText(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label, std::string prefixText, std::string text, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawPrefixText(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector, std::string label, std::string prefixText, std::string text, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);

    //with suffix text
    ZoneEventTextField filledDrawSuffixText(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, std::string text, std::string suffixText, TextFieldSuffixPosition suffixPosition = TEXTFIELD_SP_INDICATOR, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawSuffixText(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label, std::string text, std::string suffixText, TextFieldSuffixPosition suffixPosition = TEXTFIELD_SP_INDICATOR, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawSuffixText(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector, std::string label, std::string text, std::string suffixText, TextFieldSuffixPosition suffixPosition = TEXTFIELD_SP_INDICATOR, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);

    //with leading icon and suffix text
    ZoneEventTextField filledDrawLeadingIconAndSuffixText(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, const char *leadingIcon, std::string text, std::string suffixText, TextFieldSuffixPosition suffixPosition = TEXTFIELD_SP_INDICATOR, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawLeadingIconAndSuffixText(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label, const char *leadingIcon, std::string text, std::string suffixText, TextFieldSuffixPosition suffixPosition = TEXTFIELD_SP_INDICATOR, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawLeadingIconAndSuffixText(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector, std::string label, const char *leadingIcon, std::string text, std::string suffixText, TextFieldSuffixPosition suffixPosition = TEXTFIELD_SP_INDICATOR, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);

    //with prefix text and trailing icon
    ZoneEventTextField filledDrawPrefixTextAndTrailingIcon(int x, int y, TextFieldMode textFieldMode, bool selector, std::string label, std::string prefixText, std::string text, const char *trailingIcon, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawPrefixTextAndTrailingIcon(int x, int y, TextFieldMode textFieldMode, int width, bool selector, std::string label, std::string prefixText, std::string text, const char *trailingIcon, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);
    ZoneEventTextField filledDrawPrefixTextAndTrailingIcon(int x, int y, TextFieldMode textFieldMode, int width, int height, bool selector, std::string label, std::string prefixText, std::string text, const char *trailingIcon, std::string helper = "", std::string error = "", unsigned int charCounter = 0, TypeTheme typeTheme = THEME_PRIMARY);




};


#endif //VITAMATERIALKIT_UITEXTFIELDS_HH
