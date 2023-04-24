# pwrowgrapldrv.sys
## What is this and what is it good for?
`pwrowgrapldrv.sys` is a Windows kernel-mode driver for reading model-specific registers (MSRs) providing running average power limit (RAPL) data. These registers are available on most AMD Zen CPUs and Intel Tiger Lake and above and provide the ability to query the energy consumption of the whole CPU package and of individual cores, sometimes including on-board GPUs and DRAM.

Unfortunately, the [`__readmsr` instruction](https://learn.microsoft.com/en-us/cpp/intrinsics/readmsr) is only available on ring 0 aka in kernel mode, i.e. our sensors cannot issue it directly. This driver, which runs in kernel mode, gives our sensors the ability to read the registers.

> **Note**
> Starting with Windows 11 and on [select Surface models running Windows 10](https://fosdem.org/2023/schedule/event/energy_power_profiling_firefox/attachments/slides/5537/export/events/attachments/energy_power_profiling_firefox/slides/5537/FOSDEM_2023_Power_profiling_with_the_Firefox_Profiler.pdf), Microsoft provides built-in support for reading the MSRs by means of the [Energy Meter Interface](https://learn.microsoft.com/en-us/windows-hardware/drivers/powermeter/energy-meter-interface). If you are on a supported device or on Windows 11, you should therefore use the `emi_sensor` instead of the `msr_sensor`, which is backed by this driver, due to the restrictions of the latter approach described below.
