/*
 *  PinDefinitionsAndMore.h
 *
 *  Contains IRMP_INPUT_PIN definitions for IRMP examples for various platforms
 *  as well as includes and definitions for LED_BUILTIN
 *
 *  Copyright (C) 2019-2020  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of IRMP https://github.com/ukw100/IRMP.
 *
 *  IRMP is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#include <Arduino.h>

/*
 * Set library modifiers first to set input pin etc.
 */
#if defined(ESP8266)
#define BLINK_13_LED_IS_ACTIVE_LOW // The LED on my board is active LOW
#define IRMP_INPUT_PIN   14 // D5
#define IRSND_OUTPUT_PIN 12 // D6 - D4/2 is internal LED
#define tone(a,b) void() // tone() inhibits receive timer
#define noTone(a) void()
//#define IRMP_TIMING_TEST_PIN 13 // D7

#elif defined(ESP32)
#define IRMP_INPUT_PIN   15  // D15
#define IRSND_OUTPUT_PIN  4  // D4
#define tone(a,b) void() // no tone() available on ESP32
#define noTone(a) void()

#elif defined(STM32F1xx) || defined(__STM32F1__)
// BluePill in 2 flavors
// STM32F1xx is for "Generic STM32F1 series" from STM32 Boards from STM32 cores of Arduino Board manager
// __STM32F1__is for "Generic STM32F103C series" from STM32F1 Boards (STM32duino.com) of manually installed hardware folder
// Timer 3 of IRMP blocks PA6, PA7, PB0, PB1 for use by Servo or tone()
#define BLINK_13_LED_IS_ACTIVE_LOW // The LED on the BluePill is active LOW
#define IRMP_INPUT_PIN   PA6
#define IRSND_OUTPUT_PIN PA7
#define TONE_PIN         PA3
//#define IRMP_TIMING_TEST_PIN PA5

#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#include "ATtinySerialOut.h"
#  if  defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#    if defined(ARDUINO_AVR_DIGISPARK)
#define LED_BUILTIN PB1
#    endif
#define IRMP_INPUT_PIN 0
#define IRSND_OUTPUT_PIN 4 // Pin 2 is serial output with ATtinySerialOut. Pin 1 is internal LED and Pin3 is USB+ with pullup on Digispark board.
#define TONE_PIN         3
//#define IRMP_TIMING_TEST_PIN 3

#  else
// ATtiny87 + ATtiny167 here. For ATtiny167 Pins PB6 and PA3 are usable as interrupt source.
#    if defined(ARDUINO_AVR_DIGISPARKPRO)
#define LED_BUILTIN      1 // PB1 - on Digispark board labeled as pin 1 / for ATtinyCore lib use D9
#define IRMP_INPUT_PIN   9 // PA3 - on Digispark board labeled as pin 9
//#define IRMP_INPUT_PIN  14 // PB6 / INT0 is connected to USB+ on DigisparkPro boards
#define IRSND_OUTPUT_PIN 8 // PA2 - on Digispark board labeled as pin 8
#define TONE_PIN          5 // PA7
//#define IRMP_TIMING_TEST_PIN 10 // PA4

#    else
#define IRMP_INPUT_PIN   3
#define IRSND_OUTPUT_PIN 2
#define TONE_PIN         7
#    endif
#  endif

#elif defined(ARDUINO_ARCH_APOLLO3)
#define IRMP_INPUT_PIN   11
#define IRSND_OUTPUT_PIN 12

#else
#define IRMP_INPUT_PIN   3 // only 2 (INT0) and 3 (INT1) are allowed here, default is 3, even if not specified.
#define IRSND_OUTPUT_PIN 4
#define TONE_PIN         5
//#define IRMP_TIMING_TEST_PIN 6
// You can alternatively specify the input pin with port and bit number if you do not have the Arduino pin number at hand
//#define IRMP_PORT_LETTER D
//#define IRMP_BIT_NUMBER 3
#endif // defined(ESP8266)

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

#if ! defined(__AVR__) // for AVR we manage hardware directly in void initPCIInterrupt()
#define IRMP_USE_ARDUINO_ATTACH_INTERRUPT
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/*
 * Imports and definitions for LCD used in AllProtocols.h
 */
#if defined (USE_SERIAL_LCD)
#include <LiquidCrystal_I2C.h>
#endif
#if defined (USE_PARALELL_LCD)
#include <LiquidCrystal.h>
#endif

#if defined (USE_1602_LCD)
// definitions for a 1602 LCD
#define LCD_COLUMNS 16
#define LCD_ROWS 2
#endif
#if defined (USE_2004_LCD)
// definitions for a 2004 LCD
#define LCD_COLUMNS 20
#define LCD_ROWS 4
#endif
