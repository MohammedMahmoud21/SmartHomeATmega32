#ifndef CONVERTER_INTERFACE_H_
#define CONVERTER_INTERFACE_H_
#include "LCD_interface.h"
#include "KeyPad_interface.h"

/**
 * @note START must be used in case of default value that wasn't returned from any function from converter app.
 *
 */
typedef enum
{
	DECIMAL = 'D',
	HEX = 'H',
	BIN = 'B',
	START
} Number_Format_type;

/**
 * @brief must be called before super loop (while(1)) to initialize DIO and LCD modules.
 *
 */
extern void Converter_Init(void);
/**
 * @brief this function perform deferent lcd output based on option argument,
 * 			it works to handle user input (convert from) and (convert to).
 *
 * @param option this var must be set to START, if this is the first time calling it or the program is
 * 			restart its functionality again.
 * @return @ref Number_Format_type
 */
extern Number_Format_type Converter_UserOption(Number_Format_type option);
extern s32 Converter_Take_User_DecimalNumber(bool_type *const exit);
extern s32 Converter_Take_User_BinaryNumber(bool_type *const exit);
extern s32 Converter_Take_User_HEXNumber(bool_type *const exit);
#endif /* CONVERTER_INTERFACE_H_ */