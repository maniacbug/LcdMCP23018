#include <LiquidCrystal2.h>

class MCP23018;

/**
 * Low-level driver for LCD using an MCP23018 I/O expander
 */

class LcdMCP23018:
    public ILcdHardware
{
public:
    LcdMCP23018(MCP23018*);
    void begin(void);
    virtual void setMode(uint8_t);
    virtual void write4bits(uint8_t);
    virtual void write8bits(uint8_t);
    virtual int fourbitmode()
    {
        return true;
    }
private:
    MCP23018* _pex;
    int _mode;
};


// vim:ai:cin:sts=4 sw=4 ft=cpp
