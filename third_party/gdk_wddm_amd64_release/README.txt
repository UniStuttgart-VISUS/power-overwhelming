--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
GPU Deployment Kit
README
Version v332.85

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
March 2014
Copyright (C) 2014 NVIDIA Corp.


Description
--------------------------
The GPU Deployment Package (GDK) is a set of tools provided primarily for the
NVIDIA(R) Tesla(TM), GRID(TM) and Quadro(TM)  range of GPUs. They aim to empower 
users to better manage their NVIDIA GPUs by providing a broad range of 
functionalities. This distribution contains:

1. NVML v332.85
: The NVIDIA Management Library (NVML) is a C-based API
                for monitoring and managing various states of the NVIDIA GPU 
                devices. It provides a direct access to the queries and commands
                exposed via nvidia-smi. The runtime version of NVML ships with 
                the NVIDIA display driver, and the SDK provides the appropriate 
                header, stub libraries and sample applications. Each new version 
                of NVML is backwards compatible and is intended to be a platform 
                for building 3rd party applications.

                http://developer.nvidia.com/nvidia-management-library-nvml

In Linux package:

2. nvidia-heathmon v332.85
: The system administrator's and cluster 
                manager's tool for detecting and troubleshooting common problems
                affecting NVIDIA Tesla GPUs in a high performance computing
                environment. nvidia-healthmon contains limited hardware 
                diagnostic capabilities, and focuses on software and system 
                configuration issues.


Changelog
--------------------------
v1.285: Initial release

For additional component changelogs, please refer to their individual 
documentation. This release is supported by NVIDIA display drivers version 285 
and later.

--------------------------
v2.295.1: CUDA 4.2 aligned release

Updates for the NVML r3.295 API
This release is supported by NVIDIA display drivers version 295 and later.

--------------------------
v2.295.2: Documentation updates

Updated some documentation for clarity
This release is supported by NVIDIA display drivers version 295 and later.

--------------------------
v3.304.4: CUDA 5.0 aligned release

Updates for the NVML r3.304 API
Added nvidia-healthmon utility to Linux GDK package
This release is supported by NVIDIA display drivers version 304.46 and later.
--------------------------

v5.319.43: CUDA 5.5 aligned release

Updates for the NVML r5.319 API
This release is supported by NVIDIA display drivers version 319.43 and later.
--------------------------

v6.331: CUDA 6.0 aligned release

Updates for the NVML r6.331 API
This release is supported by NVIDIA display drivers version 331 and later.

More information
--------------------------
For more information, please visit 
http://developer.nvidia.com/gpu-deployment-kit

