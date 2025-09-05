#ifndef UMERROR_H
#define UMERROR_H

#include "master.h"
#include "umtype.h"


//=== [mask] Global Flags (diagnostic board) ===================================
 extern uint32_t    gf_mask;     // Diagnostic Board
 extern uint32_t    gf_mask_shm; // Diagnostic Board (save for web)

#define GF_EAPPL  0x00000001L  // 1. runtime application error
#define GF_RSTRT  0x00000002L  // 2. restart detected
#define GF_DEBUG  0x00000004L  // 3. debug mode
#define GF_POWER  0x00000008L  // 4. power is low
#define GF_TERMO  0x00000010L  // 5. temperature out of range
#define GF_MHARD  0x00000020L  // 6. module hardware error                    (detected from TP_ESTATE->ehard)
#define GF_MCONF  0x00000040L  // 7. module configuration (application) error (detected from TP_ESTATE)
#define GF_CHARD  0x00000080L  // 8. channel hardware error                   (detected from TP_ESTATE->eunit)
#define GF_CCONF  0x00000100L  // 9. channel configuration error              (detected from TP_ESTATE->econst)
#define GF_CLINE  0x00000200L  //10. channel external line error              (detected from TP_ESTATE->eline)
#define GF_STBUS  0x00000400L  //11. ST-BUS error (detected in module)        (detected from TP_ESTATE)
#define GF_ELINK  0x00000800L  //12. external communication error             unused
#define GF_ILINK  0x00001000L  //13. intercontroller communication error      unused
#define GF_HOTSBY 0x00002000L  //14. Hot Standby error
#define GF_MODE1  0x00004000L  //15. DIP MODE 1 (switch)
#define GF_MODE2  0x00008000L  //16. DIP MODE 2 (switch)
#define GF_MODE3  0x00010000L  //17. DIP MODE 3 (switch)
#define GF_MODE4  0x00020000L  //18. DIP MODE 4 (switch)
#define GF_MODE5  0x00040000L  //19. DIP MODE 5 (switch)
#define GF_MODE6  0x00080000L  //20. DIP MODE 6 (switch)
#define GF_SWRUN  0x00100000L  //21. RUN-STOP   (switch)
#define GF_STATE  0x00200000L  //22. Hot Standby status (Primary-Backup)
#define GF_LIBAT  0x00400000L  //23. Lithium Battery is low
#define GF_FATAL  0x00800000L  //24. master hard/soft error
#define GF_MLINK  0x01000000L  //25. module is not answered
#define GF_DOUT1  0x02000000L  //26. Digital Output 1
#define GF_DOUT2  0x04000000L  //27. Digital Output 2
#define GF_DOUT3  0x08000000L  //28. Digital Output 3
#define GF_DINP1  0x10000000L  //29. Digital Input 1
#define GF_DINP2  0x20000000L  //30. Digital Input 2
#define GF_DINP3  0x40000000L  //31. Digital Input 3
#define GF_DINP4  0x80000000L  //32. Digital Input 4

//=== [mask] Global Error Flags ================================================
 extern uint32_t    ge_mask;      //global error flags
 extern uint32_t    ge_mask_prev; //global error flags previous

#define GE_MOD    0x001  //module error
#define GE_CHAN   0x002  //channel error
#define GE_HARD   0x004  //master error
#define GE_SBY    0x008  //hot standby error
#define GE_CONF   0x010  //configuration error
#define GE_COM    0x020  //serial port error
#define GE_ETH    0x040  //ethernet error
#define GE_BUS    0x080  //st-bus error
#define GE_RTN    0x100  //retain error

// M947F,M947R,M957O,M957D,M947D

#define GE_L1     0x020  //line 1 error
#define GE_L2     0x040  //line 2 error
#define GE_TO     0x080  //master link' timeout

//=== UNIMOD 2 [mask] Global Error Flags =======================================
#define U2_GE_MOD       0x0001  //module error
#define U2_GE_BUS_WARN  0x0002  //st-bus error
#define U2_GE_CHAN      0x0004  //channel error
#define U2_GE_SBY       0x0008  //hot standby error
#define U2_GE_SBY_WARN  0x0010  //hot standby warning
#define U2_GE_MKO       0x0020  //MKO error
#define U2_GE_MKO_WARN  0x0040  //MKO warning
#define U2_GE_ENV       0x0080  //environment error (power, temperature)
#define U2_GE_RTN       0x0100  //retain error
#define U2_GE_HARD      0x0200  //hard error
#define U2_GE_RE        0x0400  //application runtime errors

//=== [mask] Global Warning Flags ==============================================
 extern uint32_t    gw_mask; //global warning flags

#define GW_SBY    0x001  //hot standby warning
#define GW_BUS    0x002  //st-bus warning

//=== [mask] Runtime Error =====================================================
 extern uint32_t    re_mask;

#define RE_IDNUL  0x0001  //division by zero (integer)
#define RE_FICNV  0x0002  //overflow during conversion
#define RE_FDNUL  0x0004  //division by zero (floating point)
#define RE_FESTR  0x0008  //fault structure (floating point)
#define RE_FPOVF  0x0010  //positive overflow (floating point)
#define RE_FNOVF  0x0020  //negative overflow (floating point)
#define RE_DOMM   0x0040  //not used
#define RE_ARROVF 0x0080  //exceeding of array' range
#define RE_TYPE   0x0100  //type mismatch
#define RE_PNT    0x0200  //incorrect action with pointer
#define RE_F_NAN  0x0400  //NaN is prevented
#define RE_ARG    0x0800  //Incorrect argument (from user)
#define RE_C_ARG  0x1000  //Incorrect argument (from compiler or target system)

//=== [code] Restart Code ======================================================
 extern uint32_t    rc_code;

