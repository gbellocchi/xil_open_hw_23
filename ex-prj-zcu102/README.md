

# ZCU102 Project Example
We provide a pre-built ZCU102 image where an FPGA overlay integrating a MatMul accelerator is deployed on the PL.

### SD card
Insert the SD card of the ZCU102 into your development workstation and

1. Initialize the SD card with a master boot record (MBR, also known as "DOS partition table") and create two partitions:
   1. FAT32 (`0xc`), 256 MiB, bootable
   2. Linux (`0x83`), remaining space
2. Format the first partition with `vfat` and the second partition with `ext4`.
3. Mount the first partition, copy `BOOT.BIN` and `image.ub` from `$XIL_OPENHW_PATH/ex-prj-zcu102/zcu102-images` to the mounted partition, and unmount it.

The system can then be booted up after configuring the ZCU102 board jumpers to boot from the SD card. 

### Serial terminal
Plug a USB cable into the USB-UART port of the board, connect it to your workstation, and configure a serial terminal of your choice (such as `minicom` or `screen`) to access it.  Once Linux has booted, you can log in as `root` on the serial terminal without a password.

### U-boot modification on first boot
On the first boot, modify the U-Boot environment.
 
Open the serial terminal, power the ZCU102 board, and abort the automatic boot
process by pressing any key.  

Modify the uBoot environment as follows (executing one `env set` per item):
- `boot_img=boot.bin`
- `boot_targets=mmc0`
- `bootcmd=run default_bootcmd`
- `bootenvstart=0x100000`
- `bootenvsize=0x40000`
- `clobstart=0x10000000`
- `console=ttyPS0,115200`
- `cp_kernel2ram=mmcinfo && fatload mmc 0 ${netstart} ${kernel_img}`
- `default_bootcmd=run cp_kernel2ram && bootm ${netstart}`
- `kernel_img=image.ub`
- `loadaddr=0x10000000`
- `netstart=0x10000000`
- `psserial0=setenv stdout ttyPS0;setenv stdin ttyPS0`
- `serial=setenv stdout serial; setenv stdin serial`
- `stderr=serial@ff000000`
- `stdin=serial@ff000000`
- `stdout=serial@ff000000`

Remove any other environment variables with the `env delete` command. (All defined variables can be listed with `env print -a`.)

When done, save the environment with `env save`, and finally reboot with `reset`.

The U-Boot environment hardcoded in PetaLinux should be modified to provide the values listed above.  Here are two articles that could help to achieve this:
- https://www.xilinx.com/support/answers/69780.html
- https://www.fpgadeveloper.com/how-to-modify-u-boot-environment-variables-in-petalinux/

### SSH access
To set up SSH access to the board:
1. set the password for the `root` user with `passwd`;
2. allow the `root` user to log in via SSH by removing `-w` from `DROPBEAR_EXTRA_ARGS` in `/etc/default/dropbear`; and
3. restart the `dropbear` SSH server with `/etc/init.d/dropbear restart`.

If your board is connected to an Ethernet network and has been able to obtain an IP address via DHCP (check with `ip addr`), you should now be able to log in to the board with `ssh root@<board-ip>` using the password you set.  If you reboot the board, you have to repeat those settings because you made them in the memory-backed root filesystem.  In the next step, we will set up a persistent filesystem.

### Persistent filesystem
The root filesystem mounted after boot is provided by PetaLinux.  It is loaded into memory during boot, and changes are not persisted to the SD card.  

A persistent filesystem resides on the second partition of the SD card.  Linux will mount that partition at `/run/media/mmcblk0p2` during boot.  

A provided script runs during boot and mounts
- `/run/media/mmcblk0p2/home` at `/home` to persist user data, and
- `/run/media/mmcblk0p2/etc/dropbear` at `/etc/dropbear` to persist SSH host keys.

Create those two directories on the SD card and manually mount them this time.  Then create the directory `/home/root/startup_scripts`.  Any executable placed in this directory will be run during boot (in alphanumeric order).  You can use this feature to make the SSH access setup permanent by creating two files:
```sh
cat > /home/root/startup_scripts/00_set_root_password << EOT
#!/bin/sh
echo "root:password_you_define" | chpasswd
EOT
cat > /home/root/startup_scripts/01_dropbear_allow_root_login << EOT
#!/bin/sh
sed -i -e 's/DROPBEAR_EXTRA_ARGS="-w"/DROPBEAR_EXTRA_ARGS=""/' /etc/default/dropbear
EOT
chmod +x /home/root/startup_scripts/*
```

### PULP kernel module
Communicating with the PULP accelerator requires loading the Linux kernel driver for PULP.  

To do so, run
```sh
insmod /run/media/mmcblk0p2/lib/modules/4.19.0/extra/pulp.ko
```
after every reboot.  

The kernel messages on the serial terminal will inform you about the outcome (it should end with `PULP: Device registered.` if successful).

### Install accelerator libraries
```
ssh $HERO_TARGET_HOST "mkdir -p /home/root/workspace_xil_open_hw_23/libs"
scp $XIL_OPENHW_PATH/ex-prj-zcu102/sw/libs/* $HERO_TARGET_HOST:/home/root/workspace_xil_open_hw_23/libs
```

### Heterogeneous application environment
To enable the dynamic linker to find the required libraries, run
```sh
export LD_LIBRARY_PATH=/run/media/mmcblk0p2/usr/lib:/run/media/mmcblk0p2/lib:/home/root/workspace_xil_open_hw_23/libs
```
in every session on the board.

### Deploy heterogeneous application
Afterwards applications can be transferred to the board with:
```
scp $XIL_OPENHW_PATH/ex-prj-zcu102/sw/app/SW-xil-open-hw-23 $HERO_TARGET_HOST:/home/root/workspace_xil_open_hw_23
```

### Run heterogeneous application
Connect to the board and run the deployed application:
```
/home/root/workspace_xil_open_hw_23/SW-xil-open-hw-23
```
