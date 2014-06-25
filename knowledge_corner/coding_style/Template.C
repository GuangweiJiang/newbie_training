//==========================================
// Filename:
//      FlashRW.cpp
//
// Copyright (C) 2006 Wistron
// All rights reserved.
//
// Description:
//      This file will Read/Write data from/to Flash.
//
// Author/Created Date:
//      Guangwei Jiang, Jan12'06
//
// Modification History:
// 
//
//
// Note:
//    
//==========================================
//
// 
//


//--------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------





//-----------------------------------------------------------------
// MACROS
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------
	



//-----------------------------------------------------------------
// CONSTANTS AND VARIABLES
//-----------------------------------------------------------------



//-----------------------------------------------------------------
// INTERNAL FUNCTIONS
//-----------------------------------------------------------------



//-----------------------------------------------------------------
// EXTERNAL FUNCTIONS
//-----------------------------------------------------------------



//-----------------------------------------------------------------
// IMPLEMENTATION
//-----------------------------------------------------------------




//----------------------------------------------------------------------------
// Function:
//      OpenOneDevice (
//			IN		HDEVINFO                    HardwareDeviceInfo,
//			IN		PSP_DEVICE_INTERFACE_DATA   DeviceInfoData,
//			IN		char						*devName
//			)
//
// Description:
//		Given the HardwareDeviceInfo, representing a handle to the plug and
//		play information, and deviceInfoData, representing a specific usb device,
//		open that device and fill in all the relevant information in the given
//		USB_DEVICE_DESCRIPTOR structure.
//
// Parameters:
//      HardwareDeviceInfo:  handle to info obtained from Pnp mgr via SetupDiGetClassDevs()
//		DeviceInfoData:      ptr to info obtained via SetupDiEnumDeviceInterfaces()
//
// Return Value:
//      return HANDLE if the open and initialization was successfull,
//      else INVLAID_HANDLE_VALUE.
//
