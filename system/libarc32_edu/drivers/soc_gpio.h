/** INTEL CONFIDENTIAL Copyright 2014-2015 Intel Corporation All Rights Reserved.
  *
  * The source code contained or described herein and all documents related to
  * the source code ("Material") are owned by Intel Corporation or its suppliers
  * or licensors.
  * Title to the Material remains with Intel Corporation or its suppliers and
  * licensors.
  * The Material contains trade secrets and proprietary and confidential information
  * of Intel or its suppliers and licensors. The Material is protected by worldwide
  * copyright and trade secret laws and treaty provisions.
  * No part of the Material may be used, copied, reproduced, modified, published,
  * uploaded, posted, transmitted, distributed, or disclosed in any way without
  * Intel's prior express written permission.
  *
  * No license under any patent, copyright, trade secret or other intellectual
  * property right is granted to or conferred upon you by disclosure or delivery
  * of the Materials, either expressly, by implication, inducement, estoppel or
  * otherwise.
  *
  * Any license under such intellectual property rights must be express and
  * approved by Intel in writing
  *
  ******************************************************************************/

#ifndef SOC_GPIO_H_
#define SOC_GPIO_H_

/**
 * \addtogroup common_drivers
 * @{
 * \defgroup soc_gpio SOC GPIO: General Purpose Input/Output API
 * @{
 * \brief Definition of the structure and functions used by SOC GPIO Driver implementation.
 */

#if defined(CONFIG_SOC_GPIO_32) || defined(CONFIG_SOC_GPIO_AON)

#include "data_type.h"
#include "gpio.h"

// soc gpio 32 bit count
#if defined(CONFIG_SOC_GPIO_32)
#define SOC_GPIO_32_BITS    (32)
#endif

// soc gpio aon bit count
#if defined(CONFIG_SOC_GPIO_AON)
#define SOC_GPIO_AON_BITS    (6)
#endif

/*!
 * Port list
 */
typedef enum {
#if defined(CONFIG_SOC_GPIO_32)
    SOC_GPIO_32=0,      /*!< GPIO 32 port */
    #if defined(CONFIG_SOC_GPIO_AON)
    SOC_GPIO_AON,       /*!< GPIO aon port */
    #endif
#elif defined(CONFIG_SOC_GPIO_AON)
    SOC_GPIO_AON=0,     /*!< GPIO aon port */
#endif
    SOC_PORT_COUNT      /*!< GPIO port count */
} SOC_GPIO_PORT;


