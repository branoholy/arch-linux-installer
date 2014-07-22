Arch Linux Installer
====================

archlinux-installer
--------------------
*Unofficial installer for Arch Linux using config file.*

`archlinux-installer` installs clean and minimal Arch Linux installation 
on whole disk. It supports BIOS/EFI and encrypted LVM.

Download
--------
You can download source code and build `archlinux-installer` according to 
[build instruction](#build) below or download binaries from 
[Releases](https://github.com/branoholy/archlinux-installer/releases) page.

Usage
-----
1. Boot Arch Linux installation [image](https://www.archlinux.org/download/) 
(you can use [archlinux-usb-creator](https://github.com/branoholy/archlinux-usb-creator) 
to create bootable USB).

2. Download binary from [Releases](https://github.com/branoholy/archlinux-installer/releases) 
page or [build](#build) your own binary.

3. Edit [config](#config) file as you need 
(you may omit this step if you will specify options as command line arguments).

4. Run `archlinux-installer`.

```bash
$ ./archlinux-installer [options] [<config-path>]
```

### Config
Config files are using INI-like syntax (see [examples](https://github.com/branoholy/archlinux-installer/tree/master/examples)).

To show all possible options, simply run `archlinux-installer` without options.

Dependencies
------------
There are no dependencies for running binary release (all libraries are linked 
statically). Dependencies are necessary only for building.

`archlinux-installer` is using:

* [Boost.Program_options](http://www.boost.org/doc/libs/release/doc/html/program_options.html) 
library (version 1.53 or newer).

Build
-----
Make sure you have installed all [dependencies](#dependencies) before building.

```bash
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

For faster build on multicore processor, you can use:

```bash
$ cmake --build . -- -j4
```

Where option `-j4` means you want to use 4 cores for building.

Examples
--------
Run `archlinux-installer` with config file:
```bash
$ ./archlinux-installer path/to/config.conf
```

Run `archlinux-installer` with command line arguments:
```bash
$ ./archlinux-installer --disk-device /dev/sda --locales "en_US.UTF-8 UTF-8" --lang en_US --hostname my-arch --timezone Europe/Prague
```

License
-------
Arch Linux Installer is licensed under GNU GPL v3 (see 
[COPYING](https://github.com/branoholy/archlinux-installer/blob/master/COPYING) 
file).

