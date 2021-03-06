//
//  CommandClassesPublic.h
//  Part of Z-Way.C library
//
//  Created by Alex Skalozub on 2/1/12.
//  Based on Z-Way source code written by Christian Paetz and Poltorak Serguei
//
//  Copyright (c) 2012 Z-Wave.Me
//  All rights reserved
//  info@z-wave.me
//
//  This source file is subject to the terms and conditions of the
//  Z-Wave.Me Software License Agreement which restricts the manner
//  in which it may be used.
//

#ifndef zway_command_classes_public_h
#define zway_command_classes_public_h


// Command Class Basic //

// Send Basic Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_basic_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Basic Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: value
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_basic_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE value, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Wakeup //

// Send Wakeup Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_wakeup_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Wakeup CapabilityGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_wakeup_capabilities_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Wakeup NoMoreInformation (Sleep)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_wakeup_sleep(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Wakeup Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: interval
// Wakeup interval in seconds
//
// @param: notification_node_id
// Node Id to be notified about wakeup
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_wakeup_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int interval, ZWBYTE notification_node_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class NoOperation //

// Send NoOperation empty packet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
// This function is not exported into C and JS. Please use zway_device_send_nop() instead
// ZWEXPORT ZWError zway_cc_nop_send(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Battery //

// Send Battery Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_battery_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class ManufacturerSpecific //

// Send ManufacturerSpecific Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_manufacturer_specific_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ManufacturerSpecific Device Id Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: type
// Device Id type to request
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_manufacturer_specific_device_id_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE type, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Proprietary //

// Send Proprietary Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_proprietary_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Proprietary Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: length
// Length of data
//
// @param: data
// Data to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_proprietary_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE length, const ZWBYTE *data, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Configuration //

// Send Configuration Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: parameter
// Parameter number (from 1 to 255)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_configuration_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE parameter, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Configuration Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: parameter
// Parameter number (from 1 to 255)
//
// @param: value
// Value to be sent (negative and positive values are accepted, but will be stripped to size)
//
// @param: size
// @default: 0
// Size of the value (1, 2 or 4 bytes). Use 0 to guess from previously reported value if any
// 0 means use size previously obtained Get
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_configuration_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE parameter, int value, ZWBYTE size, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Configuration SetDefault
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: parameter
// Parameter number to be set to device default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_configuration_set_default(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE parameter, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SensorBinary //

// Send SensorBinary Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: sensorType
// Type of sensor to query information for
// @default: -1
// 0xFF to query information for the first available sensor type
// -1 to query information for all supported sensor types
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_sensor_binary_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int sensorType, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Association //

