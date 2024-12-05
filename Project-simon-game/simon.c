// Nathan Okoh

#include "simon.h"

void GPIO_Config() {
    // Enable clocks for GPIOA, GPIOB, and GPIOC
    RCC->APB2ENR |= (1 << 2) | (1 << 3) | (1 << 4);  // Enable GPIOA, GPIOB, and GPIOC clocks by setting bits 2, 3, and 4 in APB2ENR

    // Configure PA0, PA1, PA4, and PA5 as output for LEDs
    GPIOA->CRL &= ~(0xF << 0);    // Clear bits 0-3 for PA0
    GPIOA->CRL |= (0x2 << 0);     // Set PA0 as output, 2 MHz, push-pull

    GPIOA->CRL &= ~(0xF << 4);    // Clear bits 4-7 for PA1
    GPIOA->CRL |= (0x2 << 4);     // Set PA1 as output, 2 MHz, push-pull

    GPIOA->CRL &= ~(0xF << 16);   // Clear bits 16-19 for PA4
    GPIOA->CRL |= (0x2 << 16);    // Set PA4 as output, 2 MHz, push-pull

    GPIOA->CRL &= ~(0xF << 20);   // Clear bits 20-23 for PA5
    GPIOA->CRL |= (0x2 << 20);    // Set PA5 as output, 2 MHz, push-pull

    // Configure PB0 as output for LED
    GPIOB->CRL &= ~(0xF << 0);    // Clear bits 0-3 for PB0
    GPIOB->CRL |= (0x2 << 0);     // Set PB0 as output, 2 MHz, push-pull

    // Configure PC13 as input floating for button
    GPIOC->CRH &= ~(0xF << 20);   // Clear settings for PC13 (bits 20-23)
    GPIOC->CRH |= (0x4 << 20);    // Set PC13 as input floating
}

int seed = 0;            // Global variable for seed
int incrementedSeed = 0;
void beginningSequence() {
    // Cylon Eye Scanner (Knight Rider) light sequence
    // LEDs will light up in a sequence from PA0 to PA4 and then back to PA0
    // It will continue until any button is pressed
    // Start the Cylon sequence and continue until a button is pressed
		 incrementedSeed = 0;
	
    while (1) {  
        // Increment pressTime with each loop iteration
				incrementedSeed++;
        // LED Sequence: PA0, PA1, PA4, PB0, PA4, PA1
        GPIOA->ODR |= (1 << 0); // Turn on PA0
        delay(100); // Delay
        GPIOA->ODR &= ~(1 << 0); // Turn off PA0
        // Button press check after each LED action
        if (checkButtonPress()) {
					GPIOA->ODR &= ~(0x1F);  // Turn off all LEDs (PA0 to PA4)
					break;
				}
				
				incrementedSeed++;
        GPIOA->ODR |= (1 << 1); // Turn on PA1
        delay(100); // Delay
        GPIOA->ODR &= ~(1 << 1); // Turn off PA1
        seed++;
        // Button press check after each LED action
        if (checkButtonPress()) {
					GPIOA->ODR &= ~(0x1F);  // Turn off all LEDs (PA0 to PA4)
					break;
				}
				
				incrementedSeed++;
        GPIOA->ODR |= (1 << 4); // Turn on PA4
        delay(100); // Delay
        GPIOA->ODR &= ~(1 << 4); // Turn off PA4
        seed++;
        // Button press check after each LED action
        if (checkButtonPress()) {
					GPIOA->ODR &= ~(0x1F);  // Turn off all LEDs (PA0 to PA4)
					break;
				}
				
				incrementedSeed++;
        GPIOB->ODR |= (1 << 0); // Turn on PB0
        delay(100); // Delay
        GPIOB->ODR &= ~(1 << 0); // Turn off PB0
        
        // Button press check after each LED action
        if (checkButtonPress()) {
					GPIOA->ODR &= ~(0x1F);  // Turn off all LEDs (PA0 to PA4)
					break;
				}
				
				incrementedSeed++;
        GPIOA->ODR |= (1 << 4); // Turn on PA4
        delay(100); // Delay
        GPIOA->ODR &= ~(1 << 4); // Turn off PA4
				
       // Button press check after each LED action
        if (checkButtonPress()) {
					GPIOA->ODR &= ~(0x1F);  // Turn off all LEDs (PA0 to PA4)
					break;
				}
				
				incrementedSeed++;
        GPIOA->ODR |= (1 << 1); // Turn on PA1
        delay(100); // Delay
        GPIOA->ODR &= ~(1 << 1); // Turn off PA1
       // Button press check after each LED action
        if (checkButtonPress()) {
					GPIOA->ODR &= ~(0x1F);  // Turn off all LEDs (PA0 to PA4)
					break;
				}
    }
		seed = incrementedSeed;  // Assign the incremented seed to the global 'seed'
}

void delay(int delay) {
    for (int i = 0; i < delay * 4000; i++);
}