#define RC_EMPTY         0x00  //normal work mode
#define RC_POWER         0x01  //normal power turn on
#define RC_STOP          0x02  //stoped by STOP switch
#define RC_DEBUG         0x03  //stoped by debug request
#define RC_AE            0x05  //stoped by application error
#define RC_FW_ERR        0x06  //firmware update error
#define RC_FW_OK         0x07  //firmware update ok
#define RC_FW_BRN        0x08  //apply firmware
#define RC_RSTRT         0x09  //restart
#define RC_APPL          0x0A  //new application
#define RC_PDOWN         0x10  //power down
#define RC_WDT           0x11  //watchdog
#define RC_STM           0x12  //lost link with STM
#define RC_STM_INIT      0x13  //incorrect init procedure with STM
#define RC_ROM           0x14  //error in ROM test
#define RC_APPLY_GET     0x15  //apply changes (get request)
#define RC_APPLY_TEST    0x16  //apply changes (test run)
#define RC_UPD           0x17  //need to reboot
#define RC_INIT          0x18  //init error
#define RC_ETH_UPD       0x19  //need to reboot for update network settings
#define RC_RES_DEFAULTS  0x1A  //was reset by DIP2=DIP4=DIP6=ON to defaults
#define RC_SPI_CLR       0x1B  //can't clear SPI flash sector
#define RC_STM_RESET     0x1C  //reset from STM
#define RC_TERMO         0x1D  //temperature is high
#define RC_FW_UPD        0x1E  //start updating firmware
#define RC_STM_UNSTBL    0x1F  //unstable connection with STM
// #define RC_UPD_OS_OK     0xXX  //OS update ok (заготовка на будущее)
// #define RC_ROM_INIT      0xXX  //incorrect ROM init (for AE_ROM_INIT)
#define RC_PROG          0x20  //
#define RC_BLK_ON        0x21  //variable locking is enabled
#define RC_BLK_OFF       0x22  //variable locking is disabled
#define RC_FAULT_CNT     0x23  //more than 5 application reboots

//=== [code] Application Error (critical) ======================================
 extern uint32_t    ae_code; //fatal application error


#if defined(UNIMOD_CUT)
#define AE_NOERR           0x00  //no errors
#define AE_CONF            0x01  //configuration error
#define AE_NOMEM           0x02  //not enough memory
#define AE_NOMOD           0x03  //unknown module (device)
#define AE_STBUS           0x04  //STBUS configuration error
#define AE_MOD             0x05  //Incorrect module definition
#define AE_BMOD            0x06  //Module binary definition not found
#define AE_UART_INIT       0x07  //UART init error
#define AE_STM_INIT        0x08  //STM  init error
#define AE_SERIAL_START    0x09  //Serial driver start error
#define AE_UCOM_START      0x0A  //Serial driver start error
#define AE_UNITS_GET       0x0B  //Unit get state error
#define AE_UNIT_STA        0x0C  //Unit state error
#define AE_UNIT_UNKNOWN    0x0D  //Unit types & settings mismatch
#define AE_SEM             0x0E  //Semaphore error

#define AE_EXT_CONF_WDT             0x01  //Watchdog configuration error
#define AE_EXT_CONF_STBUS_MODE      0x02  //STBUS mode error
#define AE_EXT_CONF_STBUS_BAUD      0x03  //STBUS baud error
#define AE_EXT_CONF_USTB_NOTFOUND   0x04  //Using of USTB in project, but USTB not found
#define AE_EXT_CONF_SERIAL_MODE     0x05  //Incorrect serial mode
#define AE_EXT_CONF_TRANSIT_SIZE    0x06  //Incorrect memory size for module transit requests
#define AE_EXT_CONF_MOD_ADDR        0x07  //Module address error

// todo: not in old api
#define AE_TNET    0x1E  //TREINET init error
#define AE_RTN     0x20  //RTN init error
#define AE_SYSLOG  0x30  //Syslog error
#define AE_EXT_CONF_NET_UPDATE      0x10  //Need reboot to update network settings
#define AE_EXT_CONF_STBUS_ID        0x23  //STBUS ID error
#define AE_EXT_CONF_STBUS_PROTO     0x0F  //STBUS protocol error
#define AE_EXT_CONF_MOD_NUM         0x1E  //Incorrect module number

#else // defined(UNIMOD_CUT)

#define AE_NOERR   0x00  //no errors
#define AE_V_STK   0x01  //variable stack overflow
#define AE_NOTMC   0x02  //unknown TMC
#define AE_CONF    0x03  //configuration error
#define AE_CHSUM   0x04  //check sum error
#define AE_WRITE   0x05  //application write error
#define AE_WDT     0x06  //application is stoped by internal watchdog
#define AE_APPL    0x07  //application structure error
#define AE_NOFUN   0x08  //unknown function
#define AE_NOFBL   0x09  //unknown function block
#define AE_NOMEM   0x0A  //not enough memory
#define AE_NOVER   0x0B  //unknown TIC version
#define AE_NOMOD   0x0C  //unknown module (device)
#define AE_O_STK   0x0D  //offset (FB copy) stack overflow
#define AE_D_STK   0x0E  //data (FB data) stack overflow
#define AE_C_STK   0x0F  //code (FB code) stack overflow
#define AE_N_STK   0x10  //(FB number) stack overflow
#define AE_OVF_MSG 0x17  //too many strings
#define AE_NOST    0x1C  //unknown structure
#define AE_ST_STK  0x1D  //structure stack overflow
#define AE_TNET    0x1E  //TREINET init error
#define AE_HDA     0x1F  //HDA init error
#define AE_RTN     0x20  //RTN init error
#define AE_STBUS   0x21  //STBUS configuration error
#define AE_MODBUS  0x22  //MODBUS configuration error
#define AE_STRUCT  0x23  //Old structures are not supported
#define AE_PARAM   0x24  //Incorrect master parameters
#define AE_UPD     0x25  //Need to reboot for update target system
#define AE_SEM     0x26  //Semaphore error
#define AE_MOD     0x27  //Incorrect module definition
#define AE_IP      0x28  //Need to reboot for update network settings
#define AE_TASKS   0x29  //Incorrect tasks definition
#define AE_DIFF    0x2A  //Diff.cfg structure error
//#define AE_ROM_INIT 0x2B  //Incorrect ROM init
//#define AE_DSTRUCT  0x2C  //Dynamic structures are not supported
#define AE_SHM     0x2D  //can't init shared memory
#define AE_NOVAR   0x2E  //empty base is not allowed for M401E
#define AE_ARB     0x2F  //arbiter init error
#define AE_SYSLOG  0x30  //Syslog error
#define AE_IPTABLES  0x31  //Firewall(iptables) init. error
#define AE_BACNET  0x32  //BACNET configuration error
#define AE_FAULT_CNT  0x33  //More than 5 application reboots
#define AE_UART_INIT  0x34  //UART init error
#define AE_STM_INIT   0x35  //STM  init error