// Send Association Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// @default: 0
// Group Id (from 1 to 255)
// 0 requests all groups
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Association Set (Add)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// Group Id (from 1 to 255)
//
// @param: include_node
// Node to be added to the group
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZWBYTE include_node, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Association Remove
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// Group Id (from 1 to 255)
//
// @param: exclude_node
// Node to be removed from the group
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_remove(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZWBYTE exclude_node, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Association GroupingsGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_groupings_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Meter //

// Send Meter Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: scale
// @default: -1
// Desired scale
// -1 for all scales
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int scale, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Meter Reset
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_reset(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Meter SupportedGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_supported(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class MeterPulse //

// Send MeterPulse Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_pulse_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SensorMultilevel //

// Send SensorMultilevel Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: sensor_type
// @default: -1
// Type of sensor to be requested.
// -1 means all sensor types supported by the device
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_sensor_multilevel_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int sensor_type, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SensorConfiguration //

// Send SensorConfiguration Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_sensor_configuration_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SensorConfiguration Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// Value set mode
//
// @param: value
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_sensor_configuration_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE mode, float value, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SwitchAll //

// Send SwitchAll Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_all_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchAll Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// SwitchAll Mode: see definitions below
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_all_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

#define SWITCH_ALL_SET_EXCLUDED_FROM_THE_ALL_ON_ALL_OFF_FUNCTIONALITY            0x00
#define SWITCH_ALL_SET_EXCLUDED_FROM_THE_ALL_ON_FUNCTIONALITY_BUT_NOT_ALL_OFF    0x01
#define SWITCH_ALL_SET_EXCLUDED_FROM_THE_ALL_OFF_FUNCTIONALITY_BUT_NOT_ALL_ON    0x02
#define SWITCH_ALL_SET_INCLUDED_IN_THE_ALL_ON_ALL_OFF_FUNCTIONALITY              0xFF

// Send SwitchAll Set On
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_all_set_on(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchAll Set Off
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_all_set_off(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SwitchBinary //

// Send SwitchBinary Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_binary_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchBinary Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: value
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_binary_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBOOL value, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class SwitchMultilevel //

// Send SwitchMultilevel Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_multilevel_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchMultilevel Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: level
// Level to be set
//
// @param: duration
// @default: 0xff
// Duration of change:
//  0 instantly
//  0x01-0x7f in seconds
//  0x80-0xfe in minutes mapped to 1-127 (value 0x80=128 is 1 minute)
//  0xff use device factory default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_multilevel_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE level, ZWBYTE duration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchMultilevel StartLevelChange
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: dir
// Direction of change: 0 to incrase, 1 to decrase
//
// @param: duration
// @default: 0xff
// Duration of change:
//  0 instantly
//  0x01-0x7f in seconds
//  0x80-0xfe in minutes mapped to 1-127 (value 0x80=128 is 1 minute)
//  0xff use device factory default
//
// @param: ignoreStartLevel
// @default: TRUE
// If set to True, device will ignore start level value and will use it's curent value
//
// @param: startLevel
// @default: 50
// Start level to change from
//
// @param: incdec
// @default: 0
// Increment/decrement type for step:
//  0 Increment
//  1 Decrement
//  2 Reserved
//  3 No Inc/Dec
//
// @param: step
// @default: 0xff
// Step to be used in level change in percentage
// 0-99 mapped to 1-100%
// 0xff uses device factory default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_multilevel_start_level_change(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE dir, ZWBYTE duration, ZWBOOL ignoreStartLevel, ZWBYTE startLevel, ZWBYTE incdec, ZWBYTE step, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchMultilevel StopLevelChange
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_multilevel_stop_level_change(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class MultiChannelAssociation //

// Send MultiChannelAssociation Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// @default: 0
// Group Id (from 1 to 255)
// 0 requests all groups
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_association_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannelAssociation Set (Add)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// Group Id (from 1 to 255)
//
// @param: include_node
// Node to be added to the group
//
// @param: include_instance
// Instance of the node to be added to the group
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_association_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZWBYTE include_node, ZWBYTE include_instance, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannelAssociation Remove
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group_id
// Group Id (from 1 to 255)
//
// @param: exclude_node
// Node to be removed from the group
//
// @param: exclude_instance
// Instance of the node to be removed from the group
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_association_remove(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group_id, ZWBYTE exclude_node, ZWBYTE exclude_instance, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannelAssociation GroupingsGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_association_groupings_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class MultiChannel //

// Send MultiChannel Get (MultiInstance V1 command)
// Reports number of channels supporting a defined Command Class
// Depricated by MutliChannel V2 - needed for old devices only
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: cc_id
// Command Class Id in question
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE cc_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannel Endpoint Find
// Note that MultiChannel EndpointFind Report is not supported as useless. But one can still trap the response packet in logs.
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: generic
// Generic type in search
//
// @param: specific 
// Specific type in search
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_endpoint_find(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE generic, ZWBYTE specific, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannel Endpoint Get
// Get the number of available endpoints
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_endpoint_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannel Capabilities Get
// Request information about the specified endpoint
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: endpoint
// Endpoint in question
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_capabilities_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE endpoint, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send MultiChannel Aggregated Members Get
// Request information about endpoints in the specified aggregated endpoint (v4 and above)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: endpoint
// Aggregated endpoint in question
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_multichannel_aggregated_members_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE endpoint, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Node Naming //

// Send NodeNaming GetName and GetLocation
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_node_naming_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send NodeNaming GetName
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_node_naming_get_name(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send NodeNaming GetLocation
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_node_naming_get_location(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send NodeNaming SetName
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: name
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_node_naming_set_name(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWCSTR name, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send NodeNaming SetLocation
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: location
// Value
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_node_naming_set_location(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWCSTR location, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat SetPoint //

// Send ThermostatSetPoint Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// @default: -1
// Thermostat Mode
// -1 requests for all modes
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_thermostat_setpoint_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ThermostatSetPoint Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// Thermostat Mode
//
// @param: value
// temperature
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_thermostat_setpoint_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int mode, float value, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat Mode //

// Send ThermostatMode Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_thermostat_mode_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ThermostatMode Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// Thermostat Mode
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_thermostat_mode_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat Fan Mode //

// Send ThermostatFanMode Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_thermostat_fan_mode_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ThermostatFanMode Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: on
// TRUE to turn fan on (and set mode), FALSE to comletely turn off (mode is ignored)
// 
// @param: mode
// Thermostat Fan Mode
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_thermostat_fan_mode_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBOOL on, ZWBYTE mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat Fan State //

// Send ThermostatFanState Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_thermostat_fan_state_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Thermostat Operating State //

// Send ThermostatOperatingState Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_thermostat_operating_state_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ThermostatOperatingState Logging Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: state
// State number to get logging for
// 0 to get log for all supported states
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_thermostat_operating_state_logging_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE state, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Alarm Sensor //

// Send AlarmSensor SupportedGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_alarm_sensor_supported_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send AlarmSensor Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: type
// @default: -1
// Alarm type to get
// -1 means get all types
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_alarm_sensor_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int type, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Door Lock //

// Send DoorLock Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_door_lock_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send DoorLock Configuration Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_door_lock_configuration_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send DoorLock Configuration Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: mode
// Lock mode
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_door_lock_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE mode, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send DoorLock Configuration Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: opType
// Operation type
//
// @param: outsideState
// State of outside door handle
//
// @param: insideState
// State of inside door handle
//
// @param: lockMin
// Lock after a specified time (minutes part)
//
// @param: lockSec
// Lock after a specified time (seconds part)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_door_lock_configuration_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE opType, ZWBYTE outsideState, ZWBYTE insideState, ZWBYTE lockMin, ZWBYTE lockSec, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Door Lock Logging //

// Send DoorLockLogging Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: record
// @default: 0
// Record number to get, or 0 to get last records
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_door_lock_logging_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE record, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class User Code //

// Send UserCode Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// @default: -1
// User index to get code for (1 ... maxUsers)
// -1 to get codes for all users
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_user_code_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send UserCode Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User index to set code for (1...maxUsers)
// 0 means set for all users
//
// @param: code
// Code to set (4...10 characters long)
//
// @param: status
// Code status to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_user_code_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWCSTR code, ZWBYTE status, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send UserCode Set (raw)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User index to set code for (1...maxUsers)
// 0 means set for all users
//
// @param: length
// Length of code in bytes
//
// @param: code
// Code to set (4...10 bytes long)
//
// @param: status
// Code status to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_user_code_set_raw(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE length, const ZWBYTE *code, ZWBYTE status, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Command Class Time //

// Send Time TimeGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_time_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Time DateGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_date_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Time TimeOffsetGet
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_offset_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Time Parameters //

// Send TimeParameters Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_parameters_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send TimeParameters Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_time_parameters_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Clock //

// Send Clock Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_clock_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Clock Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_clock_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Scene Activation //

// Send SceneActivation Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: sceneId
// Scene Id
//
// @param: dimmingDuration
// @default: 0xff
// Dimming duration
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_scene_activation_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE sceneId, ZWBYTE dimmingDuration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Scene Controller Conf //

// Send SceneControllerConf Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group
// @default: 0
// Group Id
// 0 requests all groups
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_scene_controller_conf_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SceneControllerConf Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: group
// Group Id
//
// @param: scene
// Scene Id
//
// @param: duration
// @default: 0x0
// Duration
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_scene_controller_conf_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE group, ZWBYTE scene, ZWBYTE duration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Scene Actuator Conf //

// Send SceneActuatorConf Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: scene
// @default: 0
// Scene Id
// 0 means get current scene
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_scene_actuator_conf_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE scene, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SceneActuatorConf Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: scene
// Scene Id
//
// @param: level
// Level
//
// @param: dimming
// @default: 0xff
// Dimming
//
// @param: override
// @default: TRUE
// If false then the current settings in the device is associated with the Scene Id. If true then the Level value is used
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_scene_actuator_conf_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE scene, ZWBYTE level, ZWBYTE dimming, ZWBOOL override, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Indicator //

// Send Indicator Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_indicator_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Indicator Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: val
// Value to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_indicator_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE val, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Protection //

// Send Protection Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: state
// Local control protection state
//
// @param: rfState
// @default: 0
// RF control protection state
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE state, ZWBYTE rfState, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Exclusive Control Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_exclusive_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Exclusive Control Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: controlNodeId
// Node Id to have exclusive control over destination node
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_exclusive_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE controlNodeId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Timeout Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_timeout_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Protection Timeout Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: timeout
// Timeout in seconds
// 0 is no timer set
// -1 is infinite timeout
// max value is 191 minute (11460 seconds)
// values above 1 minute are rounded to 1-minute boundary
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_protection_timeout_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int timeout, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Schedule Entry Lock //

// Send ScheduleEntryLock Enable(All)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to enable/disable schedule for
// 0 to enable/disable for all users
//
// @param: enable
// TRUE to enable schedule, FALSE otherwise
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_enable(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBOOL enable, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ScheduleEntryLock Weekday Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to get schedule for
// 0 to get for all users
//
// @param: slot
// Slot to get schedule for
// 0 to get for all slots
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_weekday_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE slot, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ScheduleEntryLock Weekday Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to set schedule for
//
// @param: slot
// Slot to set schedule for
//
// @param: dayOfWeek
// Weekday number (0..6)
// 0 = Sunday
// ...
// 6 = Saturday
//
// @param: startHour
// Hour when schedule starts (0..23)
//
// @param: startMinute
// Minute when schedule starts (0..59)
//
// @param: stopHour
// Hour when schedule stops (0..23)
//
// @param: stopMinute
// Minute when schedule stops (0..59)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_weekday_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE slot, ZWBYTE dayOfWeek, ZWBYTE startHour, ZWBYTE startMinute, ZWBYTE stopHour, ZWBYTE stopMinute, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ScheduleEntryLock Year Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to enable/disable schedule for
// 0 to get for all users
//
// @param: slot
// Slot to get schedule for
// 0 to get for all slots
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_year_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE slot, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ScheduleEntryLock Year Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: user
// User to set schedule for
//
// @param: slot
// Slot to set schedule for
//
// @param: startYear
// Year in current century when schedule starts (0..99)
//
// @param: startMonth
// Month when schedule starts (1..12)
//
// @param: startDay
// Day when schedule starts (1..31)
//
// @param: startHour
// Hour when schedule starts (0..23)
//
// @param: startMinute
// Minute when schedule starts (0..59)
//
// @param: stopYear
// Year in current century when schedule stops (0..99)
//
// @param: stopMonth
// Month when schedule stops (1..12)
//
// @param: stopDay
// Day when schedule stops (1..31)
//
// @param: stopHour
// Hour when schedule stops (0..23)
//
// @param: stopMinute
// Minute when schedule stops (0..59)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_schedule_entry_lock_year_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int user, ZWBYTE slot, ZWBYTE startYear, ZWBYTE startMonth, ZWBYTE startDay, ZWBYTE startHour, ZWBYTE startMinute, ZWBYTE stopYear, ZWBYTE stopMonth, ZWBYTE stopDay, ZWBYTE stopHour, ZWBYTE stopMinute, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Command Class ClimateControlSchedule //

// Send ClimateControlSchedule Override Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_climate_control_schedule_override_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send ClimateControlSchedule Override Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: overrideType
// Override type to set
// (0 - no override, 1 - temporary override, 2 - permanent override)
//
// @param: overrideState
// Override state
// -128 (0x80) ... -1 (0xFF): setpoint -12.8 ... -0.1 degrees
// 0 (0x00): setpoint
// 1 (0x01) ... 120 (0x78): setpoint +0.1 ... +12 degrees
// 121 (0x79): frost protection
// 122 (0x7A): energy saving
// 123 (0x7B) ... 126 (0x7D): reserved
// 127 (0x7F): unused
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_climate_control_schedule_override_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE overrideType, ZWBYTE overrideState, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Command Class MeterTableMonitor //

// Send StatusTableMonitor Status Get for a range of dates
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: maxResults
// @default: 0
// Maximum number of entries to get from log
// 0 means all matching entries
//
// @param: startDate
// Start date and time (local UNIX time)
//
// @param: endDate
// End date and time (local UNIX time)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_table_monitor_status_date_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE maxResults, time_t startDate, time_t endDate, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send StatusTableMonitor Status Get for specified depth
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: maxResults
// @default: 0
// Number of entries to get from log
// 0 means current status only
// 0xFF means all entries
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_table_monitor_status_depth_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE maxResults, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send StatusTableMonitor Current Data Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: setId
// @default: 0
// Index of dataset to get data for
// 0 to get data for all supported datasets
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_table_monitor_current_data_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE setId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send StatusTableMonitor Historical Data Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: setId
// @default: 0
// Index of dataset to get data for
// 0 to get data for all supported datasets
//
// @param: maxResults
// @default: 0
// Maximum number of entries to get from log
// 0 means all matching entries
//
// @param: startDate
// Start date and time (local UNIX time)
//
// @param: endDate
// End date and time (local UNIX time)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_meter_table_monitor_historical_data_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE setId, ZWBYTE maxResults, time_t startDate, time_t endDate, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class Alarm //

// Send Alarm Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: type
// @default: 0
// Type of alarm to get level for
// 0 to get level for all supported alarms (v2 and higher)
// 0xFF to get level for first supported alarm (v2 and higher)
//
// @param: event
// @default: 0
// Notification event to get level for
// This argument is ignored prior to Notification v3
// Must be 0 if type is 0xFF
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_alarm_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE type, ZWBYTE event, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Alarm Set (v2 and higher)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: type
// Type of alarm to set level for
//
// @param: level
// Level to set (0x0 = off, 0xFF = on, other values are reserved)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_alarm_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE type, ZWBYTE level, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class PowerLevel //

// Send PowerLevel Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_power_level_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send PowerLevel Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: level
// Power level to set (from 0 to 9)
//
// @param: timeout
// Timeout in seconds
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_power_level_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE level, ZWBYTE timeout, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send PowerLevel Test Node Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_power_level_test_node_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send PowerLevel Test Node Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: testNodeId
// Node to set test packets to
//
// @param: level
// Power level to use (from 0 to 9)
//
// @param: frameCount
// Number of test frames to send (from 1 to 65535)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_power_level_test_node_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE testNodeId, ZWBYTE level, int frameCount, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Command Class ZWavePlus Info //

// Send ZWave+ Info Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_zwave_plus_info_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Command Class Firmware Update //

// Send Firmware Metadata Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_firmware_update_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send Firmware Update Request Get
//
// On process start Z-Way sets fragmentCount:
//  devices.N.instances.0.commandClasses.122.data.fragmentCount = 3073 (0x00000c01)
// Then it asks the device to start the process. The device can refuse it (i.e. if local confirmation timed out).
// If confirmed, the device will send us a report with adjusted fragment size (if it wants Z-Way to send by smaller packets) and report "Ready" (updateStatus = 255, see below).
//  devices.N.instances.0.commandClasses.122.data.updateStatus = 255 (0x000000ff)
//  devices.N.instances.0.commandClasses.122.data.fragmentCount = 3277 (0x00000ccd)
// At this point fragmentTransmitted == 0
//  devices.N.instances.0.commandClasses.122.data.fragmentTransmitted =0
// Then device starts asking Z-Way for different packets. Z-Way will update fragmentTransmitted to allow track the process.
// Once done (fragmentCount == fragmentTransmitted), the device will send again a report if the flashing was successful. updateStatus contains the status: checksum error = 0, assemble error = 1, success, restart manually = 254, success, automatic restart = 255
// waitTime refers to the time device will take to reboot.
//  devices.N.instances.0.commandClasses.122.data.updateStatus = 255 (0x000000ff)
//  devices.N.instances.0.commandClasses.122.data.waitTime = 5 (0x00000005)
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: manufacturerId
// Manufacturer Id (2 bytes)
//
// @param: firmwareId
// Firmware Id (2 bytes)
//
// @param: firmwareTarget
// Firmware target number (0 for main chip, 1..255 for additional chips)
// Used only for CC v3 and above
//
// @param: length
// Size of firmware image
//
// @param: data
// Firmware image data in binary format (use hex2bin to convert from Intel Hex)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_firmware_update_perform(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, int manufacturerId, int firmwareId, ZWBYTE firmwareTarget, size_t length, const ZWBYTE *data, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Command Class Association Group Information //

// Send AGI Get Info
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: groupId
// Group Id to get info for (0 for all groups)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_group_information_get_info(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE groupId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send AGI Get Name
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: groupId
// Group Id to get info for (0 for all groups)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_group_information_get_name(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE groupId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send AGI Get Commands
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: groupId
// Group Id to get info for (0 for all groups)
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_association_group_information_get_commands(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE groupId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Command Class SwitchColor //

// Send SwitchColor Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: capabilityId
// Capability Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_color_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE capabilityId, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchColor Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: capabilityId
// Capability Id
//
// @param: state
// State to be set for the capability
//
// @param: duration
// @default: 0xff
// Duration of change:
//  0 instantly
//  0x01-0x7f in seconds
//  0x80-0xfe in minutes mapped to 1-127 (value 0x80=128 is 1 minute)
//  0xff use device factory default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_color_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE capabilityId, ZWBYTE state, ZWBYTE duration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchColor SetMultiple
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: length
// Size of capabilities/states arrays (up to 16)
//
// @param: capabilityIds
// Array of capabilities to set
//
// @param: states
// Array of state values to be set for the capabilities
//
// @param: duration
// @default: 0xff
// Duration of change:
//  0 instantly
//  0x01-0x7f in seconds
//  0x80-0xfe in minutes mapped to 1-127 (value 0x80=128 is 1 minute)
//  0xff use device factory default
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_color_set_multiple(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE length, const ZWBYTE * capabilityIds, const ZWBYTE * states, ZWBYTE duration, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchColor StartStateChange
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: capabilityId
// Capability Id to start changing state for
//
// @param: dir
// Direction of change: 0 to incrase, 1 to decrase
//
// @param: ignoreStartLevel
// @default: TRUE
// If set to True, device will ignore start level value and will use it's curent value
//
// @param: startLevel
// @default: 50
// Start level to change from
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_color_start_state_change(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE capabilityId, ZWBYTE dir, ZWBOOL ignoreStartLevel, ZWBYTE startLevel, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send SwitchColor StopStateChange
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: capabilityId
// Capability Id to stop changing state for
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_switch_color_stop_state_change(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE capabilityId,  ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);


// Command Class BarrierOperator //

// Send BarrierOperator Get
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_barrier_operator_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send BarrierOperator Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: state
// State to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_barrier_operator_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE state, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send BarrierOperator Signal Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: signalType
// Signal subsystem type to get state for
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_barrier_operator_signal_get(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE signalType, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

// Send BarrierOperator Signal Set
//
// @param: zway
// ZWay object instance
//
// @param: node_id
// Destination Node Id
//
// @param: instance_id
// Instance Id
//
// @param: signalType
// Signal subsystem type to set state for
//
// @param: state
// State to set
//
// @param: successCallback
// @default: NULL
// Custom function to be called on function success
// NULL if callback is not needed
//
// @param: failureCallback
// @default: NULL
// Custom function to be called on function failure
// NULL if callback is not needed
//
// @param: callbackArg
// Custom argument to be passed to custom function to be called on function success or failure
//
ZWEXPORT ZWError zway_cc_barrier_operator_signal_set(ZWay zway, ZWBYTE node_id, ZWBYTE instance_id, ZWBYTE signalType, ZWBYTE state, ZJobCustomCallback successCallback, ZJobCustomCallback failureCallback, void* callbackArg);

#endif
