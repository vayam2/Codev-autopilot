/****************************************************************************
 *
 *   Copyright (c) 2019 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file board_config.h
 *
 * codev AQUILA-v2 internal definitions
 */

#pragma once

/****************************************************************************************************
 * Included Files
 ****************************************************************************************************/

#include <px4_platform_common/px4_config.h>
#include <nuttx/compiler.h>
#include <stdint.h>

#include <stm32_gpio.h>

/****************************************************************************************************
 * Definitions
 ****************************************************************************************************/

/* PX4IO connection configuration */

#define BOARD_USES_PX4IO_VERSION       2
#define PX4IO_SERIAL_DEVICE            "/dev/ttyS5"
#define PX4IO_SERIAL_TX_GPIO           GPIO_USART6_TX
#define PX4IO_SERIAL_RX_GPIO           GPIO_USART6_RX
#define PX4IO_SERIAL_BASE              STM32_USART6_BASE
#define PX4IO_SERIAL_VECTOR            STM32_IRQ_USART6
#define PX4IO_SERIAL_TX_DMAMAP         DMAMAP_USART6_TX
#define PX4IO_SERIAL_RX_DMAMAP         DMAMAP_USART6_RX
#define PX4IO_SERIAL_RCC_REG           STM32_RCC_APB2ENR
#define PX4IO_SERIAL_RCC_EN            RCC_APB2ENR_USART6EN
#define PX4IO_SERIAL_CLOCK             STM32_PCLK2_FREQUENCY
#define PX4IO_SERIAL_BITRATE           1500000               /* 1.5Mbps -> max rate for IO */

/* Configuration ************************************************************************************/

#  define BOARD_HAS_LTC44XX_VALIDS      2 // No LTC or N Bricks
#  define BOARD_HAS_USB_VALID           1 // LTC Has No USB valid
#  define BOARD_HAS_NBAT_V              2 // Only one Vbat to ADC
#  define BOARD_HAS_NBAT_I              2 // No Ibat ADC

/* CODEV AQUILA GPIOs ************************************************************************/

/* LEDs are driven with push open drain to support Anode to 5V or 3.3V */

#define GPIO_nLED_RED        /* PB1 */  (GPIO_OUTPUT|GPIO_OPENDRAIN|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTB|GPIO_PIN1)
#define GPIO_nLED_GREEN      /* PB0 */  (GPIO_OUTPUT|GPIO_OPENDRAIN|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTB|GPIO_PIN0)
#define GPIO_nLED_BLUE       /* PE9 */  (GPIO_OUTPUT|GPIO_OPENDRAIN|GPIO_SPEED_50MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN9)

#define BOARD_HAS_CONTROL_STATUS_LEDS      1
#define BOARD_OVERLOAD_LED     LED_RED
#define BOARD_ARMED_STATE_LED  LED_BLUE

/*
 * ADC channels
 *
 * These are the channel numbers of the ADCs of the microcontroller that
 * can be used by the Px4 Firmware in the adc driver
 */

/* ADC defines to be used in sensors.cpp to read from a particular channel */

#define ADC1_CH(n)                  (n)

/* Define GPIO pins used as ADC N.B. Channel numbers must match below */

#define PX4_ADC_GPIO  \
	/* PA0 */  GPIO_ADC1_INP16,   \
	/* PA1 */  GPIO_ADC1_INP17,   \
	/* PA2 */  GPIO_ADC12_INP14,  \
	/* PA3 */  GPIO_ADC12_INP15,  \
	/* PA4 */  GPIO_ADC12_INP18,  \
	/* PB0 */  GPIO_ADC12_INP9,   \
	/* PC0 */  GPIO_ADC123_INP10, \
	/* PC1 */  GPIO_ADC123_INP11, \
	/* PC2 */  GPIO_ADC123_INP12, \
	/* PC3 */  GPIO_ADC12_INP13,  \
	/* PC4 */  GPIO_ADC12_INP4

/* Define Channel numbers must match above GPIO pin IN(n)*/

