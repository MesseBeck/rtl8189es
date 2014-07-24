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
#ifndef __XMIT_OSDEP_H_
#define __XMIT_OSDEP_H_

#include <drv_conf.h>
#include <osdep_service.h>
#include <drv_types.h>

struct pkt_file {
	_pkt *pkt;
	SIZE_T pkt_len;	 //the remainder length of the open_file
	_buffer *cur_buffer;
	u8 *buf_start;
	u8 *cur_addr;
	SIZE_T buf_len;
};

#define NR_XMITFRAME	256

struct xmit_priv;
struct pkt_attrib;
struct sta_xmit_priv;
struct xmit_frame;
struct xmit_buf;

extern int _rtw_xmit_entry(_pkt *pkt, _nic_hdl pnetdev);
extern int rtw_xmit_entry(_pkt *pkt, _nic_hdl pnetdev);

void rtw_os_xmit_schedule(_adapter *padapter);

int rtw_os_xmit_resource_alloc(_adapter *padapter, struct xmit_buf *pxmitbuf,u32 alloc_sz);
void rtw_os_xmit_resource_free(_adapter *padapter, struct xmit_buf *pxmitbuf,u32 free_sz);

extern void rtw_set_tx_chksum_offload(_pkt *pkt, struct pkt_attrib *pattrib);

extern uint rtw_remainder_len(struct pkt_file *pfile);
extern void _rtw_open_pktfile(_pkt *pkt, struct pkt_file *pfile);
extern uint _rtw_pktfile_read (struct pkt_file *pfile, u8 *rmem, uint rlen);
extern sint rtw_endofpktfile (struct pkt_file *pfile);

extern void rtw_os_pkt_complete(_adapter *padapter, _pkt *pkt);
extern void rtw_os_xmit_complete(_adapter *padapter, struct xmit_frame *pxframe);

#endif //__XMIT_OSDEP_H_
