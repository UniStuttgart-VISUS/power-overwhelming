# Measuring power using Tinkerforge Voltage/Current Bricklet 2.0
In the following, we provide additional lessons learned from our measurements of GPU energy consumption for our BELIV 2022 paper "Power Overwhelming: Quantifying the Energy Cost of Visualisation".

## Limited bandwidth
The bandwidth of the I2C bus used is limited. Several conclusions must be drawn from this fact:

1. Do not attach and enable *Tinkerforge Voltage/Current Bricklets* that do not provide relevant information for an experiment.
2. Measurements from bricklets attached to the bottommost master brick of the stack seem to produce more reliable samples.
3. Do not sample the bricklets more often than they acutally produce new data.

## Configuring the bricklets.
1. Make sure to reset all bricklets at the start of each measurment series. We found that asynchronous callbacks registered from previous measurements might still be active and waste valuable bandwidth if the previous run was not cleanly shut down. Performing a reset unconditionally ensures that the bricklets are in a constistent state every time.
