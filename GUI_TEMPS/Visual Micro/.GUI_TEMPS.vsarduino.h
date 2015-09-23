/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega w/ ATmega2560 (Mega 2560), Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define ARDUINO 165
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define F_CPU 16000000L
#define ARDUINO 165
#define ARDUINO_AVR_MEGA2560
#define ARDUINO_ARCH_AVR
extern "C" void __cxa_pure_virtual() {;}

//
//
void gInit();
void gButtonPressed(int id);
void gItemUpdated(int id);
void EEPROMWriteInt(int p_address, int p_value);
unsigned int EEPROMReadInt(int p_address);
void guino_update();
void gInitEEprom();
void gSetColor(int _red, int _green, int _blue);
void gGetSavedValue(int item_number, int *_variable);
void gBegin(int _eepromKey);
int gAddButton(char * _name);
void gAddColumn();
int gAddLabel(char * _name, int _size);
int gAddSpacer(int _size);
int gAddToggle(char * _name, int * _variable);
int gAddFixedGraph(char * _name,int _min,int _max,int _bufferSize, int * _variable, int _size);
int gAddMovingGraph(char * _name,int _min,int _max, int * _variable, int _size);
int gUpdateLabel(int _item, char * _text);
int gAddRotarySlider(int _min,int _max, char * _name, int * _variable);
int gAddSlider(int _min,int _max, char * _name, int * _variable);
void gUpdateValue(int _item);
void gUpdateValue(int * _variable);
void gSendCommand(byte _cmd, byte _item, int _value);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include <GUI_TEMPS.ino>
#include <Guino_libray.ino>