#define AE_EXT_CONF_WDT             0x01  //Watchdog configuration error
#define AE_EXT_CONF_SEM             0x02  //Semaphore error
#define AE_EXT_CONF_VER             0x03  //Unknown version
#define AE_EXT_CONF_HDR             0x04  //Header struct error
#define AE_EXT_CONF_CRC             0x05  //Checksum error
#define AE_EXT_CONF_STANDBY_MODE    0x06  //Standby mode error
#define AE_EXT_CONF_STANDBY_OPT     0x07  //Standby mode error
#define AE_EXT_CONF_STANDBY_SYNC    0x08  //Standby sync mode error
#define AE_EXT_CONF_STANDBY_FMODE   0x09  //Standby file sync mode error
#define AE_EXT_CONF_STANDBY_FINIT   0x0A  //Standby file init error
#define AE_EXT_CONF_NRG_SAVE        0x0B  //Mod energy save mode error
#define AE_EXT_CONF_LOG_INIT        0x0C  //System log init error
#define AE_EXT_CONF_STBUS_MODE      0x0D  //STBUS mode error
#define AE_EXT_CONF_STBUS_BAUD      0x0E  //STBUS baud error
#define AE_EXT_CONF_STBUS_PROTO     0x0F  //STBUS protocol error
#define AE_EXT_CONF_NET_UPDATE      0x10  //Need reboot to update network settings
#define AE_EXT_CONF_NETCFG_SAVE     0x11  //Netcfg save error
#define AE_EXT_CONF_NETCFG_IP       0x12  //IP is incorrect
#define AE_EXT_CONF_NETCFG_IFNUM    0x13  //Incorrect interface number
#define AE_EXT_CONF_NETCFG_NETMASK  0x14  //Incorrect Netmask
#define AE_EXT_CONF_NETCFG_SUBNET   0x15  //Two IP from same subnet
#define AE_EXT_CONF_UDP_RESTART     0x16  //Error while restart um_eth
#define AE_EXT_CONF_TCP_RESTART     0x17  //Error while restart um_tcp
#define AE_EXT_CONF_TASK_RESTART    0x18  //Error while restart some communication task
#define AE_EXT_CONF_CYCLE_TIME      0x19  //Cycle time exceeds Watchdog
#define AE_EXT_CONF_USTB_NOTFOUND   0x1A  //Using of USTB in project, but USTB not found
#define AE_EXT_CONF_SERIAL_MODE     0x1B  //Incorrect serial mode
#define AE_EXT_CONF_STANDBY_DIP     0x1C  //Standby mode and DIP5 mismatch
#define AE_EXT_CONF_NETCFG_EXT      0x1D  //Ext. IP from different subnets
#define AE_EXT_CONF_MOD_NUM         0x1E  //Incorrect module number
#define AE_EXT_CONF_TCP_NOTDEFINED  0x1F  //No um_tcp tasks in project
#define AE_EXT_CONF_NETCFG_ETHMODE  0x20  //Incorrect ethernet mode
#define AE_EXT_CONF_ROUTECFG_SAVE   0x21  //route.cfg save error
#define AE_EXT_CONF_CYCLE_MODE      0x22  //Cycle mode unknown
#define AE_EXT_CONF_STBUS_ID        0x23  //STBUS ID error
#define AE_EXT_CONF_BACNET          0x24  //BACnet does't support error
#define AE_EXT_CONF_TRANSIT_SIZE    0x18  //Incorrect memory size for module transit requests // todo-api: change code to 0x24

#endif // #if else defined(UNIMOD_CUT)

#define AE_EXT_MOD_SERVICE_SIZE     0x01  //Incorrect size of service settings structure

#define AE_EXT_TNET_WDT       0x01  //Watchdog configuration error
#define AE_EXT_TNET_INIT      0x02  //init error
#define AE_EXT_TNET_RUN       0x03  //task is not running
//#define AE_EXT_TNET_IP        0x04  //not found my IP address
#define AE_EXT_TNET_NUM       0x05  //Incorrect task number
#define AE_EXT_TNET_MINI      0x06  //Settings already in master.ini
#define AE_EXT_TNET_PORT      0x07  //Port is in use
#define AE_EXT_TNET_DST_PATH  0x08  //Can't find path to dest. IP
#define AE_EXT_TNET_NODATA    0x09  //Data not linked
#define AE_EXT_TNET_DIAGSIZE  0x0A  //Diag struct size is too small
#define AE_EXT_TNET_PING_OPEN 0x0B  //Ping task open error
#define AE_EXT_TNET_NEPI      0x0C  //N_epi calc error
#define AE_EXT_TNET_SHLEN     0x0D  //Total shared memory size error
#define AE_EXT_TNET_SCL_INIT  0x0E  //SCL task init error
#define AE_EXT_TNET_NOMEM     0x0F  //not enough memory
#define AE_EXT_TNET_NEED_PRP  0x10  //Need to PRP mode
#define AE_EXT_TNET_IPTABLES  0x11  //Firewall(iptables) init. error

#define AE_EXT_ARB_TO_CALC    0x01  //arbiter calc timeouts error

// code for statistic
#define AE_EXT_DIFF_WRITE     0x01
#define AE_EXT_DIFF_APPL      0x02  //application structure error
#define AE_EXT_DIFF_NOMEM     0x03  //not enough memory
#define AE_EXT_VER            0x04  //unknown version
//#define AE_EXT_SVD_FORMAT     0x05  //

