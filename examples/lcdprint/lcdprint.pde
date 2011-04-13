#include <Wire.h>
#include <MCP23018.h>
#include <LiquidCrystal2.h>
#include <LcdMCP23018.h>

/**
 * @file lcdprint.pde
 *
 * Simple example to print text to an LCD controlled by
 * MCP23018 i/o extender.
 */

MCP23018 pex(7);
LcdMCP23018 hwif(&pex);
LiquidCrystal2 lcd(&hwif);

void setup(void)
{
    Wire.begin();
    pex.begin();
    hwif.begin();
    lcd.begin(16,2);

    lcd.clear();
    lcd.print("I speak I2C. Are");
    lcd.setCursor(0,1);
    lcd.print("you proud of me?");
}

void loop(void)
{
}

// vim:ai:cin:sts=4 sw=4 ft=cpp
