# jp81f

![jp81f](https://i.imgur.com/2nig7JA.jpeg)

*This is standard Japanese layout keyboard.*

* Keyboard Maintainer: [alektor_diy](https://github.com/sasami.mc41@gmail.com)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *in preparation*

Make example for this keyboard (after setting up your build environment):

    make jp81f:via

Flashing example for this keyboard:

    make jp81f:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
