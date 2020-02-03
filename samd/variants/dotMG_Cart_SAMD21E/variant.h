/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_DOTMG_CART_SAMD21E_
#define _VARIANT_DOTMG_CART_SAMD21E_

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK			  (48000000ul)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#ifdef __cplusplus
extern "C" unsigned int PINCOUNT_fn();
#endif
#define PINS_COUNT           (PINCOUNT_fn())
#define NUM_DIGITAL_PINS     (23u)
#define NUM_ANALOG_INPUTS    (9u)
#define NUM_ANALOG_OUTPUTS   (1u)
#define analogInputToDigitalPin(p)  (((p) < NUM_ANALOG_INPUTS) ? (p) : -1)

#define digitalPinToPort(P)        (&(PORT->Group[g_APinDescription[P].ulPort]))
#define digitalPinToBitMask(P)     (1 << g_APinDescription[P].ulPin)
#define portOutputRegister(port)   (&(port->OUT.reg))
#define portInputRegister(port)    (&(port->IN.reg))
#define portModeRegister(port)     (&(port->DIR.reg))
#define digitalPinHasPWM(P)        (g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER)

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

/*
 * Analog pins
 */
#define PIN_A0               (0ul)
#define PIN_A1               (1ul)
#define PIN_A2               (2ul)
#define PIN_A3               (3ul)
#define PIN_A4               (4ul)
#define PIN_A5               (5ul)
#define PIN_A6               (6ul)
#define PIN_A7               (7ul)
#define PIN_A8               (8ul)
#define PIN_DAC0             PIN_A0

static const uint8_t A0  = PIN_A0;
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;
static const uint8_t A4  = PIN_A4;
static const uint8_t A5  = PIN_A5;
static const uint8_t A6  = PIN_A6;
static const uint8_t A7  = PIN_A7;
static const uint8_t A8  = PIN_A8;
static const uint8_t DAC0 = PIN_DAC0;
#define ADC_RESOLUTION		12

/*
 * Extension pins
 */
#define PIN_X0               (1ul)
#define PIN_X1               (2ul)
#define PIN_X2               (3ul)
#define PIN_X3               (4ul)
#define PIN_X4               (11ul)
#define PIN_X5               (12ul)
#define PIN_X6               (13ul)

static const uint8_t X0  = PIN_X0;
static const uint8_t X1  = PIN_X1;
static const uint8_t X2  = PIN_X2;
static const uint8_t X3  = PIN_X3;
static const uint8_t X4  = PIN_X4;
static const uint8_t X5  = PIN_X5;
static const uint8_t X6  = PIN_X6;

/*
 * ATN represents the slave/chip select pin for the first SPI module,
 * which is typically the display in this board's case.
 *
 * https://forum.arduino.cc/index.php?topic=330088.msg2280038#msg2280038
 */
#define PIN_ATN              (16ul)
static const uint8_t ATN = PIN_ATN;

/*
 * Serial interface
 */
#define PIN_SERIAL_RX       (14ul)
#define PIN_SERIAL_TX       (15ul)
#define PAD_SERIAL_TX       (UART_TX_PAD_2)
#define PAD_SERIAL_RX       (SERCOM_RX_PAD_3)

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MOSI         (11u)
#define PIN_SPI_MISO         (12u)
#define PIN_SPI_SCK          (13u)
#define PERIPH_SPI           sercom1

#define PAD_SPI_TX           SPI_PAD_0_SCK_1
#define PAD_SPI_RX           SERCOM_RX_PAD_2

static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (3u)
#define PIN_WIRE_SCL         (2u)
#define PERIPH_WIRE          sercom0
#define WIRE_IT_HANDLER      SERCOM0_Handler

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

/*
 * USB
 */
#define PIN_USB_DM          (19ul)
#define PIN_USB_DP          (20ul)

/*
 * I2S Interfaces
 */
#define I2S_INTERFACES_COUNT 1

#define I2S_DEVICE          0
#define I2S_CLOCK_GENERATOR 3
#define PIN_I2S_SD          (1u)
#define PIN_I2S_SCK         (2u)
#define PIN_I2S_FS          (3u)

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
*/
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;

extern Uart Serial;

#endif

#ifdef __cplusplus
extern "C" {
#endif
unsigned int PINCOUNT_fn();
#ifdef __cplusplus
}
#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.

#define Serial SerialUSB  // Alias Serial to USB virtual serial port for ease of use

#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         Serial
// Serial has no physical pins broken out, so it's not listed as HARDWARE port
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

#endif /* _VARIANT_DOTMG_CART_SAMD21E_ */

