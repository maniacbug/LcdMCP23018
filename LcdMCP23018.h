#include <LiquidCrystal2.h>

class MCP23018;

/**
 * Low-level driver for LCD using an MCP23018 I/O expander
 *
 * Use this as the hardware interface for a LiquidCrystal2 instance
 * which will drive the LCD over the MCP23018.
 *
 * Except for begin(), the rest of the public methods are only called by 
 * LiquidCrystal2, not directly by the user.
 */

class LcdMCP23018:
    public ILcdHardware
{
public:
    /**
     * Constructor
     *
     * @param pex Pointer to the instantiated port expander driving class
     */
    LcdMCP23018(MCP23018* pex);
    
    /**
     * Begin operation
     *
     * Call after begin() on the port expander, before beginning the
     * LiquidCrystal2 instance.
     */
    void begin(void);

    /**
     * Sets the interface mode.
     *
     * Controls whether subsequent calls to write4bits or write8bits are
     * commands to control operation of the unit or data to be displayed.
     * 
     * @param mode LOW for command mode, HIGH for data mode
     */
    virtual void setMode(uint8_t mode);

    /**
     * Writes 4 bits to the unit
     *
     * @param data d0-d3 contain the 4 bits to be sent
     */
    virtual void write4bits(uint8_t data);
    
    /**
     * Writes 8 bits to the unit
     *
     * Note that this interface ONLY supports '4 bit' mode.  Writing 8
     * bits will result in 2 calls to write4bits().
     *
     * @param data The 8 bits to be sent 
     */
    virtual void write8bits(uint8_t data);

    /**
     * Test whether the unit is operating in 4-bit mode
     *
     * We are always in 4-bit mode in the current implementation.  This
     * method is required by the interface, so we provide it.
     *
     * @return true if we're in 4 bit mode.
     */
    virtual int fourbitmode()
    {
        return true;
    }
private:
    MCP23018* _pex;  /**< Driver instance for the underlying I/O expander */
    int _mode;  /**< Current mode the device is operating in, LOW=command, HIGH=data */
};

/**
 * @example lcdprint.pde
 *
 * Simple example to print text to an LCD controlled by
 * MCP23018 i/o extender.
 */

/**
 * @mainpage Low-level driver for LCD using an MCP23018 I/O expander
 *
 * Use this as the hardware interface for a LiquidCrystal2 instance
 * which will drive the LCD over the MCP23018.
 *
 * Dependencies:
 *
 * @li LiquidCrystal2 library
 * @li MCP23018 library
 *
 * Please refer to:
 *
 * @li <a href="http://maniacbug.github.com/LcdMCP23018/">Documentation Main Page</a>
 * @li <a href="http://maniacbug.github.com/LcdMCP23018/classLcdMCP23018.html">Lcd23018 Class Documentation</a>
 * @li <a href="https://github.com/maniacbug/LcdMCP23018/">Source Code</a>
 * @li <a href="https://github.com/maniacbug/LcdMCP23018/archives/master">Downloads Page</a>
 */

// vim:ai:cin:sts=4 sw=4 ft=cpp
