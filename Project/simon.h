// Nathan Okoh

#ifndef SIMON_H
#define SIMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Base addresses for peripheral registers
#define RCC_BASE        0x40021000  // Base address for the RCC (Reset and Clock Control)
#define GPIOA_BASE      0x40010800  // Base address for GPIO port A
#define GPIOB_BASE      0x40010C00  // Base address for GPIO port B
#define GPIOC_BASE      0x40011000  // Base address for GPIO port C

// RCC Register Definition
#define RCC             ((RCC_TypeDef *) RCC_BASE)  // Define RCC as a pointer to RCC_TypeDef at the RCC base address

// GPIO Register Definition for GPIO ports A, B, and C
#define GPIOA           ((GPIO_TypeDef *) GPIOA_BASE)  // Define GPIOA as a pointer to GPIO_TypeDef at GPIOA base address
#define GPIOB           ((GPIO_TypeDef *) GPIOB_BASE)  // Define GPIOB as a pointer to GPIO_TypeDef at GPIOB base address
#define GPIOC           ((GPIO_TypeDef *) GPIOC_BASE)  // Define GPIOC as a pointer to GPIO_TypeDef at GPIOC base address

// Define structures to represent the register layout for RCC and GPIO
// This provides a structured way to access each register within the RCC and GPIO peripherals


#define NUMBER_OF_LEDS 4
#define MAX_ROUNDS 10

// RCC Register Structure
typedef struct {
    volatile uint32_t CR;        // Clock control register
    volatile uint32_t CFGR;      // Clock configuration register
    volatile uint32_t CIR;       // Clock interrupt register
    volatile uint32_t APB2RSTR;  // APB2 peripheral reset register
    volatile uint32_t APB1RSTR;  // APB1 peripheral reset register
    volatile uint32_t AHBENR;    // AHB peripheral clock enable register
    volatile uint32_t APB2ENR;   // APB2 peripheral clock enable register
    volatile uint32_t APB1ENR;   // APB1 peripheral clock enable register
    volatile uint32_t BDCR;      // Backup domain control register
    volatile uint32_t CSR;       // Control/status register
    volatile uint32_t RESERVED0; // Reserved space in memory
    volatile uint32_t CFGR2;     // Clock configuration register 2
} RCC_TypeDef;                   // Typedef for RCC registers as a struct (used to access RCC registers as a group)

// GPIO Register Structure
typedef struct {
    volatile uint32_t CRL;       // Port configuration register low (configures pins 0-7)
    volatile uint32_t CRH;       // Port configuration register high (configures pins 8-15)
    volatile uint32_t IDR;       // Input data register (reads input pin states)
    volatile uint32_t ODR;       // Output data register (sets output pin states)
} GPIO_TypeDef;                  // Typedef for GPIO registers as a struct (used to access GPIO registers as a group)


void GPIO_Config();          // Configure GPIO pins for LEDs and buttons 

void beginningSequence();
void delay(int);
int checkButtonPress();
 
void roundHandler();
int randomNumberTo4();
void lightLED(int);     // lights the coresponging LED to the button the user presses, goof for visual feedback
void winSequence();
void failSequence();
void binaryLED(int);
int getUserInput();
void displaySequence(int);


#endif