int checkButtonPress() {
    return ((GPIOC->IDR & (1 << 13)) == 0) || 
           ((GPIOB->IDR & (1 << 4)) == 0) || 
           ((GPIOB->IDR & (1 << 6)) == 0) || 
           ((GPIOB->IDR & (1 << 8)) == 0) || 
           ((GPIOB->IDR & (1 << 9)) == 0);
}

int randomNumberTo4() {
    int limit = RAND_MAX - (RAND_MAX % NUMBER_OF_LEDS);
    int r;

    while ((r = rand()) >= limit);

    return r % NUMBER_OF_LEDS;
}

void lightLED(int ledIndex) {
    switch (ledIndex) {
        case 0:
            GPIOA->ODR |= (1 << 0); // Turn on PA0
            delay(200);
            GPIOA->ODR &= ~(1 << 0); // Turn off PA0
            break;
        case 1:
            GPIOA->ODR |= (1 << 1); // Turn on PA1
            delay(200);
            GPIOA->ODR &= ~(1 << 1); // Turn off PA1
            break;
        case 2:
            GPIOA->ODR |= (1 << 4); // Turn on PA4
            delay(200);
            GPIOA->ODR &= ~(1 << 4); // Turn off PA4
            break;
        case 3:
            GPIOB->ODR |= (1 << 0); // Turn on PB0
            delay(200);
            GPIOB->ODR &= ~(1 << 0); // Turn off PB0
            break;
        default:
            break;
    }
}

void winSequence() {
	// binary 10 (1010)
	delay(300);
	GPIOA->ODR |= (1 << 0); // Turn on PA0
	GPIOA->ODR |= (1 << 4); // Turn on PA4
	delay(300);
	GPIOA->ODR &= ~(1 << 0); // Turn off PA0
	GPIOA->ODR &= ~(1 << 4); // Turn off PA4
		
	for (int i = 0; i < 4; i++) {
			GPIOA->ODR |= (1 << 0); // Turn on PA0
			GPIOA->ODR |= (1 << 1); // Turn on PA1	
			GPIOA->ODR |= (1 << 4); // Turn on PA4
			GPIOB->ODR |= (1 << 0); // Turn on PB0
			delay(100);
			GPIOA->ODR &= ~(1 << 0); // Turn off PA0
			GPIOA->ODR &= ~(1 << 1); // Turn off PA1	
			GPIOA->ODR &= ~(1 << 4); // Turn off PA4
			GPIOB->ODR &= ~(1 << 0); // Turn of PB0
			delay(100); 
			}	
}

void failSequence(){
	for (int i = 0; i < 4; i++) {
		GPIOA->ODR |= (1 << 0); // Turn on PA0
		GPIOA->ODR |= (1 << 4); // Turn on PA4
		delay(100);
		GPIOA->ODR &= ~(1 << 0); // Turn off PA0
		GPIOA->ODR &= ~(1 << 4); // Turn off PA4
		delay(100); 
		GPIOA->ODR |= (1 << 1); // Turn on PA1
		GPIOB->ODR |= (1 << 0); // Turn on PB0
		delay(100);
		GPIOA->ODR &= ~(1 << 1); // Turn off PA1
		GPIOB->ODR &= ~(1 << 0); // Turn of PB0
		delay(100);
	}
}

void binaryLED(int round) {
    switch (round) {
        case 1:
          for (int i = 0; i < 4; i++) { // binary 1
            delay(100);
            GPIOA->ODR |= (1 << 0); // Turn on LED 1
            delay(100);
            GPIOA->ODR &= ~(1 << 0); // Turn off 
            delay(100);
          }
            break;
        case 2:
          for (int i = 0; i < 4; i++) { // binary 2
            delay(100);
            GPIOA->ODR |= (1 << 1); // Turn on LED 2
            delay(100);
            GPIOA->ODR &= ~(1 << 1); 
            delay(100);
          }
            break;
        case 3:
          for (int i = 0; i < 4; i++) { // binary 3
            delay(100);
            GPIOA->ODR |= (1 << 0); // Turn on LED 1
            GPIOA->ODR |= (1 << 1); // Turn on LED 2
            delay(100);
            GPIOA->ODR &= ~(1 << 0); // Turn off 
            GPIOA->ODR &= ~(1 << 1); 
            delay(100);
          }
            break;
        case 4:
          for (int i = 0; i < 4; i++) { // binary 4
            delay(100);
            GPIOA->ODR |= (1 << 4); // Turn on LED 3
            delay(100);
            GPIOA->ODR &= ~(1 << 4); // turn off
            delay(100);
          }
            break;
        case 5:
          for (int i = 0; i < 4; i++) { // binary 5
            delay(100);
            GPIOA->ODR |= (1 << 0); // Turn on LED 1
            GPIOA->ODR |= (1 << 4); // Turn on LED 3
            delay(100);
            GPIOA->ODR &= ~(1 << 0); // Turn off 
            GPIOA->ODR &= ~(1 << 4); // turn off
            delay(100);
          }
            break;
         case 6:
          for (int i = 0; i < 4; i++) { // binary 6
            delay(100);
            GPIOA->ODR |= (1 << 1); // Turn on LED 2
            GPIOA->ODR |= (1 << 4); // Turn on LED 3
            delay(100);
            GPIOA->ODR &= ~(1 << 1); // Turn off 
            GPIOA->ODR &= ~(1 << 4); // turn off
            delay(100);
          }
            break;
         case 7:
          for (int i = 0; i < 4; i++) { // binary 7
            delay(100);
            GPIOA->ODR |= (1 << 0); // Turn on LED 1
            GPIOA->ODR |= (1 << 1); // Turn on LED 2
            GPIOA->ODR |= (1 << 4); // Turn on LED 3
            delay(100); // Delay
            GPIOA->ODR &= ~(1 << 0); // Turn off 
            GPIOA->ODR &= ~(1 << 1); // Turn off 
            GPIOA->ODR &= ~(1 << 4); // turn off
            delay(100);
          }
            break;
         case 8:
          for (int i = 0; i < 4; i++) { // 8 
            delay(100);
            GPIOB->ODR |= (1 << 0); 
            delay(100); 
            GPIOB->ODR &= ~(1 << 0); 
            delay(100);
          }	
            break;
         case 9:
           for (int i = 0; i < 4; i++) { // 9
            delay(100);
            GPIOA->ODR |= (1 << 0); 
            GPIOB->ODR |= (1 << 0); 
            delay(100);
            GPIOA->ODR &= ~(1 << 0); 
            GPIOB->ODR &= ~(1 << 0); 
            delay(100);
          }	
            break;
         case 10:
           for (int i = 0; i < 4; i++) { // 10
            delay(100);
            GPIOA->ODR |= (1 << 1); 
            GPIOB->ODR |= (1 << 0); 
            delay(100);
            GPIOA->ODR &= ~(1 << 1); 
            GPIOB->ODR &= ~(1 << 0); 
            delay(100);
          }	
           break;
        default:
            break;
    }
}

