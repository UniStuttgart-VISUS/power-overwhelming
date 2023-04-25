# pwrowgrapldrv.sys
## What is this and what is it good for?
`pwrowgrapldrv.sys` is a Windows kernel-mode driver for reading model-specific registers (MSRs) providing running average power limit (RAPL) data. These registers are available on most AMD Zen CPUs and Intel Tiger Lake and above and provide the ability to query the energy consumption of the whole CPU package and of individual cores, sometimes including on-board GPUs and DRAM.

Unfortunately, the [`__readmsr` instruction](https://learn.microsoft.com/en-us/cpp/intrinsics/readmsr) is only available on ring 0 aka in kernel mode, i.e. our sensors cannot issue it directly. This driver, which runs in kernel mode, gives our sensors the ability to read the registers.

> **Note**
> Starting with Windows 11 and on [select Surface models running Windows 10](https://fosdem.org/2023/schedule/event/energy_power_profiling_firefox/attachments/slides/5537/export/events/attachments/energy_power_profiling_firefox/slides/5537/FOSDEM_2023_Power_profiling_with_the_Firefox_Profiler.pdf), Microsoft provides built-in support for reading the MSRs by means of the [Energy Meter Interface](https://learn.microsoft.com/en-us/windows-hardware/drivers/powermeter/energy-meter-interface). If you are on a supported device or on Windows 11, you should therefore use the `emi_sensor` instead of the `msr_sensor`, which is backed by this driver, due to the restrictions of the latter approach described below.

There is [another open-source project providing a similar driver](https://github.com/hubblo-org/windows-rapl-driver), which we found, however, not suitable for our software for two main reasons:

1. For reasons unbeknwonst to us, the authors decided to implement access to the MSRs by means of `IRP_MJ_DEVICE_CONTROL` (an I/O control request) instead of `IRP_MJ_READ` (reading a file). This is disadvantageous for `msr_sensor`, because the Linux implementation of this sensor reads the MSR files in `/dev/cpu/XXX/msr` and we therefore prefer a similar interface on Windows 10, thus avoiding two completely diverging implementations.

2. The `__readmsr` instruction reads the register of the core the calling thread is running on, i.e. the thread affinity of the code reading the register must be set to the logical CPU we are interested in. The aforementioned driver does not ensure that in kernel mode, i.e. the user-mode sensor thread must be bound to the correct core for this to work. This is error-prone and we again want to have a path-based solution like in the Linux kernel to have a similar implementation of the sensor on both platforms.

This driver offers a behaviour that is very close to the behaviour of the `msr` device files on Linux, most notably (i) it allows for opening individual cores for which the driver handles thread affinity by itself, (ii) it uses `IRP_MJ_READ` for delivering the data and (iii) it uses the position of the file pointer as the address of the machine-specific register to return.

## Build
In order to build the driver, the [Windows Driver Kit (WDK)](https://learn.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk) must be installed on the machine. We have a [CMake find](https://github.com/SergiusTheBest/FindWDK) in place that should detect the installation automatically.

> **Note**
> The CMake build process will automatically choose the latest version of the driver kit, so make sure that this version can build drivers supported on your target machine.

You must enable building the driver using the `PWROWG_BuildDriver` option, which is disabled by default. If enabled, the driver will be built and all files required to install it will be generated in or copied to the binary directory. These files include
* the driver binary `pwrowgrapldrv.sys`
* the INF file configuring the installation
* the catalogue file for test-signing the driver
* the binary of the KMDF co-installer.

## Installation
### Preparing the target machine
The driver is not WHQL-signed (you just built it yourself) and for this being a research project, we have no plans for providing a signed driver. Therefore, the target machine needs to be configured to allow unsafe drivers. In an elevated command prompt, run
```cmd
bcdedit -set TESTSIGNING ON
```

You should be able to install and run the driver if you [test sign the catalogue](https://learn.microsoft.com/en-us/windows-hardware/drivers/install/introduction-to-test-signing). The main steps for test-signing are:

1. Creating a certificate with [EKU 1.3.6.1.5.5.7.3.3](https://oidref.com/1.3.6.1.5.5.7.3.3), e.g.
```cmd
makecert -r -pe -ss PrivateCertStore -n CN="Power Overwhelming (Test)" -eku 1.3.6.1.5.5.7.3.3 pwrowgrapldrv.cer
```
2. Creating a catalogue file using [Inf2Cat](https://learn.microsoft.com/en-us/windows-hardware/drivers/devtest/inf2cat). This happens automatically as post-build step when building the driver using the provided build process.
3. Test-signing the catalogue with [signtool](https://learn.microsoft.com/en-us/windows-hardware/drivers/install/test-signing-a-driver-package-s-catalog-file) from the WDK, e.g.
```cmd
signtool sign /v /fd sha256 /s PrivateCertStore /n "Power Overwhelming (Test)" /t http://timestamp.digicert.com pwrowgrapldrv.cat
```

`makecert` and `signtool` are distributed with the WDK, at time of writing in the `<WDKROOT>\bin\x64` directory.

If you do not want to sign the driver, you must disable driver integrity checks completely. This can be achieved by issuing
```cmd
bcdedit -set loadoptions DISABLE_INTEGRITY_CHECKS
```
in an elevated command prompt.

> **Warning**
> All of the above will make your machine susceptible to malicious software. Make sure to revert the changes if you need the driver anymore.

### Installation of the driver
1. Copy all files (the driver binary, the WDF binary, the INF file and the catalogue file) to the target machine.
2. Open Device Manager.
3. Select the root node of the device tree (the one with the computer name).
4. From the Action menu, choose adding legacy hardware.
5. Continue and select that you want to add hardware from a list (the one that is not recommended).
6. Continue showing all devices.
7. Select the button for custom driver sources and navigate to the folder where you put the files from step 1.
8. Continue and confirm that you want to install the driver even if it is not digitally signed.
9. Finish the installation and check that the RAPL registers show up under the system devices.
10. Reboot the target machine.

## Usage
The `visus::power_overwhelming::msr_sensor` will detect the presence of the driver by itself and provide access to RAPL data.

If you want to use it by yourself, you just need to
1. ppen a file handle for `\\.\PowerOverwhelmingRaplMsrs\<core>` where `<core>` is the zero-based index of the logical CPU you want to query;
2. seek to the position of the register. This is dependent on the hardware. You can find the registers we know of in [RaplMsr.cpp](RaplMsr.cpp);
3. read a single `std::uint64_t` from this address.

Please be aware that the RAPL MSRs typically do not provide data that are directly usable, but they must be transformed into a commonly used quantity by applying a divisor that can be read using the driver, too.

## Debugging the driver
1. [Setup the Kernel debugger](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/debug-universal-drivers---step-by-step-lab--echo-kernel-mode-)
2. Make the operating system break on startup: Select "Toggle Initial Break" in the Breakpoints menu.
3. Reboot the target machine.
4. Enable debug outputs for everything once the system breaks: `ed nt!Kd_DEFAULT_MASK 0xFFFFFFFF`
4. Continue with: `g`
