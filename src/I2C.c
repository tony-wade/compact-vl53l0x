#include <SI_C8051F380_Register_Enums.h>
#include "I2C.h"

typedef enum
{
    // Master States (最高位元組的 top 4 bits)
    I2C_STATE_MASTER_START = 0xE0,   // (主機) 傳送開始條件
    I2C_STATE_MASTER_TX_DATA = 0xC0, // (主機) 傳送位元組
    I2C_STATE_MASTER_RX_DATA = 0x80, // (主機) 接收位元組

    // Slave States (最高位元組的 top 4 bits)
    I2C_STATE_SLAVE_ADDR_RECEIVED = 0x20, // (從機) 接收位址
    I2C_STATE_SLAVE_RX_DATA = 0x00,       // (從機) 接收資料位元組
    I2C_STATE_SLAVE_TX_DATA = 0x40,       // (從機) 傳送資料位元組
    I2C_STATE_SLAVE_STOP = 0x10,          // (從機) 偵測到停止條件
    I2C_STATE_BUS_ERROR = 0x50,           // (從機/主機) 總線錯誤
} I2C_State_t;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static volatile uint8_t xdata tx_buffer[MAX_BUFFER_SIZE]; // use ISR to W/R
static volatile uint8_t xdata rx_buffer[MAX_BUFFER_SIZE];
static volatile uint8_t tx_len = 0, tx_index = 0;
static volatile uint8_t rx_len = 0, rx_index = 0;

static volatile uint8_t i2c_rw;
static volatile uint8_t target_addr;

volatile uint8_t i2c_busy = 0;
volatile uint8_t NUM_ERRORS = 0;

//-----------------------------------------------------------------------------
// I2C Core function
//-----------------------------------------------------------------------------
/* "data" as variable is forbidden!!*/
void I2C_WriteBytes(uint8_t address, const uint8_t *bytes, uint8_t length)
{
    uint8_t i;

    while (i2c_busy != 0)
    {
    } // prevent override

    target_addr = address;
    tx_len = length;
    tx_index = 0;
    i2c_rw = I2C_WRITE;
    i2c_busy = 1;

    for (i = 0; i < length; i++)
    {
        tx_buffer[i] = bytes[i];
    }

    SMB0CN_STA = 1;
}

void I2C_ReadBytes(uint8_t address, uint8_t length)
{
    while (i2c_busy != 0)
    {
    } // prevent override

    target_addr = address;
    rx_len = length;
    rx_index = 0;
    i2c_rw = I2C_READ;
    i2c_busy = 1;

    SMB0CN_STA = 1;

    while (i2c_busy != 0)
    {
    } // prevent override
}

// device-address-wr_data
void I2C_WriteDevice(uint8_t Dev, uint8_t reg, const uint8_t *source, uint8_t length)
{
    uint8_t i;
    while (i2c_busy != 0)
    {
    } // prevent override

    target_addr = Dev;
    tx_len = length + 1;
    tx_buffer[0] = reg;

    for (i = 0; i < length; i++)
    {
        tx_buffer[i + 1] = source[i]; // load
    }

    tx_index = 0;
    i2c_rw = I2C_WRITE;
    i2c_busy = 1;

    SMB0CN_STA = 1;
}

// device-wr_address + device-rd_data
// *target is API bounded, need to send rx_buffer to target
void I2C_ReadDevice(uint8_t Dev, uint8_t reg, uint8_t *target, uint8_t length)
{
    uint8_t i;

    while (i2c_busy != 0)
    {
    } // prevent override
    I2C_WriteBytes(Dev, &reg, 1);
    I2C_ReadBytes(Dev, length);

    for (i = 0; i < rx_len; i++)
    {
        target[i] = rx_buffer[i];
    }
}

//-----------------------------------------------------------------------------
// I2C ISR, will automatically trigger after received ACK/NACK
//-----------------------------------------------------------------------------
SI_INTERRUPT(SMBUS0_ISR, SMBUS0_IRQn)
{

    if (SMB0CN_ARBLOST == 0)
    {
        switch (SMB0CN & 0xF0)
        {
        case I2C_STATE_MASTER_START:
            SMB0DAT = (target_addr << 1) | i2c_rw; // LSB is R/W bit
            SMB0CN_STA = 0;                        // clear for next START
            break;

        case I2C_STATE_MASTER_TX_DATA:
            if (SMB0CN_ACK)
            {
                if (i2c_rw == I2C_WRITE)
                { // IMPORTANT!
                    if (tx_index >= tx_len)
                    {                   // finish
                        SMB0CN_STO = 1; // Send STOP
                        i2c_busy = 0;
                    }
                    else
                    {
                        SMB0DAT = tx_buffer[tx_index++];
                    }
                }
                else
                {
                    // Wait 'til SMB0CN transit to Read
                }
            }
            else
            {                   // NACK
                SMB0CN_STO = 1; // Send STOP condition, followed
                SMB0CN_STA = 1; // By a START
                i2c_busy = 0;
                // NUM_ERRORS++;           // Indicate error
            }
            break;

        case I2C_STATE_MASTER_RX_DATA:
            rx_buffer[rx_index++] = SMB0DAT;

            if (rx_index < rx_len)
            {
                SMB0CN_ACK = 1; // ACK, next
            }
            else
            {                   // finish
                SMB0CN_ACK = 0; // 最後一個 byte，NACK
                SMB0CN_STO = 1;
                i2c_busy = 0;
            }
            break;

            // case....

        default:
            SMB0CF &= ~0x80; // Reset communication
            SMB0CF |= 0x80;
            SMB0CN_STA = 0;
            SMB0CN_STO = 0;
            SMB0CN_ACK = 0;

            i2c_busy = 0; // Free SMBus
            NUM_ERRORS++;
            break;
        }
    }

    else
    {
        SMB0CF &= ~0x80; // Reset communication
        SMB0CF |= 0x80;
        SMB0CN_STA = 0;
        SMB0CN_STO = 0;
        SMB0CN_ACK = 0;

        i2c_busy = 0; // Free SMBus
        NUM_ERRORS++;
    }

    SMB0CN_SI = 0; // MUST!
}
