/*
 * hal_spi.h
 *
 * Copyright (c) ${year}, Diego F. Asanza. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * Created on January 23, 2015, 8:27 PM
 */
#ifndef HAL_SPI_H
#define	HAL_SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

    void hal_spi_init_16bit(void);
    void hal_spi_write_16bit(uint16_t value);

#ifdef	__cplusplus
}
#endif

#endif	/* HAL_SPI_H */

