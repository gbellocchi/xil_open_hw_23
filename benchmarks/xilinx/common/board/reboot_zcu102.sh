# =====================================================================
# Title:        reboot_zcu102
# Description:  Reboot ZCU102 board.
# =====================================================================
#
# Copyright (C) 2022 University of Modena and Reggio Emilia.
#
# Author: Gianluca Bellocchi, University of Modena and Reggio Emilia.
#
# =====================================================================

#!/usr/bin/env bash

# reboot
ssh $HERO_TARGET_HOST /sbin/reboot