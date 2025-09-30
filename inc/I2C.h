#ifndef I2C_H_
#define I2C_H_

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern volatile uint8_t i2c_busy;   // global state


//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define MAX_BUFFER_SIZE  4



//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------
typedef enum {
    I2C_WRITE = 0,
    I2C_READ  = 1
} I2C_Direction;



//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------
void I2C_WriteBytes(uint8_t address, const uint8_t* bytes, uint8_t length);
void I2C_ReadBytes(uint8_t address, uint8_t length);
void I2C_WriteDevice(uint8_t Dev, uint8_t reg, const uint8_t *source, uint8_t length);
void I2C_ReadDevice(uint8_t Dev, uint8_t reg, uint8_t *target, uint8_t length);


#endif /* I2C_H_ */
