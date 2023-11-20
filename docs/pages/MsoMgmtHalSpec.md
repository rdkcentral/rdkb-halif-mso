# MsoMgmt HAL Documentation

## Acronyms

- `HAL` \- Hardware Abstraction Layer
- `RDK-B` \- Reference Design Kit for Broadband Devices
- `OEM` \- Original Equipment Manufacture

## Description

The below diagram describes the high-level software architecture of the MsoMgmt HAL module stack.

![MsoMgmt HAL Architecture Diag](images/MsoMgmt_HAL_Architecture.png)

MsoMgmt HAL is an abstraction layer implemented to interact with vendor software to set or get information about PoD seed for MSO password validation.

## Component Runtime Execution Requirements

### Initialization and Startup

There are no dependent APIs expected to be initialized for invoking the MsoMgmt HAL client module.

RDK MsoMgmt HAL doesn't mandate any predefined requirements for the implementation of these APIs. It is up to the
3rd party vendors to handle it appropriately to meet operational requirements.

Independent API's 3rd party implementation is expected to work without any prerequisites.

Failure to meet these requirements will likely result in undefined and unexpected behavior.

## Threading Model

The interface is not thread safe.

Any module that invokes the API should ensure calls are made in a thread-safe manner.

Different 3rd party vendors are allowed to create internal threads to meet the operational requirements. In this case, 3rd party implementations should be responsible for synchronizing between the calls and events and cleaning up the thread.

## Process Model

All APIs are expected to be called from multiple processes.

## Memory Model

The client is responsible for allocating and de-allocating memory for necessary APIs as specified in API documentation.

Different 3rd party vendors are allowed to allocate memory for internal operational requirements. In this case, 3rd party implementations should be responsible for de-allocating memory internally.

## Power Management Requirements

The HAL is not involved in any of the power management operations.

Any power management state transitions MUST not affect the operation of the HAL.

## Asynchronous Notification Model

There are no asynchronous notifications.

## Blocking calls

The API's are expected to work synchronously and should complete within a time period commensurate with the complexity of the operation and in accordance with any relevant specification.

Any calls that can fail due to the lack of a response should have a timeout period in accordance with any API documentation.

## Internal Error Handling

All the MsoMgmt HAL APIs should return errors synchronously as a return argument. HAL is responsible for handling system errors (e.g., out of memory) internally.

## Persistence Model

There is no requirement for HAL to persist any setting information. The caller is responsible for persisting any settings related to their implementation.

## Nonfunctional requirements

Following non functional requirement should be supported by the component.

## Logging and debugging requirements

The component should log all the errors and critical informative messages, which helps to debug or triage the issues and understand the functional flow of the system.

The logging should be consistent across all HAL components.

If the vendor is going to log, then it has to be logged in the `xxx_vendor_hal.log` file name.

Logging should be defined with log levels as per Linux standard logging.

## Memory and performance requirements

The component should not contribute more to memory and CPU utilization while performing normal operations and should be commensurate with the operation required.

## Quality Control

MsoMgmt HAL implementation should pass `Coverity`, `Black duck`, `Valgrind` checks without any issue.

There should not be any memory leaks or corruption introduced by HAL and underneath 3rd party software implementation.

## Licensing

MsoMgmt HAL implementation is expected to be released under the Apache License 2.0.

## Build Requirements

The source code should be built under the Linux Yocto environment and delivered as a shared library named `libhal_msomgmt.so`

## Variability Management

Any new API introduced should be implemented by all the 3rd party modules, and RDK generic code should be compatible with specific versions of HAL software.

Each API interface will be versioned using [Semantic Versioning 2.0.0](https://semver.org/), the vendor code will comply with a specific version of the interface.

## Platform or Product Customization

None

## Interface API Documentation

All HAL function prototypes and datatype definitions are available in `mso_mgmt_hal.h` file.

1. Components/Process must include `mso_mgmt_hal.h` to make use of MsoMgmt hal capabilities.
2. Components/Process should add linker dependency for `libhal_msomgmt.so`

## Theory of operation and key concepts

Covered as per "Description" sections in the API documentation.

## Sequence Diagram

```mermaid
sequenceDiagram
title MsoMgmt HAL Sequence Diagram
participant Caller
participant MsoMgmt HAL
participant Vendor
Caller->>MsoMgmt HAL: mso_validatepwd()
MsoMgmt HAL->>Vendor: 
Vendor ->>MsoMgmt HAL: 
MsoMgmt HAL->>Caller: mso_validatepwd() return

Caller->>MsoMgmt HAL: mso_get_pod_seed()
MsoMgmt HAL->>Vendor: 
Vendor ->>MsoMgmt HAL: 
MsoMgmt HAL->>Caller: mso_get_pod_seed() return

Caller->>MsoMgmt HAL: mso_set_pod_seed()
MsoMgmt HAL->>Vendor: 
Vendor ->>MsoMgmt HAL: 
MsoMgmt HAL->>Caller: mso_set_pod_seed() return
```
