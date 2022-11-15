/*
 * default_config.h
 *
 * This header contains a default setup, in case the virtual eeprom fails, or if we decide to not use it.
 * The data in here will act as the default for the values in the handles,
 * if reading from eeprom is successful, it will be overwritten
 *
 *  Created on: Oct 1, 2021
 *      Author: fbalazs
 */

#ifndef INC_DEFAULT_CONFIG_H_
#define INC_DEFAULT_CONFIG_H_

/* 0 - default 5000-7500-10000 lut
 * 1 - flipased luts and config
 * 2 - sindy luts and config
 *
 * 4 - DD test config
 */
#define manual_config_select 1

void default_config();

#endif /* INC_DEFAULT_CONFIG_H_ */