int getUserInput() {
    if ((GPIOB->IDR & (1 << 4)) == 0) return 0; // Black button
    if ((GPIOB->IDR & (1 << 6)) == 0) return 1; // Red button
    if ((GPIOB->IDR & (1 << 8)) == 0) return 2; // Green button
    if ((GPIOB->IDR & (1 << 9)) == 0) return 3; // Blue button
    return -1; // No button pressed
}

int sequence[MAX_ROUNDS]; // Array to store the LED sequence
int currentRound = 0;

void displaySequence(int round) {
    for (int i = 0; i < round; i++) {
        int ledIndex = sequence[i];  // Get the LED index from the sequence
        lightLED(ledIndex);  // Light up the LED corresponding to that index
        delay(400); // Delay between LED flashes
    }
}

void roundHandler() {
    // Generate the full random sequence at the start of the game
    for (int i = 0; i < MAX_ROUNDS; i++) {
        sequence[i] = randomNumberTo4();  // Random LED value (0-3)
    }

    currentRound = 0; // Start from round 1

    // Main game loop
    while (currentRound < MAX_ROUNDS) {
        currentRound++; // Increment round

        // Display the sequence for the current round
        displaySequence(currentRound);

        // Prepare for user input
        int timeout = 7000000; // Timeout duration for the entire round 7 seconds x 2, 14 seconds
        int elapsed = 0;       // Elapsed time counter
        int inputCount = 0;         // Number of inputs received

        // Wait for the user to input the sequence
        while (elapsed < timeout && inputCount < currentRound) {
            int input = getUserInput(); // Get the user input
            if (input != -1) {          // As long as there's input
                lightLED(input);        // Provide feedback by lighting the corresponding LED

                // Validate each individual input
                if (input != sequence[inputCount]) {
                    binaryLED(currentRound);
                    failSequence(); // Trigger fail sequence
                    return;         // End the game immediately
                }

                inputCount++; // Increment the count of inputs
            }
            elapsed++; // Increment elapsed time
        }

        // Check if user failed to provide enough inputs in time
        if (inputCount < currentRound) {
            
            binaryLED(currentRound);
            failSequence(); // Trigger fail sequence
            return;         // End the game
        }

        // Delay before moving to the next round
        delay(500);
    }

    // If all rounds are completed, trigger the win sequence
    winSequence();
}



int main(void) {
   GPIO_Config(); // Initialize GPIOs

    while (1) { // Infinite loop for restarting the game
        beginningSequence(); // Start the game with the Knight Rider sequence

        srand(seed); // Seed the random number generator
        delay(500);

        roundHandler(); // Run the main game logic

        // Wait for any button press to restart the game
        while (1) {
            if (((GPIOC->IDR & (1 << 13)) == 0) || // Check PC13
                ((GPIOB->IDR & (1 << 4)) == 0) ||  // Check PB4
                ((GPIOB->IDR & (1 << 6)) == 0) ||  // Check PB6
                ((GPIOB->IDR & (1 << 8)) == 0) ||  // Check PB8
                ((GPIOB->IDR & (1 << 9)) == 0)) {  // Check PB9
                delay(500); // Debounce delay
                break;      // Exit the waiting loop and restart
            }
        }
    }
}
