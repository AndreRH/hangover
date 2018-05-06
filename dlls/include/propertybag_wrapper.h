/*
 * Copyright 2018 Stefan Dösinger for CodeWeavers
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
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef PROPERTYBAG_WRAPPER_H
#define PROPERTYBAG_WRAPPER_H

#include <oaidl.h>

struct propertybag_wrapper;

struct propertybag_wrapper *propertybag_wrapper_create(uint64_t guest_iface);
struct propertybag_wrapper *propertybag_wrapper_from_IPropertyBag(IPropertyBag *iface);
void propertybag_wrapper_destroy(struct propertybag_wrapper *wrapper);
uint64_t propertybag_wrapper_guest_iface(struct propertybag_wrapper *wrapper);
IPropertyBag * propertybag_wrapper_host_iface(struct propertybag_wrapper *wrapper);

#endif
