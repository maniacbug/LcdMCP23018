#include <Wire.h>
#include <MCP23018.h>
#include <LcdMCP23018.h>

#undef DEBUG

uint8_t DB_shift = 2; // D4-7 on d2-5
uint8_t Enable_shift = 1; // Enable on d1
uint8_t RS_shift = 0; // RS on d0

uint8_t DB_mask = 0xf << DB_shift;
uint8_t Enable_mask = 1 << Enable_shift;
uint8_t RS_mask = 1 << RS_shift;

LcdMCP23018::LcdMCP23018(MCP23018* pex):
    _pex(pex), _mode(LOW)
{
}

// Call after pex has begin
void LcdMCP23018::begin(void)
{
    _pex->SetPortA(0);
    _pex->SetPortB(0);
    _pex->SetPullups(0,DB_mask|Enable_mask|RS_mask);
}

void LcdMCP23018::setMode(uint8_t mode)
{
    _mode = mode;
}

// @param mode whether command (LOW) or data (HIGH) mode

void LcdMCP23018::write4bits(uint8_t value)
{
#ifdef DEBUG
    Serial.print("/write4bits/");
    Serial.print(value,HEX);
    Serial.print("/");
    Serial.println(_mode,HEX);
#endif

    // command mode
    if (_mode == LOW)
    {
        _pex->SetPortB( ( (value << DB_shift) & DB_mask) );
        delayMicroseconds(1);
        _pex->SetPortB( ( ( (value << DB_shift) & DB_mask) | Enable_mask ) );
        delayMicroseconds(1);
        _pex->SetPortB( ( (value << DB_shift) & DB_mask) );
        delayMicroseconds(100);
    }

    // data mode
    else
    {
        _pex->SetPortB( ( ( (value << DB_shift) & DB_mask) | RS_mask )   );
        delayMicroseconds(1);
        _pex->SetPortB( ( ( (value << DB_shift) & DB_mask) | RS_mask | Enable_mask )   );
        delayMicroseconds(1);
        _pex->SetPortB( ( ( (value << DB_shift) & DB_mask) | RS_mask )   );
        delayMicroseconds(100);
    }
}

void LcdMCP23018::write8bits(uint8_t value)
{
    // Not really supported, but we can go ahead and wing it!
    write4bits(value>>4);
    write4bits(value);
}


// vim:ai:cin:sts=4 sw=4 ft=cpp