#define AE_EXT_SYSLOG_RET_MASK  0x00FFFFFF // Mask for return code
#define AE_EXT_SYSLOG_RUN       0x00000000 // Errot while run syslog daemon (extra = return code)
#define AE_EXT_SYSLOG_CONF_FILE 0x01000000 // Error while open syslog config file

#define AE_EXT_BACNET_DEFSIZE   0x01 // Incorrect size of p_main->bacnet_defsize
#define AE_EXT_BACNET_DIAGSIZE  0x02 // Incorrect size of diag_device_defsize or diag_property_defsize

//=== [mask] Retain Status =====================================================
// extern uint32_t    rtn_mask;  //retain status

//mask
#define RTN_BUF1_E_SIZE  0x001  //buf 1. size mismatch
#define RTN_BUF1_E_CRC   0x002  //buf 1. crc error
#define RTN_BUF1_E_APPL  0x004  //buf 1. another appl
#define RTN_BUF1_OK      0x008  //buf 1. retain is done
//...
#define RTN_BUF2_E_SIZE  0x080  //buf 2. size mismatch
#define RTN_BUF2_E_CRC   0x100  //buf 2. crc error
#define RTN_BUF2_E_APPL  0x200  //buf 2. another appl
#define RTN_BUF2_OK      0x400  //buf 2. retain is done

// code for statistic
#define RTN_E_VER          0x10  //application structure error
#define RTN_E_SVD_FORMAT   0x11  //application structure error
#define RTN_E_DIFF         0x12  //application structure error
#define RTN_E_COLDSTART    0x13  //cold start
#define RTN_E_FAULT_CNT    0x14  //more than 5 application reboots

//=== [code] Driver Error (critical) ===========================================
 extern unsigned  de_code; //fatal driver error

#define DE_NOERR  0x00  //no errors
#define DE_SHM    0x01  //share memory error
#define DE_SEM    0x02  //semaphore error
#define DE_MEM    0x03  //device memory error
#define DE_BREAK  0x04  //driver break
#define DE_PIC    0x05  //PIC not respond
#define DE_OVF    0x06  //pointer overflow
#define DE_MODE   0x07  //set mode error
#define DE_NTX    0x08  //number of packets mismatch
#define DE_CMD    0x09  //bad command
#define DE_STA    0x0a  //master state error
#define DE_IRQ    0x0b  //master interrupt error
#define DE_CRC    0x0c  //incorrect crc missed
#define DE_DESYNC 0x0d  //cores out of sync error
#define DE_M172S  0x0e  //cycle_MB_M172S error
#define DE_PROTO  0x0f  //protocol mismatch

#define DE_EXT_M172S_NOINIT     1
#define DE_EXT_M172S_GET_RX_TX  2
#define DE_EXT_M172S_SUB_RX     3
#define DE_EXT_M172S_OPKT_SZ    4
#define DE_EXT_M172S_IPKT_SZ    5
#define DE_EXT_M172S_IPKT_ID    6
#define DE_EXT_M172S_MCURR      7
#define DE_EXT_M172S_OPACKETS   8

//=== [mask] Synchronization Error =============================================
 extern uint32_t    se_mask;      //synchronization error
 extern uint32_t    se_mask_prev; //synchronization error previous

#define SE_MODE   0x0001  //undefined standby type
#define SE_TYPE   0x0002  //other standby type
#define SE_CRC    0x0004  //crc16 error
#define SE_LEN    0x0008  //other data length
#define SE_APP    0x0010  //other application version
#define SE_VAR    0x0020  //other variable collection
#define SE_FBL    0x0040  //other FBL collection
#define SE_FILE   0x0080  //other FILE collection
#define SE_OFILE  0x0100  //output FILE error
#define SE_IFILE  0x0200  //input FILE error
#define SE_BLOCK  0x0400  //blocked by key
#define SE_RUN    0x0800  //task is not running
#define SE_LINE   0x1000  //task return error
#define SE_IP     0x2000  //not found my IP address
#define SE_DBL    0x4000  //out of sync with master-duplicate

//=== [code] CLONE/Duplicate Synchronization Error =============================
 extern uint32_t    cse_code;      //clone/duplicate synchronization error
 extern uint32_t    cse_code_prev; //clone/duplicate synchronization error previous

#define CSE_CLONE     0x0001  //out of sync with clone
#define CSE_REM_MODE  0x0002  //out of sync with master-duplicate
#define CSE_REM_LATE  0x0003  //out of sync with master-duplicate

//=== [mask] Power Error =======================================================
 extern uint32_t    pe_mask; //power error

#if (PLATFORM == PL_QNX)
  #define PE_PWR_MASK  0x01    //power is low (summary)
  #define PE_LIBAT     0x02    //lithium battery is low
  #define PE_TERMO     0x04    //temperature out of range
  #define PE_LPWR_1    0x08    //power 1 is low
  #define PE_LPWR_2    0x10    //power 2 is low
#elif (PLATFORM == ROCKCHIP)
  #define PE_LPWR_1    0x01    //power 1 is low
  #define PE_HPWR_1    0x02    //power 1 is high
  #define PE_LPWR_2    0x04    //power 2 is low
  #define PE_HPWR_2    0x08    //power 2 is high
  #define PE_TERMO_H   0x20    //temperature is high
  ///// for pe_mask
  #define PE_PWR_MASK  0x0F    //power error mask
  ///// for STM protocol
  #define PWR_STA_MASK 0x0F    //power error mask
  #define PWR_STA_OK   0x03    //power ok
#elif (PLATFORM == PL_NUVOTON)
  #define PE_LPWR_1    0x01    //power 1 is low
  #define PE_HPWR_1    0x02    //power 1 is high
  ///// for pe_mask
  #define PE_PWR_MASK  0x03    //power error mask
#elif (PLATFORM == PL_PC_V2)
  #define PE_PWR_MASK  0x00    //not used
#endif

//=== [code] Hard Error ========================================================
// extern uint32_t    he_code; //hard error