#ifdef __cplusplus
 extern "C" {
#endif

/*! \fn     DRIVER_API_RC soc_gpio_set_config(SOC_GPIO_PORT port_id, uint8_t bit, gpio_cfg_data_t *config)
*
*  \brief   Function to configure specified GPIO bit in specified GPIO port
*           Configuration parameters must be valid or an error is returned - see return values below.
*
*  \param   port_id         : GPIO port identifier
*  \param   bit             : bit in port to configure
*  \param   config          : pointer to configuration structure
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_DEVICE_TYPE_NOT_SUPPORTED    - if port id is not supported by this controller\n
*           DRV_RC_INVALID_CONFIG               - if any configuration parameters are not valid\n
*           DRV_RC_CONTROLLER_IN_USE,             if port/bit is in use\n
*           DRV_RC_CONTROLLER_NOT_ACCESSIBLE      if port/bit is not accessible from this core\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_set_config(SOC_GPIO_PORT port_id, uint8_t bit, gpio_cfg_data_t *config);

/*! \fn     DRIVER_API_RC soc_gpio_set_port_config(SOC_GPIO_PORT port_id, soc_gpio_cfg_data_t *config)
*
*  \brief   Function to configure specified GPIO port (in LMT case the selection is ignored - only one port)
*
*  \param   port_id :         GPIO port identifier
*  \param   config  :         pointer to configuration structure
*
*  \return  RC_OK on success
*           RC_DEVICE_TYPE_NOT_SUPPORTED    - if port id is not supported by this controller
*           RC_INVALID_CONFIG               - if any configuration parameters are not valid
*           RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_set_port_config(SOC_GPIO_PORT port_id, gpio_port_cfg_data_t *config);

/*! \fn     DRIVER_API_RC soc_gpio_deconfig(SOC_GPIO_PORT port_id, uint8_t bit)
*
*  \brief   Function to deconfigure specified GPIO bit in specified GPIO port
*           Configuration parameters must be valid or an error is returned - see return values below.
*
*  \param   port_id         : GPIO port identifier
*  \param   bit             : bit in port to deconfigure
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_DEVICE_TYPE_NOT_SUPPORTED    - if port id is not supported by this controller\n
*           DRV_RC_INVALID_CONFIG               - if any configuration parameters are not valid\n
*           DRV_RC_CONTROLLER_IN_USE,             if port/bit is in use\n
*           DRV_RC_CONTROLLER_NOT_ACCESSIBLE      if port/bit is not accessible from this core\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_deconfig(SOC_GPIO_PORT port_id, uint8_t bit);

/*! \fn     DRIVER_API_RC soc_gpio_port_deconfig(SOC_GPIO_PORT port_id)
*
*  \brief   Function to deconfigure specified specified GPIO port
*
*  \param   port_id :        GPIO port identifier
*
*  \return  DRV_RC_OK on success
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_port_deconfig(SOC_GPIO_PORT port_id);

/*! \fn     DRIVER_API_RC soc_gpio_enable(SOC_GPIO_PORT port_id)
*
*  \brief   Function to enable the specified GPIO port
*           Upon success, the specified GPIO port is no longer clock gated in hardware, it is now
*           capable of reading and writing GPIO bits and of generating interrupts.
*
*  \param   port_id         : GPIO port identifier
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_DEVICE_TYPE_NOT_SUPPORTED    - if port id is not supported by this controller\n
*           DRV_RC_INVALID_CONFIG               - if any configuration parameters are not valid\n
*           DRV_RC_CONTROLLER_IN_USE,             if port/bit is in use\n
*           DRV_RC_CONTROLLER_NOT_ACCESSIBLE      if port/bit is not accessible from this core\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_enable(SOC_GPIO_PORT port_id);

/*! \fn     DRIVER_API_RC soc_gpio_disable(SOC_GPIO_PORT port_id)
*
*  \brief   Function to disable the specified GPIO port
*           Upon success, the specified GPIO port is clock gated in hardware, it is now
*           incapable of reading, writing GPIO bits and of generating interrupts.
*
*  \param   port_id         : GPIO port identifier
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_DEVICE_TYPE_NOT_SUPPORTED    - if port id is not supported by this controller\n
*           DRV_RC_INVALID_CONFIG               - if any configuration parameters are not valid\n
*           DRV_RC_CONTROLLER_IN_USE,             if port/bit is in use\n
*           DRV_RC_CONTROLLER_NOT_ACCESSIBLE      if port/bit is not accessible from this core\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_disable(SOC_GPIO_PORT port_id);

/*! \fn     DRIVER_API_RC soc_gpio_write(SOC_GPIO_PORT port_id, uint8_t bit, boolean_t value)
*
*  \brief   Function to set output value on the gpio bit
*
*  \param   port_id         : GPIO port identifier
*  \param   bit             : bit in port to configure
*  \param   value           : value to write to bit
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_write(SOC_GPIO_PORT port_id, uint8_t bit, boolean_t value);


/*! \fn     DRIVER_API_RC soc_gpio_read(SOC_GPIO_PORT port_id, uint8_t bit, boolean_t *value)
*
*  \brief   Function to read a GPIO bit
*
*  \param   port_id         : GPIO port identifier
*  \param   bit             : bit in port to configure
*  \param   *value          : address to place read value
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_read(SOC_GPIO_PORT port_id, uint8_t bit, boolean_t *value);

/*! \fn     DRIVER_API_RC soc_gpio_write_port(SOC_GPIO_PORT port_id, uint32_t value)
*
*  \brief   Function to write to a value to a given port
*
*  \param   port_id         : GPIO port identifier
*  \param   value           : value to write to port
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_write_port(SOC_GPIO_PORT port_id, uint32_t value);

/*! \fn     DRIVER_API_RC soc_gpio_read_port(SOC_GPIO_PORT port_id, uint32_t *value)
*
*  \brief   Function to read a given port
*
*  \param   port_id         : GPIO port identifier
*  \param   *value          : location to store result
*
*  \return  DRV_RC_OK on success\n
*           DRV_RC_FAIL otherwise
*/
DRIVER_API_RC soc_gpio_read_port(SOC_GPIO_PORT port_id, uint32_t *value);

#ifdef __cplusplus
}
#endif

#endif
#endif  /* SOC_GPIO_H_ */

/**@} @}*/
