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
> Universität Stuttgart, VISUS and any person involved in this project do not make any warranty of the permissibility, safety and fitness for any purpose of the process described herein. We are not electrical engineers, and in no event shall we be liable for any claim, damages or other liability, arising from, out of or in connection with following the process described here. **You do that at your own risk!**

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
* Label printer. This is optional, but we recommend labelling the bricklets such that you easily know what is connected to them.
* Antistatic mat and/or antistatic wrist strap. We strongly recommend using this while working with expensive electronic parts.

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
* 1 &times; *[Tinkerforge Workbench (34 &times; 20 cm)](https://www.tinkerforge.com/en/shop/tinkerforge-workbench-34x20cm.html)*
* 15 &times; *[Tinkerforge Mounting Kit 12 mm](https://www.tinkerforge.com/en/shop/accessories/mounting/mounting-kit-12mm.html)*
* 1 m (or longer) USB-C to USB-C cable or USB-C to USB-A cable.

## Instructions
1. Assemble the bench table.

    Consult the manual of your bench table. Some tables come with bezels detached that must be screwed to the body before the computer components can be installed.
   
2. Assemble the computer on the bench table. Refer to the manual of your mainboard for detailed instructions. Typically, the following steps are necessary:
    1. Attach the mainboard to the bench table using the spacers provided with the mainboard.
    
        Nowadays, there is usually no need to install a back plate for the CPU fan, but you may want to check the manual of your fan whether it requires installation of one *before* the mainboard is screwed to the bench table.
        
    4. Mount the CPU in its socket.
    
        Consult the manual for instructions and make sure that the marker in one of the corner of the CPU and the marker on the socket match. The markers might be rather subtle.
        
    5. Install the CPU fan.
    
        Consult the manual for instructions. Some fans require special brackets to be installed on the mainboard. In any case, apply some heat paste (about the size of a pea), which should come with the fan, on the centre of the CPU before pressing the fan on it. Make sure to tighten the screws iteratively in alternating order.
        
        In some cases, the CPU is very close to the memory slots and a large CPU fan will make it difficult to reach the slots. You might want to install the memory before installing the fan in this case.
        
    6. Install the RAM modules.

        If you do not install a module in every slot, consult the manual which ones should be used.
        
    7. Install the hard disk.

        SATA disks are fairly easy to connect with the respective cables.
        
        M.2 SSDs might have a dedicated heat sink that must be removed from the mainboard before they can be installed. Consult the manual for instructions.
        
        On some mainboards, PCIe lanes are shared between M.2 SSDs and the PCIe slots. Consult the manual to find out which M.2 slot and which PCIe slot for the GPU you should used to avoid conflicts. You want to make sure that both can work with the full bandwidth available.
        
    8. Install the GPU.
    9. Install the power supply unit (PSU).

        On most bench table, the PSU is mounted on the bottom layer of the table below the mainboard.
        
3. Cut the ATX power cables.
    1. Identify the relevant pins on the cable, for instance using the manual of your mainboard or [Wikipedia](https://en.wikipedia.org/wiki/ATX#Power_supply). 
    
        Assuming the 24-pin ATX power supply connector, the pins are (i) four 3.3 V cables on pins 1, 2, 12 and 13, (ii) five 5 V cables on pins 4, 6, 21, 22 and 23 and (iii) two 12 V cables on pins 10 and 11.
        
    2. Cut the cables in two. The location does not matter much, but we recommend cutting about 50 mm from the connector attached to the mainboard for later accessibility of the cut.
        
    3. In order to identify the ends when putting them together later, you want to *immediately* tie the cables to each voltage together using cable tie on both sides of the cut and mark them with a unique colour (either shrink tubing or tape).

    4. Remove the insulation on both sides of the cut. 
    
        Consult the manual of your lever nuts or ferrules on how much of the insulation you need to remove. For the WAGO lever nuts we used, 11 mm are recommended.
    
    5. If you intend to solder the cables instead of using level nuts, add the ferrules to the end of the cables.
        
4. Cut the EPS P4/P8 CPU power cables.
    1. Consulte a trustworthy website with a diagram showing the pins on the cable, for instance on [TODO](http://127.0.0.1).

        For a 6-pin connector, there are two 12 V cables on pins 1 and 3 and two ground cables on pins 4 and 6. The 12 V pins should be on opposite side of the clamp that holds the connector in place.
        
        For an 8-pin connector, there are three 12 V cables on pins 1, 2 and 3 and three ground cables on pins 5, 7 and 8. The ground pins should be on the side of the clamp that holds the connector in place.
        
    2. Cut the cables in two. The location does not matter buch, but we recommend cutting about 50 mm from the connectors attached to the mainboard for later accessibility of the cut.
    
    3. In order to identify the ends when putting them together later, you want to *immediately* tie the cables to each voltage together using cable tie on both sides of the cut and mark them with a unique colour (either shrink tubing or tape).

    4. Remove the insulation on both sides ot the cut.
        
    5. If you intend to solder the cables instead of using level nuts, add the ferrules to the end of the cables.

6. Cut the PCIe power cables.
    1. Consulte a trustworthy website with a diagram showing the pins on the cable, for instance on [Wikipedia](https://en.wikipedia.org/wiki/PCI_Express#Power).

        For a 6-pin connector, there are two 12 V cables on pins 1 and 3 and two ground cables on pins 4 and 6. The 12 V pins should be on opposite side of the clamp that holds the connector in place.
        
        For an 8-pin connector, there are three 12 V cables on pins 1, 2 and 3 and three ground cables on pins 5, 7 and 8. The ground pins should be on the side of the clamp that holds the connector in place.
        
    2. Cut the cables in two. The location does not matter buch, but we recommend cutting about 50 mm from the connectors attached to the GPU for later accessibility of the cut.
    
    3. In order to identify the ends when putting them together later, you want to *immediately* tie the cables to each voltage together using cable tie on both sides of the cut and mark them with a unique colour (either shrink tubing or tape).

    4. Remove the insulation on both sides ot the cut.
        
    5. If you intend to solder the cables instead of using level nuts, add the ferrules to the end of the cables.
