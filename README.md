# SimonGame
The Final Project for ENSE352 - Fundamentals of Computer System Architecture

# Video Showcase 
https://youtube.com/shorts/7o1RiaVvYJE?feature=share

# Project Overview
The project is based on it's namesake, electronic short-term memory game by Hasbro. The game starts off with a "Knight Rider" light sequence. This sequence is just the leds flashing on by one in a cycle so it looks like the light is moving. Once user presses any button the first round will start, it will light up LEDs at random and the user must input the correct sequence. If the user fails to enter the correct sequence within a certain amount of time, or enters a wrong input, the LEDs will display a fail sequence and then light up the binary number of the round the user failed on, until the user presses any button to restart the game. If the user completes 10 rounds, they win! the LEDs will display a win sequence and then light up the binary digit 10, until the user presses any button to restart the game.

# Winning Sequence
All 4 LEDS flashing four times, and then lighting up the binary digit 10 (1010). Only displayed when the user has completed 10 rounds (5 rounds in the demo video)
#Failure Sequence
Occurs when..
- User enters and incorrect input that does not match the sequence
- Use takes too long (exceeds 14 seconds for the round)
The failure sequence is the odd and even LEDS flashing back and forth 4 times, (1010, 0101), and then lighting up the binary digit of the round the user failed on.

#Components
- STM32F103RB
- Breadboard
- 270 Ohm resistor
- 2 Green LEDs
- 2 Red LEDs
- 4 push buttons

# Gameplay
1. Start the game
The Knight rider sequence is going, you press any button and the first round will start
2. Rounds
The first round starts with a 1 LED sequence, which you will then input. The second round has a 2 LED sequence which you then input, so on and so forth

# Enjoy!
