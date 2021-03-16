# gxmdbg_r

#### This plugin is intended only for developers!

Use debug GXM module on retail PS Vita.
Debug GXM module will be loaded for all game and VSH applications.
Tested on 3.60 and 3.65

# Usage
Grab vs0/sys/external/libgxm_dbg_es4.suprx from TOOL firmware corresponding to your current firmware version and put it in ux0:data/external.
If debug module is not found, normal GXM module will be loaded instead.

- Path to debug module can be changed in source code
- Debug module is not loaded as shared unlike normal GXM module
- It is not recommended to use debug GXM module when testing for performance

# Building

Use https://github.com/Vita-Development-Suite
