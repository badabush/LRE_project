/*
 * lre_usb.c
 *
 *  Created on: 06.12.2017
 *      Author: marc
 */

#include "lre_usb.h"

void lre_usbInitiate(void) {
	/* The Application layer has only to call USBD_Init to
	 initialize the USB low level driver, the USB device library, the USB clock
	 ,pins and interrupt service routine (BSP) to start the Library*/
	USBD_Init(&USB_Device_dev, &USR_desc, &USBD_CDC_cb, &USR_cb);
}

void lre_usbSendString(char* string, uint32_t length) {
//	uint32_t len;
//	len = sprintf((char*) usb_send_buffer, "1337\r\n");
	TEMPLATE_fops.pIf_DataTx((uint8_t*) string, length);

}

void lre_usbReceivedString(char* Buf, uint32_t Len) {
	// This function is called, when the microcontroller receives something over the USB virtual COM port interface
	// add your code here

}

// USB interrupt handler
void USB_IRQHandler(void) {
	USB_Istr();
}
