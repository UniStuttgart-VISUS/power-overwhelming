# pwrowgrapldrv.sys
## What is this and what is it good for?
`pwrowgrapldrv.sys` is a Windows kernel-mode driver for reading model-specific registers (MSRs) providing running average power limit (RAPL) data. These registers are available on most AMD Zen CPUs and Intel Tiger Lake and above and provide the ability to query the energy consumption of the whole CPU package and of individual cores, sometimes including on-board GPUs and DRAM.

Unfortunately, the [`__readmsr` instruction](https://learn.microsoft.com/en-us/cpp/intrinsics/readmsr) is only available on ring 0 aka in kernel mode, i.e. our sensors cannot issue it directly. This driver, which runs in kernel mode, gives our sensors the ability to read the registers.

> **Note**
> Starting with Windows 11 and on [select Surface models running Windows 10](https://fosdem.org/2023/schedule/event/energy_power_profiling_firefox/attachments/slides/5537/export/events/attachments/energy_power_profiling_firefox/slides/5537/FOSDEM_2023_Power_profiling_with_the_Firefox_Profiler.pdf), Microsoft provides built-in support for reading the MSRs by means of the [Energy Meter Interface](https://learn.microsoft.com/en-us/windows-hardware/drivers/powermeter/energy-meter-interface). If you are on a supported device or on Windows 11, you should therefore use the `emi_sensor` instead of the `msr_sensor`, which is backed by this driver, due to the restrictions of the latter approach described below.

There is [another open-source project providing a similar driver](https://github.com/hubblo-org/windows-rapl-driver), which we found, however, not suitable for our software for two main reasons:

1. For reasons unbeknwonst to us, the authors decided to implement access to the MSRs by means of `IRP_MJ_DEVICE_CONTROL` (an I/O control request) instead of `IRP_MJ_READ` (reading a file). This is disadvantageous for `msr_sensor`, because the Linux implementation of this sensor reads the MSR files in `/dev/cpu/XXX/msr` and we therefore prefer a similar interface on Windows 10, thus avoiding two completely diverging implementations.

2. The `__readmsr` instruction reads the register of the core the calling thread is running on, i.e. the thread affinity of the code reading the register must be set to the logical CPU we are interested in. The aforementioned driver does not ensure that in kernel mode, i.e. the user-mode sensor thread must be bound to the correct core for this to work. This is error-prone and we again want to have a path-based solution like in the Linux kernel to have a similar implementation of the sensor on both platforms.
