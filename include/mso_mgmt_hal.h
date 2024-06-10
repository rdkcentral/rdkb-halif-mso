/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**!
*
* @file mso_mgmt_hal.h
* @brief MSO Management Hardware Abstraction Layer (HAL)
*
* This header file provides a standardized interface for interacting with
* DOCSIS devices in Multiple System Operator (MSO) environments.
*
* The MSO Management HAL enables key functionalities like:
*   -  Device provisioning and configuration
*   - Data model access (reading/writing parameters)
*   - Event notifications for status changes
*   - Security management for device interactions
*
* By abstracting hardware and protocol specifics, this HAL simplifies
* management application development for diverse DOCSIS devices.
*/

#ifndef __MSO_MGMT_HAL_H__
#define __MSO_MGMT_HAL_H__

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/
/**
* @defgroup msomgmt_hal MSO Management HAL
*
* This module provides the function call prototypes and structure definitions.
*
* @defgroup  msomgmt_hal_types  MSO Management HAL Data Types
* @ingroup   msomgmt_hal
*
* @defgroup msomgmt_hal_apis   MSO Management HAL APIs
* @ingroup  msomgmt_hal
*
**/


/**
 * @addtogroup msomgmt_hal_types
 * @{
 */

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif

typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef int             boolean;

#ifndef SEC_PER_YEAR
#define SEC_PER_YEAR    31536000
#endif

#ifndef SIZE_arrisCmDevHttpClientSee
#define SIZE_arrisCmDevHttpClientSeed 8L
#endif

#ifndef ERROR
#define ERROR -1
#endif

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
/**! Indicates the result of MSO password validation. */
typedef enum
{
    Invalid_PWD, /**!< Password is Invalid. */
    Good_PWD,    /**!< Password is valid. */
    Unique_PWD,  /**!< Password is Unique (not previously used). */
    Expired_PWD, /**!< Password is Expired. */
    TimeError    /**!< Time-related error occurred during validation. */
}
mso_pwd_ret_status;

/*
* TODO:
*   - Consider renaming enum values to a more consistent format (e.g., `MSO_PWD_INVALID`, `MSO_PWD_GOOD`, etc.).
*   - Add a value representing "Unknown" or "Not Validated" for cases where validation hasn't been performed yet.
*   - Evaluate the need for a "Unique" status; this may be better handled as a separate flag or function.
*/

/**
 * @}
 */

/**
 * @addtogroup msomgmt_hal_apis
 * @{
 */

/*
* TODO (Error Handling Enhancement - MsoMgmt HAL):
*   - Replace the generic `RETURN_ERR` with an enumerated error code type for improved clarity and debugging.
*   - Define specific error codes to pinpoint various failure scenarios, including:
*       - Invalid input parameters (e.g., null pointers, out-of-range values, invalid MAC addresses)
*       - Resource allocation failures (e.g., out-of-memory)
*       - Communication errors with the cable modem or underlying hardware
*       - Timeout errors when waiting for responses
*       - File system errors (e.g., file not found, permission denied)
*       - DOCSIS-specific errors (e.g., ranging failure, registration failure)
*       - SNMP-related errors (e.g., authentication failure, MIB access issues)
*       - Firmware update errors (e.g., download failure, invalid image)
*       - Internal errors within the MsoMgmt HAL
*   - Document the new error codes thoroughly in the header file and any relevant guides.
*/

/**!
* @brief Validates a password against the current MSO "password of the day."
*
* This function checks if the provided password matches the valid password set for the MSO user for the current day.
*
* @param[in] pwd - The password to be validated (pre-allocated by the caller).
*
* @returns Password validation status (`mso_pwd_ret_status`):
* @retval Invalid_PWD - Password is invalid (does not match the current password of the day).
* @retval Good_PWD - Password is valid and matches the current password of the day.
* @retval Expired_PWD - Password has expired.
* @retval TimeError - A time-related error occurred during validation (e.g., clock synchronization issue).
*
* TODO: 
*  - Consider removing `Unique_PWD` as it may be unrelated to the "password of the day" concept.
*  - Add a `MSO_PWD_UNKNOWN` or `MSO_PWD_NOT_VALIDATED` value to the enum for cases where validation cannot be performed or hasn't occurred yet.
*  - Introduce more specific error codes for invalid passwords (e.g., `MSO_PWD_WRONG`, `MSO_PWD_FORMAT_ERROR`).
*/
mso_pwd_ret_status mso_validatepwd(char *pwd);

/**!
* @brief Sets the "Password of the Day" (PoD) seed for MSO password validation.
*
* This function configures the seed value used to generate the daily password for MSO users.
*
* @param[in] pSeed - The PoD seed (pre-allocated buffer, at least 64 bytes).
*
* @returns Status of the operation:
* @retval RETURN_OK - On success.
* @retval RETURN_ERR - On failure (e.g., invalid seed, decryption error).
*
* @note Newer Broadband Devices MUST decrypt the seed on demand when this function is called.
*/
INT mso_set_pod_seed(char *pSeed);

/**!
* @brief Retrieves the Password of the Day (PoD) seed for MSO password validation.
*
* This function retrieves the decrypted PoD seed from the configuration file or the `rdkbEncryptedClientSeed` SNMP OID.
*
* @param[out] pSeed - Pre-allocated buffer (at least 64 bytes) to store the retrieved seed. 
*
* @returns Status of the operation:
* @retval RETURN_OK - On success.
* @retval RETURN_ERR - On failure (e.g., retrieval error, decryption error).
*
* @note  For security reasons, the `pSeed` buffer MUST be manually overwritten after use.
*/
INT mso_get_pod_seed(char* pSeed);

#endif
/**
 * @}
 */