#define ADC_BATTERY_VOLTAGE_CHANNEL        /* PA0 */  ADC1_CH(16)
#define ADC_BATTERY_CURRENT_CHANNEL        0
#define ADC1_12_CHANNEL			   ADC1_CH(14)
#define ADC1_15_CHANNEL			   ADC1_CH(15)
#define ADC1_6V6_IN_CHANNEL                 /* PA4 */  ADC1_CH(18)
#define ADC_RSSI_IN_CHANNEL                 /* PB0 */  ADC1_CH(9)
#define ADC_SCALED_V5_CHANNEL               /* PC0 */  ADC1_CH(10)
#define ADC_SCALED_VDD_3V3_SENSORS_CHANNEL  /* PC1 */  ADC1_CH(11)
#define ADC_HW_VER_SENSE_CHANNEL            /* PC2 */  ADC1_CH(12)
#define ADC_HW_REV_SENSE_CHANNEL            /* PC3 */  ADC1_CH(13)
#define ADC1_3V3_IN_CHANNEL                 /* PC4 */  ADC1_CH(4)

#define ADC_CHANNELS \
	((1 << ADC_BATTERY_VOLTAGE_CHANNEL)       | \
	 (1 << ADC_BATTERY_CURRENT_CHANNEL)       | \
	 (1 << ADC1_6V6_IN_CHANNEL)                | \
	 (1 << ADC_RSSI_IN_CHANNEL)                | \
	 (1 << ADC_SCALED_V5_CHANNEL)              | \
	 (1 << ADC_SCALED_VDD_3V3_SENSORS_CHANNEL) | \
	 (1 << ADC_HW_VER_SENSE_CHANNEL)           | \
	 (1 << ADC_HW_REV_SENSE_CHANNEL)           | \
	 (1 << ADC1_3V3_IN_CHANNEL))

/* Define Battery 1 Voltage Divider and A per V
 */

#define BOARD_BATTERY1_V_DIV         (9.0f)     /* measured with the provided PM board */
#define BOARD_BATTERY1_A_PER_V       (36.367515152f)

/* HW has to large of R termination on ADC todo:change when HW value is chosen */

#define BOARD_ADC_OPEN_CIRCUIT_V     (5.6f)

/* HW Version and Revision drive signals Default to 1 to detect */

#define BOARD_HAS_HW_VERSIONING

#define GPIO_HW_REV_DRIVE    /* PH14  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTH|GPIO_PIN14)
#define GPIO_HW_REV_SENSE    /* PC3   */ GPIO_ADC12_INP13
#define GPIO_HW_VER_DRIVE    /* PG0   */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTG|GPIO_PIN0)
#define GPIO_HW_VER_SENSE    /* PC2   */ GPIO_ADC123_INP12
#define HW_INFO_INIT         {'V','D','2','x','x',0}
#define HW_INFO_INIT_VER     3
#define HW_INFO_INIT_REV     4

/* CAN Silence
 *
 * Silent mode control \ ESC Mux select
 */

#define GPIO_CAN1_SILENT_S0  /* PC1  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTC|GPIO_PIN1)
#define GPIO_CAN2_SILENT_S1  /* PC2  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTC|GPIO_PIN2)
#define GPIO_CAN3_SILENT_S2  /* PC3  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTC|GPIO_PIN3)

#define BOARD_TAP_ESC_MODE 2 // select closed-loop control mode for the esc

#define BOARD_USE_ESC_CURRENT_REPORT

#define BOARD_MAX_LEDS 4 // Define the number of led this board has
/* HEATER
 * PWM in future
 */
#define GPIO_HEATER_OUTPUT   /* PA4  T14CH1 */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTA|GPIO_PIN4)
#define GPIO_EEPROM_WP	       /* PB2 */   (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTB|GPIO_PIN2)

/* PWM Capture
 *
 * 6  PWM Capture inputs are configured.
 *
 * Pins:
 *
 * FMU_CAP1 : PB11 : TIM2_CH4
 * FMU_CAP2 : PB3  : TIM2_CH2
 * FMU_CAP3 : PA5  : TIM2_CH1
 * FMU_CAP4 : PH9  : TIM12_CH2
 * FMU_CAP5 : PH6  : TIM12_CH1
 * FMU_CAP6 : PD14 : TIM4_CH3
 */

#define GPIO_TIM2_CH4_IN     /* PB11   FMU_CAP3 */ GPIO_TIM2_CH4IN_2
#define GPIO_TIM2_CH2_IN     /* PB3    FMU_CAP2 */ GPIO_TIM2_CH2IN_2
#define GPIO_TIM2_CH1_IN     /* PA5    FMU_CAP1 */ GPIO_TIM2_CH1IN_3
#define GPIO_TIM12_CH2_IN    /* PH9    FMU_CAP4 */ GPIO_TIM12_CH2IN_2
#define GPIO_TIM12_CH1_IN    /* PH6    FMU_CAP5 */ GPIO_TIM12_CH1IN_2
#define GPIO_TIM4_CH3_IN     /* PD14   FMU_CAP6 */ GPIO_TIM4_CH3IN_2

