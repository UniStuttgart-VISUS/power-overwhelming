# Building a bench table for measuring GPU power consumption
In the following, we provide instructions for building a power measurement setup to be used with the library, mainly based on [Tinkerforge](https://github.com/Tinkerforge) bricklets. The setup was used for our BELIV 2022 paper "Power Overwhelming: Quantifying the Energy Cost of Visualisation".

## Disclaimer
> **Warning**
> The procedure below involves manipulating current-carrying cables in your computer!

> **Warning**
> Do not proceed if you do not have the appropriate education and/or knowledge to perform or feel uncomfortable in performing the steps described here! Special training might be required in your country in order to be allowed to perform such modifications.

> **Warning**
> The modifications described in the following will **invalidate the warranty** on the components and render them useless for normal operations.

> **Warning**
> Universität Stuttgart, VISUS and any person involved in this project do not make any warranty of the permissibility, safety and fitness for any purpose of the process described herein. In no event shall they be liable for any claim, damages or other liability, arising from, out of or in connection with following the process described here. **You do that at your own risk!**

## Parts and special tools
> **Note**
> Mentioning of specific products in this guide does not constitute an endorsement of said products by Universität Stuttgart, VISUS or any person involved in this project. We are mentioning these only for your convenience and as a reference for the specific setup we built. However, other products might be similarly or better suitable for the purpose. We do not receive any commission for any of the products mentioned.

### Tools
* Soldering station
* Solder with flux
* Screwdrivers
* Side-cutting pliers
* 3D printer
* Cable stripper, e.g. *Knipex 12 40 2000.* In principle, this is optional, but you will need to strip a lot of cables, so this is highly recommended.
* Heat gun, e.g. *Bosch GHG 20-63 Professional.* This is also optional, but if you want to use shrink tubing to insulate and mark cables, you need one.
* Crimp tong. This is optional and only required if you intend to solder the connections instead of clamping them together. Due to the large number of connections, we strongly advise against soldering them.

### PC components
* Bench table, e.g. *Lian Li PC-T70X.* You will need an open bench table, because after installing the riser card, the GPU will not fit into a PC chassis anymore.
* Power supply unit, e.g. *BeQuiet Dark Power Pro P12 1200W.* We recommend using a modular PSU for which you can purchase the PC-side cables individually such that you can try again if you made a mistake.
* PCI Express riser, e.g. *[Adex Electronics PEX16IX](http://www.adexelec.com/pex16ix).* Make sure to choose a riser that has probing/soldering points for the power lanes. You need to be able to bypass the internal power lanes of the riser and replace these with cables running through the power sensors.
* Mainboard, e.g. *ASUS ROG Strix X570-E Gaming*
* CPU, e.g. *AMD Ryzen 9 5900X*
* CPU fan, e.g. *BeQuiet Pure Rock Slim 2*
* RAM, e.g. *Crucial Ballistix Black 64GB PC3200 CL16 kit*
* Hard disk/SSD, e.g. *Samsung 980 PRO 500 GB*
* GPUs to test

### Parts
* 20 m litz wire with 1.5 mm² cross section. We recommend having half in red and half in blue/black. Depending on the placement of the components, you might need more or less wire. However, you should aim at keeping it as short as possible.
* ??? m litz wire with 2.5 mm² cross section. Again, we recommend having half in red and half in blue/black.
* 60 &times; wire connectors for wires with a cross section of up to 1.5 mm², e.g. *WAGO 221-2411.* Due to the large number of connections, we strongly recommend using revisable wire connectors instead of soldering them.
* 25 &times; 5-conductor lever nuts for wires with a cross section of up to 2.5 mm², e.g. *WAGO 221-415.*
* ??? &times; ferrule. This is only required if you intend to solder the connections. Due to the large number of connections, we strongly advise against soldering them.
* Cable tie. While optional, it facilitates the setup if you can tie wires that belong together.
* Shrink tubing in different colours. This is required to mark the wires you have cut such that you know which ones need to be connected. Alternatively, you can also use tape for that.
* Electrical tape in different colours. This is required to mark the wires you have cut sucht that you know which ones need to be connected. Alternatively, you can also use coloured shrink tubing.
* 3 &times; *[Tinkerforge Master Brick 3.1](https://www.tinkerforge.com/en/shop/master-brick.html)*
* 12 &times; *[Tinkerforge Voltage/Current Bricklet 2.0](https://www.tinkerforge.com/en/shop/voltage-current-v2-bricklet.html)*
* 12 &times; *[Tinkerforge Bricklet Cable 50 cm (7p-7p)](https://www.tinkerforge.com/en/shop/bricklet-cable-50cm-7p-7p.html)*
* 1 &times; *[Tinkerforge Workbench (34 &times; 20 cm](https://www.tinkerforge.com/en/shop/tinkerforge-workbench-34x20cm.html)*
* 1 m (or longer) USB-C to USB-C cable or USB-C to USB-A cable.

## Instructions