#define HE_RTC           0x01    //Time in RTC incorrect
#define HE_MEM           0x02    //Memory leaks
#define HE_ETH_OK        0x03    //Ethernet os ok
#define HE_ETH_ERR       0x04    //Ethernet is fail
#define HE_LINK_UP       0x05    //Ethernet link is up
#define HE_LINK_DOWN     0x06    //Ethernet link is down
#define HE_PING_OK       0x07    //Ping is ok
#define HE_PING_ERR      0x08    //Ping is failed
#define HE_SFP_LINK_UP   0x09    //SFP link is up
#define HE_SFP_LINK_DOWN 0x0A    //SFP link is down
#define HE_USTB_ERR      0x0B    //USTB init is incorrect
#define HE_UNIT_PWR_ERR  0x0C    //UNIT power error

//=== [code] Configuration Error ===============================================

#define CFG_E_MODTYPE  0x01  //Module type mismatch
#define CFG_E_MODVER   0x02  //Module configuration version mismatch
#define CFG_E_MODCFG   0x03  //Module configuration mismatch
#define CFG_E_MODANS   0x04  //Incorrect answer on reading Block 0
#define CFG_E_WPARAM   0x05  //Module parameters write error
#define CFG_E_ID_ANS   0x06  //Incorrect answer on reading Block 0x0D
#define CFG_E_LOADER   0x07  //Module in loader mode
#define CFG_E_INIT     0x08  //Initialization of module
#define CFG_E_PARAM    0x09  //Parameters mismatch
#define CFG_E_COUNTER  0x0A  //Counter mismatch
#define CFG_E_REPLACE  0x0B  //I/O module has been replaced

//=== [mask] Communication Error ===============================================
 extern uint32_t    ce_mask;      //communication error
 extern uint32_t    ce_mask_prev; //communication error (previous)

#define CE_ST1OVF 0x0001L  //st-bus1 overflow
#define CE_ST1SUM 0x0002L  //st-bus1 check sum error
#define CE_ST1PKT 0x0004L  //st-bus1 packet format error
#define CE_ST1TO  0x0008L  //st-bus1 timeout
#define CE_ST2OVF 0x0010L  //st-bus2 overflow
#define CE_ST2SUM 0x0020L  //st-bus2 check sum error
#define CE_ST2PKT 0x0040L  //st-bus2 packet format error
#define CE_ST2TO  0x0080L  //st-bus2 timeout
#define CE_COMOVF 0x0100L  //serial port overflow
#define CE_COMSUM 0x0200L  //serial port check sum error
#define CE_COMPKT 0x0400L  //serial port packet format error
#define CE_COMTO  0x0800L  //serial port timeout
#define CE_ETHOVF 0x1000L  //ethernet overflow
#define CE_ETHSUM 0x2000L  //ethernet check sum error
#define CE_ETHPKT 0x4000L  //ethernet packet format error
#define CE_ETHTO  0x8000L  //ethernet timeout

//mask
#define CE_BUS_OK  0x0000L  //bus ok
#define CE_BUS_OVF 0x0001L  //bus overflow
#define CE_BUS_SUM 0x0002L  //bus check sum error
#define CE_BUS_PKT 0x0004L  //bus packet format error
#define CE_BUS_TO  0x0008L  //bus timeout

//code
#if defined(UNIMOD_CUT)
 // ������ ��� trei_services - ����� ���� ���� � ����������� ����� CFG_E_
 #define CE_MOD_INIT        8  //Initialization of module
 #define CE_MOD_PARAM       9  //Parameters mismatch
 #define CE_MOD_COUNTER    10  //Counter mismatch
 // #define CE_MOD_REPLACE    11  //I/O module has been replaced
 #define CE_MOD_RESET      11  //Detect module reset (ST-BUS(N))
 #define CE_MOD_WRK        12  //Not in work mode (ST-BUS(N))
 #define CE_MOD_ARG        13  //Incorrect arg in um_step (ST-BUS(N))

 // todo: not in old api
 #define CE_MOD_OK          5  //Module in run mode
 #define CE_MOD_ERR         8  //Exchange error (overflow, frame error)
 #define CE_LINE_OK        32  //Line ok
 #define CE_LINE_TO        36  //Line timeout
 #define CE_LINE_MOD_OK    48  //Line ok for some module
 #define CE_LINE_MOD_ERR   50  //Exchange error, without details
 #define CE_LINE_MOD_SUM   52  // #define CE_BUS_SUM 0x0002L  //bus check sum error
 #define CE_LINE_MOD_PKT   53  // #define CE_BUS_PKT 0x0004L  //bus packet format error
 #define CE_LINE_MOD_TO    54  //Line timeout for some module

#elif (LOG_VERSION == LOG_VERSION_1_0)
 #define CE_MOD_OK      0x500  //Module in run mode
 #define CE_MOD_INIT    0x501  //Initialization of module
 #define CE_MOD_ERR     0x502  //Exchange error (overflow, frame error)
 //                     0x503  //CRC error
 //                     0x504  //Incorrect packet format
 //                     0x505  //Timeout
 #define CE_MOD_PARAM   0x506  //Parameters mismatch
 #define CE_MOD_COUNTER 0x507  //Counter mismatch
 #define CE_MOD_REPLACE 0x508  //I/O module has been replaced

 #define CE_LINE_OK     0x700  //Line ok
 #define CE_LINE_TO     0x704  //Line timeout
 #define CE_LINE_MOD_OK 0x800  //Line ok for some module
 #define CE_LINE_MOD_TO 0x805  //Line timeout for some module

