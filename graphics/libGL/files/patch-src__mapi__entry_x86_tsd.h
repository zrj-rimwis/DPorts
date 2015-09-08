--- src/mapi/entry_x86_tsd.h.orig	2015-09-02 20:06:23.000000000 +0300
+++ src/mapi/entry_x86_tsd.h	2015-09-08 09:13:29.000000000 +0300
@@ -58,8 +58,8 @@ __asm__(".balign 32\n"
 #include <string.h>
 #include "u_execmem.h"
 
-static const char x86_entry_start[];
-static const char x86_entry_end[];
+extern const char x86_entry_start[] __attribute__((visibility("hidden")));
+extern const char x86_entry_end[] __attribute__((visibility("hidden")));
 
 void
 entry_patch_public(void)
