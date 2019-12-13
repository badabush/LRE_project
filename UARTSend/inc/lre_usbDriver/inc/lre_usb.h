/*
 * lre_usb.h
 *
 *  Created on: 06.12.2017
 *      Author: marc
 */

#ifndef LRE_USB_H_
#define LRE_USB_H_

// check if the symbol INTERNAL_PULLUP is defined
#ifndef INTERNAL_PULLUP
#error add INTERNAL_PULLUP to preprocessor symbols!
#endif


#include "stm32f0xx.h"
#include "stm32f072b_discovery.h"
#include "usbd_cdc_if_template.h"
#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include <stdlib.h>
#include <stdio.h>

USB_CORE_HANDLE USB_Device_dev;

uint8_t usb_send_buffer[30];

void lre_usbInitiate(void);
void lre_usbSendString(char* string, uint32_t length);
void lre_usbReceivedString(char* Buf, uint32_t Len);


#endif /* LRE_USB_H_ */