#else
 #define CE_MOD_OK          5  //Module in run mode
 #define CE_MOD_INIT        6  //Initialization of module
 #define CE_MOD_ERR         8  //Exchange error (overflow, frame error)
 //                         9  //CRC error
 //                        10  //Incorrect packet format
 //                        11  //Timeout
 #define CE_MOD_PARAM      12  //Parameters mismatch
 #define CE_MOD_COUNTER    13  //Counter mismatch
 #define CE_MOD_REPLACE    14  //I/O module has been replaced
 //#define CE_MOD_BLOCK_ON   15  //block poll
 //#define CE_MOD_BLOCK_OFF  16  //unblock poll

 #define CE_LINE_OK        32  //Line ok
 #define CE_LINE_TO        36  //Line timeout
 #define CE_LINE_MOD_OK    48  //Line ok for some module
 #define CE_LINE_MOD_ERR   50  //Exchange error, without details
 #define CE_LINE_MOD_OVF   51  // #define CE_BUS_OVF 0x0001L  //bus overflow
 #define CE_LINE_MOD_SUM   52  // #define CE_BUS_SUM 0x0002L  //bus check sum error
 #define CE_LINE_MOD_PKT   53  // #define CE_BUS_PKT 0x0004L  //bus packet format error
 #define CE_LINE_MOD_TO    54  //Line timeout for some module

#endif

//=== UNIMOD 1 [mask] Target System Mode =======================================
 extern uint32_t    sm_mask;  //current mode (NOAPPL, RUN)

#define SM_RUN       0x0001  //application in run mode
#define SM_BUSY      0x0002
#define SM_DEBUG     0x0004  //application in step-debug mode
#define SM_STOP      0x0008
#define SM_BLOCK     0x0010  //block application autorun
#define SM_MAIN      0x0020  //1 - reserve
#define SM_LOADER    0x0040  //loader mode
#define SM_WBLOCK    0x0080  //application writing is blocked
#define SM_SSTB      0x0100  //UNET/STHL 0x2C support (become MAIN)
#define SM_SBLK      0x0200  //is blocked to become main (key or run/stop in stop)
#define SM_STANDBY   0x0400  //Master is in standby mode
#define SM_SECONDARY 0x0800  //Master is in standby mode & secondary
#define SM_SD_CONN   0x1000  //SD is connected
#define SM_SD_SYNC   0x2000  //SD is connected and backup is done

//=== UNIMOD 2 [value] Target System Mode ======================================
#define WRK_MODE_INIT        0  //
#define WRK_MODE_RUN         1  // run mode
#define WRK_MODE_CFG         2  //
#define WRK_MODE_STEP        3  //
#define WRK_MODE_UPD         4  //
#define WRK_MODE_TESTRUN     5  //
#define WRK_MODE_TRANSFER    6  //
#define WRK_MODE_CANCEL      7  //
#define WRK_MODE_INITSLV     8  //
#define WRK_MODE_WAITSYNC    9  //
#define WRK_MODE_LOADER     10  // loader mode
#define WRK_MODE_BUSY     0xFF

//=== UNIMOD 2 [mask] Target System Mode extra flags ===========================
#define WRK_FLAGS_STOP       0x0001
#define WRK_FLAGS_SERVICE    0x0002
#define WRK_FLAGS_STANDBY    0x0004  //Master is in standby mode
#define WRK_FLAGS_SECONDARY  0x0008  //Master is in standby mode & secondary
#define WRK_FLAGS_BACKUP     0x0010  //in reserve
#define WRK_FLAGS_SBLK       0x0020  //is blocked to become main (key or run/stop in stop)
#define WRK_FLAGS_WBLOCK     0x0040  //application writing is blocked

//=== UNIMOD 2 [mask] Hardware flags ===========================================
#if defined(M501E)
 #define HARD_FLAGS_SD_CONN  0x0001  //SD is connected
#elif defined(M401E) || defined(M1201E)
 #define HARD_FLAGS_USB_CONN 0x0001  //USB is connected
 #define HARD_FLAGS_SLOT_M1  0x0002  //Master at M1 slot of carcass
 #define HARD_FLAGS_SLOT_M2  0x0004  //Master at M2 slot of carcass
#endif

//=== [mask] Switch ============================================================
 extern uint32_t    sw_mask;
#define SW_MCLR   0x001fc000L  //to clear GF_MODE mask (gf_mask)

//=== [mask] Digital Output ====================================================
 extern uint32_t    do_mask;
#define DO_MCLR   0x0e000000L  //to clear GF_DOUT mask (gf_mask)

//=== [mask] Digital Input =====================================================
 extern uint32_t    di_mask;
#define DI_MCLR   0xf0000000L  //to clear GF_DINP mask (gf_mask)

//=== [code] Modbus MKO Init Error ====================================================
 extern uint32_t    mbi_code;  //Modbus initialization error

#define MBI_E_VER         1
#define MBI_E_MEM         2
#define MBI_E_TASK        3
#define MBI_E_PORT        4
#define MBI_E_RUN         5
#define MBI_E_MODE_M      6
#define MBI_E_MODE_S      7
#define MBI_E_FUNC        8
#define MBI_E_TYPE        9
#define MBI_E_ORDER      10
#define MBI_E_FTYPE      11
#define MBI_E_CNT        12
#define MBI_E_VAR        13
#define MBI_E_VTYPE      14
#define MBI_E_PREC       15
#define MBI_E_STRUCT     16
#define MBI_E_MTYPE      17
#define MBI_E_REPEAT     18
#define MBI_E_BASE       19
#define MBI_E_DIAG       20
#define MBI_E_ERR_M172S  21

//=== [code] Bacnet Init Error ====================================================
#define BAC_I_E_MEM        1
#define BAC_I_E_TASK       2
#define BAC_I_E_RUN        3
//#define BAC_I_E_BASE       4
//#define BAC_I_E_DIAG       5

//=== [code] Update Code =======================================================
 extern uint32_t    upd_code;

#define APPLY_OK       0x00  //apply changes (done)
#define APPLY_SEND     0x01  //apply changes (send to backup)
#define APPLY_SINGLE   0x02  //apply changes (first error, single work)
#define APPLY_TESTRUN  0x03  //apply changes (test run on main)
#define APPLY_RECEIVE  0x04  //apply changes (receive from main)
#define APPLY_ERR_SEQ  0x05  //apply changes (error in update sequence)
#define APPLY_TOCANCEL 0x06  //apply changes (primary detected application error)
#define APPLY_CANCELED 0x07  //apply changes (update has canceled)