#define DIRECT_PWM_CAPTURE_CHANNELS  6

/* PWM
 */
#define DIRECT_PWM_OUTPUT_CHANNELS  5
#define DIRECT_INPUT_TIMER_CHANNELS  5

#define BOARD_DSHOT_MOTOR_ASSIGNMENT {3, 2, 1, 0, 4};

/* Power supply control and monitoring GPIOs */

#define GPIO_nPOWER_IN_A                /* PG1  */ (GPIO_INPUT|GPIO_PULLUP|GPIO_PORTG|GPIO_PIN1)
#define GPIO_nPOWER_IN_B                /* PG2  */ (GPIO_INPUT|GPIO_PULLUP|GPIO_PORTG|GPIO_PIN2)
#define GPIO_nPOWER_IN_C                /* PG3  */ (GPIO_INPUT|GPIO_PULLUP|GPIO_PORTG|GPIO_PIN3)

#define GPIO_VDD_BRICK_VALID          GPIO_nPOWER_IN_A /* Brick 1 Is Chosen */
#define BOARD_NUMBER_BRICKS             1
#define GPIO_nVDD_USB_VALID             GPIO_nPOWER_IN_C /* USB     Is Chosen */

#define GPIO_nVDD_5V_PERIPH_EN          /* PG4  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTG|GPIO_PIN4)
#define GPIO_nVDD_5V_PERIPH_OC          /* PE15 */ (GPIO_INPUT |GPIO_FLOAT|GPIO_PORTE|GPIO_PIN15)
#define GPIO_nVDD_5V_HIPOWER_EN         /* PF12 */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTF|GPIO_PIN12)
#define GPIO_nVDD_5V_HIPOWER_OC         /* PG13 */ (GPIO_INPUT |GPIO_FLOAT|GPIO_PORTF|GPIO_PIN13)
#define GPIO_VDD_3V3_SPEKTRUM_POWER_EN  /* PE4  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN4)
#define GPIO_VDD_3V3_SD_CARD_EN         /* PG7  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTG|GPIO_PIN7)
#define GPIO_VDD_3V3_SENSORS_EN         /* PE3  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN3)
#define GPIO_VDD_5V_RC_EN               /* PD3  */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTD|GPIO_PIN3)


/* Define True logic Power Control in arch agnostic form */

#define VDD_5V_PERIPH_EN(on_true)          px4_arch_gpiowrite(GPIO_nVDD_5V_PERIPH_EN, !(on_true))
#define VDD_5V_HIPOWER_EN(on_true)         px4_arch_gpiowrite(GPIO_nVDD_5V_HIPOWER_EN, !(on_true))
#define VDD_3V3_SPEKTRUM_POWER_EN(on_true) px4_arch_gpiowrite(GPIO_VDD_3V3_SPEKTRUM_POWER_EN, (on_true))
#define READ_VDD_3V3_SPEKTRUM_POWER_EN()   px4_arch_gpioread(GPIO_VDD_3V3_SPEKTRUM_POWER_EN)
#define VDD_3V3_SD_CARD_EN(on_true)        px4_arch_gpiowrite(GPIO_VDD_3V3_SD_CARD_EN, (on_true))
#define VDD_3V3_SENSORS_EN(on_true)        px4_arch_gpiowrite(GPIO_VDD_3V3_SENSORS_EN, (on_true))
#define VDD_5V_RC_EN(on_true)              px4_arch_gpiowrite(GPIO_VDD_5V_RC_EN, (on_true))

/* Tone alarm output */

#define TONE_ALARM_TIMER        15  /* timer 15 */
#define TONE_ALARM_CHANNEL      1  /* PE5 TIM15_CH1 */

#define GPIO_BUZZER_1           /* PE5 */ (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_CLEAR|GPIO_PORTE|GPIO_PIN5)

#define GPIO_TONE_ALARM_IDLE    GPIO_BUZZER_1
#define GPIO_TONE_ALARM         GPIO_TIM15_CH1OUT_2

/* USB OTG FS
 *
 * PA9  OTG_FS_VBUS VBUS sensing
 */
#define GPIO_OTGFS_VBUS         /* PA9 */ (GPIO_INPUT|GPIO_PULLDOWN|GPIO_SPEED_100MHz|GPIO_PORTA|GPIO_PIN9)

