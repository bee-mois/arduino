/**
 *
 * Generic software breadboard for nodes, transceivers and gateways.
 *
 * Configuration file: "config.h".
 * All settings for controlling the behavior and role
 * of the firmware should be made inside this file.
 *
 * Software release 0.15.0
 *
 * Copyright (C) 2014-2017  Richard Pobering <einsiedlerkrebs@ginnungagap.org>
 * Copyright (C) 2014-2017  Andreas Motl <andreas.motl@elmyra.de>
 *
**/


#define HE_DEBUG                  true               // turn on debug output and choose below
#define SERIAL_BAUD               115200         // serial baud rate
#define BLINKPERIOD               500            // LED blinking period in ms
#define BOOTSTRAP_LOOP_COUNT      15             // How often to loop fast when booting
#define HE_SLEEP                  false              // enable sleeping
#define HE_SCALE                  false
#define HE_HUMIDITY               false
#define HE_TEMPERATURE            false
#define HE_DEMODATA               false
#define HE_RFM69_OTA              false
#define HE_BERadio                false
#define HE_RADIO                  false
//#define HE_CONTAINERS             false


#define IS_NODE                   false
#define IS_TRANSCEIVER            false
#define IS_GATEWAY                false


#define HE_RFM69                  false              // LowPowerLab RFM69 library
#define HE_RH69                   false              // RadioHead RH_RF69 driver
#define HE_RH95                   false              // RadioHead RH_RF95 driver
#define HE_RHTCP                  false              // RadioHead RH_TCP driver
#define HE_FLASH                  false              // Enable SPI-flash


// Compute custom configuration file
// See also: https://stackoverflow.com/questions/5873722/c-macro-dynamic-include
#ifdef CUSTOM_CONFIG
    #define PASTER(str)   #str
    #define EVALUATOR(x)  PASTER(x)
    #define CUSTOM_CONFIG_FILE EVALUATOR(CUSTOM_CONFIG)
#endif

// Custom config: Used here to overwrite toplevel settings
// To include a custom "config_xxx.h" (e.g. config_node.h vs. config_gateway.h).
// Examples:
//
//      make -f Makefile-OSX.mk HE_ROLE=node        # config_node.h
//      make -f Makefile-OSX.mk HE_ROLE=gateway     # config_gateway.h
//
// ... you get the idea!?
//
#ifdef CUSTOM_CONFIG_FILE
    #include CUSTOM_CONFIG_FILE
#endif


#if HE_DEBUG                                  /**    fine grade debug settings     ***
                                                 ***              * *                 **/
    #define DEBUG_FRAME           false
    #define DEBUG_RADIO           true              // set to 1 for radio debug
    #define DEBUG_SPI_FLASH       false              // set to 1 for SPI-flash debug
    #define DEBUG_SENSORS         false              // set to 1 for sensor debug
    #define DEBUG_BERadio         true              // set to 1 for  HE_BERadio degub
    #define DEBUG_MEMORY          false

#endif                                           /**              * *                 **/


#if HE_BERadio
    #define  BERadio_profile           "h1"           //  HE_BERadio profile
    #define  HE_HIVE_ID                2
    #define  BAD_VALUE             273.15
    #define  BERadio_DELAY         500
    #if HE_CONTAINERS == false
        #define HE_CONTAINERS      true
    #endif
#endif

#if HE_SLEEP
    #define SLEEP_MINUTES             15             // sleeptime in about minutes
#endif

                                                 /**            * * * *               ***
                                                 ***        hardware switches         ***
                                                 ***             * * *                **/


#ifndef HE_ARDUINO
    #define HE_ARDUINO              true
#endif
#ifdef __unix__
    #define HE_ARDUINO              false
    #define DEBUG_MEMORY            false
    #define HE_RH69                 false
    #define HE_RH95                 false
    #define HE_RHTCP                true
    #define HE_SCALE                false
    #define HE_HUMIDITY             false
    #define HE_TEMPERATURE          false
    #define HE_DEMODATA             true
#endif


/*
#if IS_TRANSCEIVER
    #define IS_NODE                false
    #define IS_GATEWAY             false
#elif IS_GATEWAY
    #define IS_NODE                false
    #define IS_TRANSCEIVER         false
#elif IS_NODE
    #define IS_TRANSCEIVER         false
    #define IS_GATEWAY             false
#endif
*/
                                                 /**            * * * *               ***
                                                 ***    sensor pinning & settings     ***
                                                 ***             * * *                **/

#ifdef HE_TEMPERATURE
    #define DS18B20_BUS           9              // DS18B20 data pin
    #define TEMP_PRECISION        9              // DS18B20 value resolution
    #if HE_CONTAINERS
        #define CONT_HUM            true
    #endif
#endif