//=== [code] Force Error =======================================================

#define FE_NOERR  0x00  //no errors
#define FE_LOAD   0x01  //loading is already running
#define FE_FIND   0x02  //application not found
#define FE_WRITE  0x03  //application write error
#define FE_NOMEM  0x04  //not enough memory
#define FE_APPL   0x05  //application structure error
#define FE_CHSUM  0x06  //check sum error
#define FE_ACT    0x07  //incorrect argument

//=== [code] Target System Events ==============================================
// extern uint32_t    ev_code;  //some events

#define EV_MAIN                 0x01  //switch to main mode
#define EV_BACKUP               0x02  //switch to backup mode
#define EV_MSG_BLOCK            0x03  //some error messages is blocked
#define EV_MSG_UNBLOCK          0x04  //error messages is unblocked
#define EV_SMBUS_NO             0x05  //diagnostic for external ethernet card is not supported
#define EV_SERVICE_ON           0x06  //service mode on
#define EV_SERVICE_OFF          0x07  //service mode off
#define EV_LOAD_LOCK            0x08  //application loading is locked
#define EV_LOAD_UNLOCK          0x09  //application loading is unlocked
#define EV_SD_CONNECT           0x0A  //SD connect to master
#define EV_SD_DISCONN           0x0B  //SD disconnect from master
#define EV_SD_BACKUP_START      0x0C  //start backup to SD
#define EV_SD_BACKUP_END        0x0D  //backup to SD is done
#define EV_SD_RESTORE_START     0x0E  //start restore from SD
#define EV_SD_RESTORE_END       0x0F  //restore from SD is done
#define EV_MAIN_LOCK            0x10  //switch to main is locked
#define EV_MAIN_UNLOCK          0x11  //switch to main is unlocked
//#define EV_NEED_TO_REBOOT       0x12  //need reboot for finish synchronization
#define EV_VER_DIFF             0x13  //software version of remote master is differ
#define EV_VER_SAME             0x14  //software version of remote master is match
#define EV_TIMESET_BEFORE       0x15  //UM_W_TIME, timestamp before
#define EV_TIMESET_AFTER        0x16  //UM_W_TIME, timestamp after
#define EV_APP_DIFF             0x17  //application version of remote master is differ
#define EV_APP_SAME             0x18  //application version of remote master is match
#define EV_TIMESET_APPL_BEFORE  0x19  //SETTIME from appl, timestamp before
#define EV_IPTABLES             0x1A  //iptables

//=== [code] Tasks Events ======================================================

#define TASK_CONNECT       0x01  //gate. connect to master
#define TASK_DISCONN       0x02  //gate. disconnect from master
#define TASK_CHG_SETTINGS  0x03  //web. change settings
#define TASK_CHG_UMSTART   0x04  //web. change um_start
#define TASK_CHG_IEC       0x05  //web. change iec-104 configuration
#define TASK_CHG_IMPORT    0x06  //web. import settings
#define TASK_RESET         0x07  //web. reset
#define TASK_RESTART       0x08  //web. restart
#define TASK_APPLY         0x09  //web. apply changes
#define TASK_IEC_CONNECT   0x0A  //iec-104. connect to master
#define TASK_IEC_DISCONN   0x0B  //iec-104. disconnect from master (timeout or error)
#define TASK_IEC_BREAK     0x0C  //iec-104. close connection because of another abonent is connecting
#define TASK_MB_CONNECT    0x0D  //Modbus. connect to master
#define TASK_MB_DISCONN    0x0E  //Modbus. disconnect from master (timeout or error)
#define TASK_APPLY_OS      0x0F  //apply OS
#define TASK_TCP_CONNECT   0x10  //gate. tcp. connect to master
#define TASK_TCP_DISCONN   0x11  //gate. tcp. timeout in exchange
#define TASK_UMTCP_RESUME  0x12  //gate. tcp. resume exchange
#define TASK_UMTCP_ERR     0x13  //gate. tcp. disconnect by error
//reserv
#define TASK_UDP_CONNECT   0x18  //gate. udp. connect to master
#define TASK_UDP_DISCONN   0x19  //gate. udp. disconnect from master
#define TASK_LOAD_FW_TS    0x1A  //gate. start loading Target System firmware
#define TASK_LOAD_FW_OS    0x1B  //gate. start loading Operating System firmware
#define TASK_LOAD_FW_STM   0x1C  //gate. start loading STM firmware
//#define TASK_UPDATE_TS     0x1D  //update Target System
#define TASK_UDP_SMODE     0x1E  //gate. udp. Response to UM_SMODE has been sent
#define TASK_TCP_SMODE     0x1F  //gate. tcp. Response to UM_SMODE has been sent

//=== [code] Log File Error ====================================================

#define LOG_RC          0x02  //restart code
#define LOG_RE          0x03  //runtime error
#define LOG_AE          0x04  //application error
#define LOG_PE          0x05  //power error
#define LOG_TRM         0x06  //temperature error
#define LOG_HE          0x07  //hard error
#define LOG_CONF        0x08  //configuration error
#define LOG_RTN         0x09  //retain error
#define LOG_DE          0x0A  //driver error
#define LOG_SE          0x0B  //synchronization error
#define LOG_CE          0x0C  //communication error
#define LOG_SAFE        0x0D  //safe state occured
#define LOG_NE          0x0E  //MKO error
#define LOG_MBI         0x0F  //Modbus Init. error
#define LOG_CSE         0x10  //CLONE/DBL synchronization error
//#define LOG_MKO_I       0x11  //MKO Init. error
#define LOG_APPLY       0x12  //Apply changes
#define LOG_STATE       0x13  //Master State
#define LOG_TASKS       0x14  //Events of tasks
#define LOG_UNITS       0x15  //Events of UNITS configuration
#define LOG_BACNET_INIT 0x16  //BACnet Init. error
//#define LOG_CLIENTS_CNT 0xFF  //Count of connected clients for per IP