/* High-resolution timer */
#define HRT_TIMER               8  /* use timer8 for the HRT */
#define HRT_TIMER_CHANNEL       3  /* use capture/compare channel 3 */

/* RC Serial port */

/* Input Capture Channels. */

#define INPUT_CAP1_TIMER                  2
#define INPUT_CAP1_CHANNEL     /* T2C4 */ 4
#define GPIO_INPUT_CAP1        /* PB11 */ GPIO_TIM2_CH4_IN

#define INPUT_CAP2_TIMER                  2
#define INPUT_CAP2_CHANNEL     /* T2C2 */ 2
#define GPIO_INPUT_CAP2        /*  PB3 */ GPIO_TIM2_CH2_IN

#define INPUT_CAP3_TIMER                  2
#define INPUT_CAP3_CHANNEL     /* T2C1 */ 1
#define GPIO_INPU3_CAP1        /*  PA5 */ GPIO_TIM2_CH1_IN

#define INPUT_CAP4_TIMER                  12
#define INPUT_CAP4_CHANNEL     /* T12C2*/ 2
#define GPIO_INPUT_CAP4        /* PH9  */ GPIO_TIM12_CH2_IN

#define INPUT_CAP5_TIMER                  12
#define INPUT_CAP5_CHANNEL     /* T12C1*/ 1
#define GPIO_INPUT_CAP5        /* PH6  */ GPIO_TIM12_CH1_IN

#define INPUT_CAP6_TIMER                  4
#define INPUT_CAP6_CHANNEL     /* T4C3 */ 3
#define GPIO_INPUT_CAP6        /* PD14 */ GPIO_TIM4_CH3_IN

/* PWM input driver. Use FMU AUX5 pins attached to timer4 channel 2 */

#define PWMIN_TIMER                       4
#define PWMIN_TIMER_CHANNEL    /* T4C2 */ 2
// #define GPIO_PWM_IN            /* PD13 */ GPIO_TIM4_CH2IN

/* RSSI_IN is grounded via a 10K */

#define GPIO_RSSI_IN                       /* PB0  */ (GPIO_INPUT|GPIO_PULLDOWN|GPIO_PORTB|GPIO_PIN0)

/* Safety Switch is only on PX4IO */

#define GPIO_nSAFETY_SWITCH_LED_OUT   /* PE12 */ (GPIO_INPUT|GPIO_PULLDOWN|GPIO_PORTE|GPIO_PIN12)
#define GPIO_SAFETY_SWITCH_IN         /* PE10 */ (GPIO_INPUT|GPIO_PULLDOWN|GPIO_PORTE|GPIO_PIN10)

/* Power switch controls ******************************************************/

#define SPEKTRUM_POWER(_on_true)           VDD_3V3_SPEKTRUM_POWER_EN(_on_true)


#define BOARD_HAS_POWER_CONTROL	1
/*power on/off*/
#define MS_PWR_BUTTON_DOWN 1500
#define KEY_AD_GPIO    (GPIO_INPUT|GPIO_PULLUP|GPIO_EXTI|GPIO_PORTC|GPIO_PIN4)
#define POWER_ON_GPIO  (GPIO_OUTPUT|GPIO_PUSHPULL|GPIO_SPEED_2MHz|GPIO_OUTPUT_SET|GPIO_PORTC|GPIO_PIN5)
#define POWER_OFF_GPIO (GPIO_INPUT|GPIO_PULLDOWN|GPIO_PORTC|GPIO_PIN5)
#define POWER_CHECK_GPIO (GPIO_INPUT|GPIO_PULLUP|GPIO_PORTF|GPIO_PIN0)

#define SDIO_SLOTNO                    0  /* Only one slot */
#define SDIO_MINOR                     0

/* SD card bringup does not work if performed on the IDLE thread because it
 * will cause waiting.  Use either:
 *
 *  CONFIG_LIB_BOARDCTL=y, OR
 *  CONFIG_BOARD_INITIALIZE=y && CONFIG_BOARD_INITTHREAD=y
 */

#if defined(CONFIG_BOARD_INITIALIZE) && !defined(CONFIG_LIB_BOARDCTL) && \
   !defined(CONFIG_BOARD_INITTHREAD)
#  warning SDIO initialization cannot be perfomed on the IDLE thread
#endif

