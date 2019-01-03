#ifndef UTILS_H_
# define UTILS_H_

# include <stdint.h>
# include <math.h>
# include <string>
# include <string.h>
# include <stdlib.h>
# include <psp2/ctrl.h>
# include <psp2/display.h>
# include <psp2/kernel/processmgr.h>
# include <psp2/apputil.h>
# include <psp2/io/stat.h>
# include <psp2/system_param.h>
# include <psp2/touch.h>
# include <psp2/sysmodule.h>
# include <psp2/appmgr.h>
# include <psp2/io/fcntl.h>
# include <psp2/ime_dialog.h>
# include <ctime>
# include <vector>
# include <map>
# include <string>

# include <jansson.h>
# include <vita2d.h>


//Screen
# define lerp(value, from_max, to_max) ((((value*10) * (to_max*10))/(from_max*10))/10)

# define SCREEN_H	544
# define SCREEN_L	960


//Colors
# define COLOR_CTP_LOGO RGBA8(208, 210, 210, 255)
# define COLOR_CTP_BG RGBA8(238, 238, 238, 255)

# define COLOR_CTP_LOGO_HALLOWEEN RGBA8(171, 88, 57, 255)
# define COLOR_CTP_BG_HALLOWEEN RGBA8(223, 107, 63, 255)

# define COLOR_CTP_LOGO_CHRISTMAS RGBA8(212, 36, 38, 255)
# define COLOR_CTP_BG_CHRISTMAS RGBA8(255, 255, 255, 255)

# define COLOR_CTP_LOGO_ANNIVERSARY RGBA8(101, 48, 177, 255)
# define COLOR_CTP_BG_ANNIVERSARY RGBA8(126, 60, 222, 255)

# define COLOR_BUTTON_FIRST RGBA8(101, 48, 177, 100)
# define COLOR_BUTTON_SECOND RGBA8(126, 60, 222, 150)
# define COLOR_BUTTON_THIRD RGBA8(49, 15, 141, 175)

# define COLOR_WHITE RGBA8(255, 255, 255, 255)
# define COLOR_RED RGBA8(255, 0, 0, 255)
# define COLOR_GREEN RGBA8(0, 255, 0, 255)
# define COLOR_BLUE RGBA8(0, 191, 255, 255)

# define COLOR_NIL RGBA8(0, 0, 0, 0)

//Url
# define URL_NEWS "http://customprotocol.com"
# define URL_FORUM "http://customprotocol.com/forum/"

//Directory data
# define DIRECTORY_DATA "ux0:/data/CTP/"


# define VERSION_NUMBER 2.0

#endif /* !UTILS_H_ */