//==============================================================================

  //
  // File system exceptions are returned via standard messaging interface
  //

  #define FSEXCEPT_UNKNOWN_DRIVE      0x40          // Incorrect/unknown/not installed storage device specified
  #define FSEXCEPT_HARDWARE_ERROR     0x41          // Hardware error detected. current operation will be terminated
  #define FSEXCEPT_UNFORMATTED        0x42          // Unable access drive because it was not previously formatted
  #define FSEXCEPT_INVALID_NAME       0x43          // The specified string is not a correct file name
  #define FSEXCEPT_FILE_NOT_FOUND     0x44          // File with requested name was not founded
  #define FSEXCEPT_NO_MORE_SLOTS      0x45          // No more file slots avaliable to perform this operation (file create)
  #define FSEXCEPT_FILE_TOO_LONG      0x46          // The file length exceed absolute cluster limit (write exception)
  #define FSEXCEPT_INCONTINOUS        0x47          // Incontinous sequence of write operations (write exception)
  #define FSEXCEPT_OUT_OF_FILE        0x48          // Position is not a within file data/cluster (write exception)
  #define FSEXCEPT_OUT_OF_BUFFER      0x49          // Not enough memory to perform read operation (read exception, too many data requested)
  #define FSEXCEPT_FILE_EXISTS        0x4A          // Unable write/rewrite file because it already exists
  #define FSEXCEPT_OPENED_FILES       0x4B          // File system format not allowed then one or more files are opened
  #define FSEXCEPT_CLUSTER_SIZE       0x4C          // Incorrect cluster size
  #define FSEXCEPT_FRAM_UNSUPPORTED   0x4D          // Интеллектуальный модуль не поддерживает чтение(запись) в FRAM
  #define FSEXCEPT_OP_UNSUPPORTED     0x4E          // Данная операция не поддерживается
  #define FSEXCEPT_ACCESS_DENIED      0x4F          // Access denied
  #define FSEXCEPT_DIR_IS_NOT_EMPTY   0x5D          // Нельзя удалять не пустую директорию

//==============================================================================
#if defined(UNIMOD_CUT)

#define ERR_UMSTEP_NOMOD       0x10

#define ERR_UM_WDT_RESET       0x10

#define ERR_MASTER_CMD         0x10

#define ERR_SETTIME_LOCALTIME  0x10
#define ERR_SETTIME_SETTIME    0x11
#define ERR_SETTIME_HWCLOCK    0x12
#define ERR_SETTIME_TOO_OFTEN  0x13

#define ERR_PRIO_BADPID        0x10
#define ERR_PRIO_SETPRIO       0x11

#define ERR_TRANSIT_SEL_MOD    0x04

#endif

//==============================================================================

/*
#pragma pack ( 1 )//
typedef struct T_ESTATE
{
   u_char mode;     // stop, work, debug
   u_char gerr;     // global errors
   u_char aerr;     // application errors
   u_char cres;     // reset code
  u_short ver;
  u_short type;

  u_short conf;
   u_char rerr;     // runtime errors

   u_char ehard;
   u_char emod[3];
   u_char econf;
   u_char eunit[4];
   u_char econst[4];
   u_char eline[4];
   u_char elink[4];

}TL_ESTATE;
#pragma pack ( )//
*/

//==============================================================================

extern TN_MST_INF  MST_REM_INF;
extern    u_short  LOG_EXTRA; // additional argument for log
extern     u_char  LOG_TO_TMPBUF;

//==============================================================================

          void  um_flags_clear(void);
          void  um_flags_module(TM_MODULE*, u_short);
          void  um_flags_master(void);
          void  um_flags_system(void);

          void  bus_err_to_log(u_char, u_short, T_BUS_DIAG*, u_char, u_char);
          void  mod_brd_logging(T_BUS_LINE*, TM_MODULE*, u_char);
          void  net_brd_logging(uint32_t, uint32_t, T_UMTASK*);

          void  mod_brd_logging_2_0(TM_MODULE*);

           int  log_init(uint32_t, u_char, char*);
          void  log_set_buf(u_char*);
           int  log_write(void);
          void  log_close(void);
          void  log_add(u_short code_h, uint32_t code_l, uint32_t extra, u_char ismask);
          void  log_if_changed(u_short*, u_short, uint32_t, u_short, u_char);
          void  log_add_ts_v10(u_short, uint32_t, u_short, u_char, uint32_t, uint32_t);
          void  log_add_ts_v11(u_short code_h, uint32_t code_l, uint32_t extra, u_char ismask, uint32_t sec, u_short msec);
           int  log_fread(u_char*, u_char*, uint32_t);
          void  log_add_from_tmpbuf();
       LOG_REC* log_find_reset_reason();
           int  log_get_size();
           int  log_get_ram_size(uint32_t, TL_HDR*);
           int  log_get_ram_buf(uint32_t, uint32_t, TL_HDR*);
          void  fun_shm_open();
          void  fun_shm_put(unsigned);

//==============================================================================

//#define DEF_USE_PROFILER

  #define  TIMES_CNT  30
  extern  u_char  USE_PROFILER;
  extern u_short  PROFILER_MIN;
  extern    char  PROFILER_PATH[MAX_PATH];
  extern  uint32_t  PROFILER_SIZE;
  extern  uint32_t  profiler_times[TIMES_CNT];

  extern  uint32_t  profiler_ts[TIMES_CNT];
  extern  uint32_t  PRE_CYCLE_SAV;        //duration of previous cycle

            void  profiler_check(u_char);

//#define USE_LOGGER

  extern  u_char  KER_DUMP_LOG;
  extern  u_char  BUS_DUMP_LOG;
  extern  u_char  COM_DUMP_LOG;

             int  logger_init();
            void  logger_add(u_char id, int point, u_char* buf, u_short cmd_len);
            void  logger_save();

/* // !!!!! debug
  extern  u_char  flag_logger_lock;
*/
  extern  u_char  flag_logger_save;
/*
  extern  u_char  flag_logger_save_prev;
*/ // !!!!! debug end

//==============================================================================
#endif
