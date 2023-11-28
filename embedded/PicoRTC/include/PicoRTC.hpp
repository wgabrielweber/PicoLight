/**
 * @file PicoRTC.hpp
 * @brief New time and date formats for the original SDK functions
 * @author Gabriel Weber Berwian <wgabrielweber@hotmail.com>
 * @date 19/11/2023
 * @institution UFSC
 */

#ifndef PICORTC_HPP_
#define PICORTC_HPP_

#include <stdio.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

void new_datetime_str(char *result, size_t size, const char *datetime_str);

#endif /* PICORTC_HPP_ */