/* By Providing BOARD_ADC_USB_CONNECTED (using the px4_arch abstraction)
 * this board support the ADC system_power interface, and therefore
 * provides the true logic GPIO BOARD_ADC_xxxx macros.
 */
#define BOARD_ADC_USB_CONNECTED (px4_arch_gpioread(GPIO_OTGFS_VBUS))
#define BOARD_ADC_USB_VALID     (px4_arch_gpioread(GPIO_OTGFS_VBUS))

/* Board never powers off the Servo rail */

#define BOARD_ADC_SERVO_VALID     (1)

#define BOARD_ADC_BRICK_VALID  	  (1) //!px4_arch_gpioread(GPIO_VDD_BRICK_VALID))

#define BOARD_ADC_PERIPH_5V_OC  (!px4_arch_gpioread(GPIO_nVDD_5V_PERIPH_OC))
#define BOARD_ADC_HIPOWER_5V_OC (!px4_arch_gpioread(GPIO_nVDD_5V_HIPOWER_OC))

#define BOARD_HAS_PWM  DIRECT_PWM_OUTPUT_CHANNELS

/* This board provides a DMA pool and APIs */
#define BOARD_DMA_ALLOC_POOL_SIZE 5120

/* This board provides the board_on_reset interface */

#define BOARD_HAS_ON_RESET 1
#define SDMMC_PIN_OFF(def) (((def) & (GPIO_PORT_MASK | GPIO_PIN_MASK)) | (GPIO_INPUT|GPIO_FLOAT|GPIO_SPEED_2MHz))

#define PX4_GPIO_INIT_LIST { \
		PX4_ADC_GPIO,                     \
		GPIO_HW_REV_DRIVE,                \
		GPIO_HW_VER_DRIVE,                \
		GPIO_CAN1_SILENT_S0,              \
		GPIO_CAN2_SILENT_S1,              \
		GPIO_CAN3_SILENT_S2,		  \
		GPIO_HEATER_OUTPUT,               \
		GPIO_nPOWER_IN_A,                 \
		GPIO_nPOWER_IN_B,                 \
		GPIO_nPOWER_IN_C,                 \
		GPIO_nVDD_5V_PERIPH_EN,           \
		GPIO_nVDD_5V_PERIPH_OC,           \
		GPIO_nVDD_5V_HIPOWER_EN,          \
		GPIO_nVDD_5V_HIPOWER_OC,          \
		GPIO_VDD_3V3_SENSORS_EN,	  \
		GPIO_VDD_5V_RC_EN,		  \
		GPIO_VDD_3V3_SPEKTRUM_POWER_EN,   \
		SDMMC_PIN_OFF(GPIO_SDMMC1_D0),    \
		SDMMC_PIN_OFF(GPIO_SDMMC1_D1),    \
		SDMMC_PIN_OFF(GPIO_SDMMC1_D2),    \
		SDMMC_PIN_OFF(GPIO_SDMMC1_D3),    \
		SDMMC_PIN_OFF(GPIO_SDMMC1_CMD),   \
		GPIO_VDD_3V3_SD_CARD_EN,          \
		GPIO_TONE_ALARM_IDLE,             \
		GPIO_RSSI_IN,                     \
		GPIO_OTGFS_VBUS,		  \
		GPIO_nSAFETY_SWITCH_LED_OUT,      \
		GPIO_SAFETY_SWITCH_IN,            \
	}

#define BOARD_ENABLE_CONSOLE_BUFFER

__BEGIN_DECLS

/****************************************************************************************************
 * Public Types
 ****************************************************************************************************/

/****************************************************************************************************
 * Public data
 ****************************************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************************************
 * Public Functions
 ****************************************************************************************************/

/****************************************************************************
 * Name: stm32_sdio_initialize
 *
 * Description:
 *   Initialize SDIO-based MMC/SD card support
 *
 ****************************************************************************/

int stm32_sdio_initialize(void);

/****************************************************************************************************
 * Name: stm32_spiinitialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the CODEV AQUILA
 *   board.
 *
 ****************************************************************************************************/

extern void stm32_spiinitialize(void);

extern void stm32_usbinitialize(void);

extern void board_peripheral_reset(int ms);

void board_pwr_init(int stage);

/****************************************************************************
 * Name: board_pwr_button_down
 *
 * Description:
 *   Called to Read the logical state of the power button
 ****************************************************************************/

bool board_pwr_button_down(void);

int board_shutdown(void);

#include <px4_platform_common/board_common.h>

#endif /* __ASSEMBLY__ */

__END_DECLS
