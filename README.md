# OpenSimHardware Pedals & Buttons Controller

STM32F103C8T6-based Pedals & Buttons Controller (Joystick/GamePad interface) for DIY pedals, button boxes, shifters, hand brakes, etc

Capabilities:
- 6x 12-bit (4096 steps) axises
- support rotary encoders
- support buttons in matrix
- support single buttons
- support rotary switches
- support POV Hat Switches
- up to 1kHz exchange rate with PC


<pre>
Default Pinout:
		 STM32F103C8T6
		  -----------------
		- |3VB		 +3.3V| -
  		- |C13		   GND| -
  COL1	- |C14		   +5V| - 
  COL2	- |C15		    B9| - ROW6
  ADC0 	- |A0		    B8| - ROW5
  ADC1 	- |A1		    B7| - ROW4
  ADC2	- |A2		    B6| - ROW3
  ADC3	- |A3		    B5| - ROW2
  ADC4	- |A4		    B4| - ROW1
  ADC5	- |A5		    B3| - COL4
  ROT10	- |A6		   A15| - ROT9
  COL6	- |A7		   A12| - 
  ROT1	- |B0		   A11| - 
  ROT2	- |B1		   A10| - ROT8
  ROTA	- |B10		    A9| - ROT7
  ROTB	- |B11		    A8| - ROT6
		- |R		   B15| - ROT5
		- |+3.3V	   B14| - ROT4
		- |GND		   B13| - ROT3
		- |GND		   B12| - COL3
		  ----------------
		  
</pre>
		  

Project URL - https://opensimhardware.wordpress.com/pedal-button-controller/