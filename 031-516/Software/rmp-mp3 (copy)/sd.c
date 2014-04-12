#include "hw.h"
#include "sd.h"

uint8_t sdok;
static uint8_t sd_channel;
enum {
	SD_TYPE_MMC = 0,
	SD_TYPE_SPEC1,
	SD_TYPE_SPEC2,
	SD_TYPE_SDHC,
};

int sd_type = SD_TYPE_SPEC2;

/*
 * SD card
 */

void sd_set_channel(uint8 channel)
{
  sd_channel = channel;
/*
 if(sd_channel == 1){
    ClearBit(SD_POWER_PORT,SD_POWER);
    SetBit(SD_POWER_PORT,SD2_POWER);
  }else{
    ClearBit(SD_POWER_PORT,SD2_POWER);
    SetBit(SD_POWER_PORT,SD_POWER);
  }
  */
}

int sd_init() {
  uint8_t i;
  int k;
  uint8_t r;
  uint8_t mmc = 0;

  uint8_t errorcode;
  errorcode = 0;

  sdok = 0;
  if(sd_channel == 1)
    sd_deselect(1);
  else
    sd_deselect(0);

  /* 74 cycles to start up the card */
  for (i = 0; i < 10; i++) {
    sd_recv();
  }

  if(sd_channel==1)
    sd_select(1);
  else
    sd_select(0);

  /* enter idle mode */
  for (k = 0; ; k++) {
    r = sd_cmd(CMD_GO_IDLE_STATE, 0);
    if (r == (1 << R1_IDLE_STATE)) {
			uart_puts("sd: entered IDLE state\r\n");
      break;
    }
    if (k == 0x1ff) {
      uart_puts("sd: failed to enter IDLE state\r\n");
      errorcode = 1;
      break;
    }
  }

  /* check SD card specification version */
	char sdhc = 0;
  r = sd_cmd(CMD_SEND_IF_COND, 0x100 | 0xaa); /* 2.7V..3.6V */
  if ((r & (1 << R1_ILL_COMMAND)) == 0) {
    uart_puts("sd: SD SPEC 2 (or SDHC)\r\n");
		//sd_type = SD_TYPE_SPEC2;
		sd_type = SD_TYPE_SPEC2;
		sdhc = 1;
		sd_recv();
		sd_recv();
		r = sd_recv();
		if (r & 1 == 0) {
			uart_puts("sd: voltage range mismatch\r\n");
		}
		r = sd_recv();
		if (r != 0xaa) {
			uart_puts("sd: wrong test pattern\r\n");
		}
  } else {
    sd_cmd(CMD_APP, 0);
    r = sd_cmd(CMD_SD_SEND_OP_COND, 0);
    if ((r & (1 << R1_ILL_COMMAND)) == 0) {
      uart_puts("sd: SD SPEC 1\r\n");
			sdhc = 0;
			sd_type = SD_TYPE_SPEC1;
    } else {
      uart_puts("sd: MMC\r\n");
      mmc = 1;
			sd_type = SD_TYPE_MMC;
    }
  }

	uart_puts("sd: wait for card to get ready\r\n");

  /* wait for the card to get ready */
  for (k = 0; ; k++) {
    if (sd_type == SD_TYPE_SPEC1 || sd_type == SD_TYPE_SPEC2) { // if not mmc
      uint32_t arg = 0;
      if (sd_type == SD_TYPE_SPEC2) {
        arg = 0x40000000;
      }
      sd_cmd(CMD_APP, 0);
      r = sd_cmd(CMD_SD_SEND_OP_COND, arg);
    } else {
      r = sd_cmd(CMD_SEND_OP_COND, 0);
    }

    if ((r & (1 << R1_IDLE_STATE)) == 0) {
			uart_puts("sd: entered IDLE state (ready)\r\n");
      break;
    }
    if (k == 0x7fff) {
      uart_puts("sd: card didn't enter IDLE state (not ready)\r\n");
      errorcode = 1;
			break;
    }
  }

  if (sd_type == SD_TYPE_SPEC2) {
    r = sd_cmd(CMD_READ_OCR, 0);
    if (r) {
			uart_puts("sd: OCR command failed\r\n");
			errorcode = 1;
    } else {
			if (sd_recv() & 0x40) {
				uart_puts("sd: card mode - SDHC\r\n");
				sd_type = SD_TYPE_SDHC;
			}
			sd_recv();
			sd_recv();
			sd_recv();
		}
  }

  if (sd_cmd(CMD_SET_BLOCKLEN, 512) != 0) {
    uart_puts("sd: failed to set block length to 512 bytes\r\n");
    errorcode = 1;
  }

	uart_puts("sd: done\r\n");

	if(sd_channel == 1)
	  sd_deselect(1);
	else
	  sd_deselect(0);
  sdok = 1;
  return errorcode;
}

uint8_t sd_cmd(uint8_t cmd, uint32_t arg) {
  uint8_t i;
  uint8_t r;


  sd_recv(); // skip some bytes

  sd_send(0x40 | cmd);
  sd_send((arg >> 24) & 0xff);
  sd_send((arg >> 16) & 0xff);
  sd_send((arg >> 8) & 0xff);
  sd_send(arg & 0xff);

  switch (cmd) {
    case CMD_GO_IDLE_STATE:
      sd_send(0x95);
      break;
    case CMD_SEND_IF_COND:
      sd_send(0x87);
      break;
    default:
      sd_send(0xff);
  }

  for (i = 0; i < 10; i++) {
    if ((r = sd_recv()) != 0xff)
      break;
  }

  return r;
}

uint8_t sd_read_block(uint32_t block_offset, uint8_t block[512]) {
  int r;
  uint16_t i;

  if(sd_channel==1)
    sd_select(1);
  else
    sd_select(0);

	if (sd_type == SD_TYPE_SDHC) {
		r = sd_cmd(CMD_READ_SINGLE_BLOCK, block_offset);
	} else {
		r = sd_cmd(CMD_READ_SINGLE_BLOCK, block_offset << 9);
	}

  if (r != 0) {
    uart_puts("CMD_READ_SINGLE_BLOCK command failed for offset");
    uart_puthex32(block_offset);
    uart_puts("\r\n");
    if(sd_channel == 1)
      sd_deselect(1);
    else
      sd_deselect(0);
    sdok = 0;
    return r;
  }

  while (sd_recv() != 0xfe); // TODO: use timeout?

	//UART_TxStr("Block:\r\n");
  for (i = 0; i < 512; i++) {
    uint8_t c = sd_recv();
    block[i] = c;
		//UART_TxUint8(c);
  }
	//UART_TxStr("\r\n");

  sd_recv(); sd_recv(); // skip CRC

  if(sd_channel == 1)
    sd_deselect(1);
  else
    sd_deselect(0);

  sd_recv();

  return 0;
}