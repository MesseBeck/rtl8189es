/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __USB_OPS_H_
#define __USB_OPS_H_

#include <drv_conf.h>
#include <osdep_service.h>
#include <drv_types.h>
#include <osdep_intf.h>

#define REALTEK_USB_VENQT_READ		0xC0
#define REALTEK_USB_VENQT_WRITE		0x40
#define REALTEK_USB_VENQT_CMD_REQ	0x05
#define REALTEK_USB_VENQT_CMD_IDX	0x00

enum{
	VENDOR_WRITE = 0x00,
	VENDOR_READ = 0x01,
};
#define ALIGNMENT_UNIT				16
#define MAX_VENDOR_REQ_CMD_SIZE	254		//8188cu SIE Support
#define MAX_USB_IO_CTL_SIZE		(MAX_VENDOR_REQ_CMD_SIZE +ALIGNMENT_UNIT)

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,12))
#define rtw_usb_control_msg(dev, pipe, request, requesttype, value, index, data, size, timeout_ms) \
	usb_control_msg((dev), (pipe), (request), (requesttype), (value), (index), (data), (size), (timeout_ms))
#define rtw_usb_bulk_msg(usb_dev, pipe, data, len, actual_length, timeout_ms) \
	usb_bulk_msg((usb_dev), (pipe), (data), (len), (actual_length), (timeout_ms))
#else
#define rtw_usb_control_msg(dev, pipe, request, requesttype, value, index, data, size,timeout_ms) \
	usb_control_msg((dev), (pipe), (request), (requesttype), (value), (index), (data), (size), \
		((timeout_ms) == 0) ||((timeout_ms)*HZ/1000>0)?((timeout_ms)*HZ/1000):1)
#define rtw_usb_bulk_msg(usb_dev, pipe, data, len, actual_length, timeout_ms) \
	usb_bulk_msg((usb_dev), (pipe), (data), (len), (actual_length), \
		((timeout_ms) == 0) ||((timeout_ms)*HZ/1000>0)?((timeout_ms)*HZ/1000):1)
#endif
#include <usb_ops_linux.h>

#ifdef CONFIG_RTL8192C
void rtl8192cu_set_hw_type(_adapter *padapter);
#define hal_set_hw_type rtl8192cu_set_hw_type

void rtl8192cu_set_intf_ops(struct _io_ops *pops);
#define usb_set_intf_ops	rtl8192cu_set_intf_ops

void rtl8192cu_recv_tasklet(void *priv);

void rtl8192cu_xmit_tasklet(void *priv);
#endif

#ifdef CONFIG_RTL8723A
void rtl8723au_set_hw_type(_adapter *padapter);
#define hal_set_hw_type rtl8723au_set_hw_type

void rtl8723au_set_intf_ops(struct _io_ops *pops);
#define usb_set_intf_ops rtl8723au_set_intf_ops

void rtl8192cu_recv_tasklet(void *priv);

void rtl8192cu_xmit_tasklet(void *priv);
#endif

#ifdef CONFIG_RTL8192D
void rtl8192du_set_hw_type(_adapter *padapter);
#define hal_set_hw_type rtl8192du_set_hw_type
void rtl8192du_set_intf_ops(struct _io_ops *pops);
#define usb_set_intf_ops  rtl8192du_set_intf_ops
void rtl8192du_recv_tasklet(void *priv);
void rtl8192du_xmit_tasklet(void *priv);
#endif

#ifdef CONFIG_RTL8188E
void rtl8188eu_set_hw_type(_adapter *padapter);
#define hal_set_hw_type rtl8188eu_set_hw_type
void rtl8188eu_set_intf_ops(struct _io_ops *pops);
#define usb_set_intf_ops rtl8188eu_set_intf_ops
#endif

#define USB_HIGH_SPEED_BULK_SIZE	512
#define USB_FULL_SPEED_BULK_SIZE	64

static inline u8 rtw_usb_bulk_size_boundary(_adapter * padapter,int buf_len)
{
	u8 rst = _TRUE;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);

	if (pdvobjpriv->ishighspeed)
		rst = (0 == (buf_len) % USB_HIGH_SPEED_BULK_SIZE)?_TRUE:_FALSE;
	else
		rst = (0 == (buf_len) % USB_FULL_SPEED_BULK_SIZE)?_TRUE:_FALSE;
	return rst;
}


#endif //__USB_OPS_H_

