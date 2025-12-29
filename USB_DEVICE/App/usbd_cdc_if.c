/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_cdc_if.c
  * @version        : v1.0_Cube
  * @brief          : Usb device for Virtual Com Port.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* USER CODE BEGIN INCLUDE */
/* USER CODE END INCLUDE */

/** @defgroup USBD_CDC_IF_Private_Variables
  * @{
  */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */
/* Default Line Coding: 115200bps, 1 stop bit, no parity, 8bit */
USBD_CDC_LineCodingTypeDef LineCoding = {
  115200,
  0x00,
  0x00,
  0x08
};
/* USER CODE END PRIVATE_VARIABLES */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
extern void USB_RXCallback(uint8_t* Buf, uint32_t* Len);
/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t* pbuf, uint32_t *Len);
static int8_t CDC_TransmitCplt_FS(uint8_t *pbuf, uint32_t *Len, uint8_t epnum);

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS = {
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS,
  CDC_TransmitCplt_FS
};

/* Private functions ---------------------------------------------------------*/

static int8_t CDC_Init_FS(void) {
  /* USER CODE BEGIN 3 */
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);
  return (USBD_OK);
  /* USER CODE END 3 */
}

static int8_t CDC_DeInit_FS(void) {
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  Manage the CDC class requests (Line Coding)
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length) {
  /* USER CODE BEGIN 5 */
  switch(cmd) {
    case CDC_SET_LINE_CODING:
      LineCoding.bitrate    = (uint32_t)(pbuf[0] | (pbuf[1] << 8) | (pbuf[2] << 16) | (pbuf[3] << 24));
      LineCoding.format     = pbuf[4];
      LineCoding.paritytype = pbuf[5];
      LineCoding.datatype   = pbuf[6];
      break;

    case CDC_GET_LINE_CODING:
      pbuf[0] = (uint8_t)(LineCoding.bitrate);
      pbuf[1] = (uint8_t)(LineCoding.bitrate >> 8);
      pbuf[2] = (uint8_t)(LineCoding.bitrate >> 16);
      pbuf[3] = (uint8_t)(LineCoding.bitrate >> 24);
      pbuf[4] = LineCoding.format;
      pbuf[5] = LineCoding.paritytype;
      pbuf[6] = LineCoding.datatype;
      break;

    default:
      break;
  }
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  LOW LATENCY RECEIVE LOGIC
  */
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len) {
  /* USER CODE BEGIN 6 */

  /* 1. Tell the USB hardware to prepare for the NEXT packet immediately.
     This ensures that if the PC sends data while the MCU is still processing
     the current motor command, the hardware doesn't send a NAK (busy) signal. */
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
  USBD_CDC_ReceivePacket(&hUsbDeviceFS);

  /* 2. Process current data.
     Your main.c logic should simply copy this data and set a flag. */
  USB_RXCallback(Buf, Len);

  return (USBD_OK);
  /* USER CODE END 6 */
}

/**
  * @brief  Transmit data over USB
  */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len) {
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 7 */
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
  if (hcdc->TxState != 0) {
    return USBD_BUSY;
  }
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
  result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);
  /* USER CODE END 7 */
  return result;
}

static int8_t CDC_TransmitCplt_FS(uint8_t *Buf, uint32_t *Len, uint8_t epnum) {
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 13 */
  UNUSED(Buf);
  UNUSED(Len);
  UNUSED(epnum);
  /* USER CODE END 13 */
  return result;
}