#ifdef  HE_HUMIDITY
    #define DHT_AMOUNT                1
    #define DHT_PIN1                  7              // DHT pin #1
    #define DHT_PIN2                  6              // DHT pin #2
    #define DHT_TYPE                  DHT22          // DHT type (dht22)
    #if HE_CONTAINERS
        #define CONT_HUM             true
        #ifndef CONT_TEMP
            #define CONT_TEMP        true
        #endif
    #endif
#endif

#ifdef HE_SCALE
    #define HX711_SCK                 A0             // SCK pin of hx711
    #define HX711_DT                  A1             // DT pin for hx711
    #define HX711_OFFSET          8361975

    #define HX711_KNOWN_WEIGHT     21901.f
    #ifdef HE_CONTAINERS
        #define CONT_WGHT        true
    #endif
#endif

                                                 /**            * * * *               ***
                                                 ***    specific hardware defines     ***
                                                 ***             * * *                **/
#ifdef HE_RADIO
    #define RH_ACK_TIMEOUT           200
    #if HE_RH69                                     /**   RadioHead's HE_RH69radio lib     **/
        #define RH69_NODE_ID          99             //    radio topology
        #define RH69_RESCEIVER_ID       1              // ID of next RESCEIVER (gateway | transceiver)
        //#define RH69_TRANSCEIVER_ID   3              //

        #define RH69_IRQ              2             // radio pins
        #define RH69_SS               10              //

        #define RH69_FREQUENCY        868.0         // modem settings
        #define RH69_MAX_MESSAGE_LEN 61



    #endif                                           /**              * *                 **/

    #if HE_RH95                                     /**     RadioHead's HE_RH95radio lib   **/

        #define RH95_NODE_ID          99             //       radio topology
        #define RH95_RESCEIVER_ID       1            // ID of next RESCEIVER (gateway | transceiver)
        //#define RH95_TRANSCEIVER_ID   3              //
        #if IS_TRANSCEIVER
            #define RH95_IRQ              3             // radio pins
            #define RH95_SS               5              //
        #elif IS_GATEWAY
            #define RH95_IRQ              2             // radio pins
            #define RH95_SS               10              //
        #endif


        #define RH95_FREQUENCY        868.0         // modem settings
        #define RH95_MAX_MESSAGE_LEN 255

    #endif                                           /**              * *                 **/

    // RadioHead HE_TCP driver
    #if HE_RHTCP
        #define RHTCP_NODE_ID         99
        #define RHTCP_GATEWAY_ID      1
    #endif

    #if HE_RFM69                                     /**     HE_RFM69 lib from lowpowerlab   **/
        //#include <HE_RFM69.h>                           /**              * *                 **/


        #define RFM69_NODE_ID         2              //
        #define RFM69_NETWORK_ID      100            // radio topology
        #define RFM69_GATEWAY_ID      1              //

        #define RFM69_FREQUENCY       RF69_868MHZ         // modem settings
        #define RFM69_IS_HW            0              // set to 1 for HE_RFM69HW
        #define RADIO_STATIC_POWER    0              // set to 1 for static power
        #define RFM69_POWERLEVEL            5              // powerlevel range between 1-24(?)
        //#define ENABLE_ATC                           // 1 for automatic transmission control (ATC)
        #ifdef  RFM69_ENABLE_ATC
            #define RFM69_TARGET_RSSI       -70            // RSSI
        #endif
        #define RFM69_ENCRYPTKEY      "www.hiveeyes.org"   // same 16 characters/bytes everywhere
        #define RFM69_ACK_TIME              30             // acknowledge timeout in ms
        #define RFM69_MAX_MESSAGE_LENGTH    61             // Payload limitation HE_RFM69


    #endif                                           /**              * *                 **/
#endif

#if HE_FLASH                                 /**           SPI-Flash              **/
    #define FLASH_MANUFACTURER_ID 0x0102         // MANUFACTURER_ID
                                                 // 0x1F44 for adesto(ex atmel) 4mbit flash
                                                 // 0xEF30 for windbond 4mbit flash
                                                 // 0xEF40 for windbond 16/64mbit flash
                                                 // 0x0102 for Spansion S25FL032P 32-Mbit
    #if HE_RFM69_OTA
        #include <WirelessHEX69.h>
    #endif

#endif                                           /**              * *                 **/


                                                 /**            * * * *               ***
                                                 ***   automatic compiler directives  ***
                                                 ***             * * *                **/
#ifdef __AVR_ATmega1284P__
    #define LED                   15             // most Megas have LEDs on D15
    #define FLASH_SS              23             // and FLASH SS on D23
#else
    #define LED                   13             // Pro328mini has LEDs on D9
    #define FLASH_SS              8              // and FLASH SS on D8
#endif



// Custom config: Now used to overwrite evaluated settings
#ifdef CUSTOM_CONFIG_FILE
    #include CUSTOM_CONFIG_FILE
#endif
