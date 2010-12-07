/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/

/*
 * NB! This file is for COM internal use only and may only be included from COM C-files!
 */



#ifndef COM_INTERNAL_H_
#define COM_INTERNAL_H_


extern const Com_ConfigType * ComConfig;



#ifdef COM_DEV_ERROR_DETECT
#include "Det.h"

#define DET_REPORTERROR(_x,_y,_z,_q) Det_ReportError(_x,_y,_z,_q)


// Define macro for parameter check.
#define PDU_ID_CHECK(PduId,ApiId,...) \
	if (PduId >= Com_Arc_Config.ComNIPdu) { \
		DET_REPORTERROR(COM_MODULE_ID, COM_INSTANCE_ID, ApiId, COM_INVALID_PDU_ID); \
		return __VA_ARGS__; \
	} \

#define VALIDATE_SIGNAL(SignalId, ApiId, ...) \
	if (ComConfig->ComSignal[SignalId].Com_Arc_IsSignalGroup) { \
		DET_REPORTERROR(COM_MODULE_ID, COM_INSTANCE_ID, ApiId, COM_ERROR_SIGNAL_IS_SIGNALGROUP); \
		return __VA_ARGS__; \
	} \


#else

#define DET_REPORTERROR(_x,_y,_z,_q)

#define PDU_ID_CHECK(PduId,ApiId,...)
#define VALIDATE_SIGNAL(PduId, ApiId, ...)
#endif


#define TESTBIT(source,bit) (*((uint8 *)source + (bit / 8)) & (1 << (bit % 8)))
#define SETBIT(dest,bit) *((uint8 *)dest + (bit / 8)) |= (1 << (bit % 8))
#define CLEARBIT(dest,bit) *((uint8 *)dest + (bit / 8)) &= ~(1 << (bit % 8))

#define GET_Signal(SignalId) \
	const ComSignal_type * Signal = &ComConfig->ComSignal[SignalId]\

#define GET_ArcSignal(SignalId) \
	Com_Arc_Signal_type * Arc_Signal = &Com_Arc_Config.ComSignal[SignalId]\

#define GET_IPdu(IPduId) \
	const ComIPdu_type *IPdu = &ComConfig->ComIPdu[IPduId]\

#define GET_ArcIPdu(IPduId) \
	Com_Arc_IPdu_type *Arc_IPdu = &Com_Arc_Config.ComIPdu[IPduId]\

#define GET_GroupSignal(GroupSignalId) \
	const ComGroupSignal_type *GroupSignal = &ComConfig->ComGroupSignal[GroupSignalId]\

#define GET_ArcGroupSignal(GroupSignalId) \
	Com_Arc_GroupSignal_type *Arc_GroupSignal = &Com_Arc_Config.ComGroupSignal[GroupSignalId]\



#endif /* COM_INTERNAL_H_ */