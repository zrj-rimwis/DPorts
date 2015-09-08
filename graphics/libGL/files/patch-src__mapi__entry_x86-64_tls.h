--- src/mapi/entry_x86-64_tls.h.orig	2015-09-06 19:54:50.000000000 +0300
+++ src/mapi/entry_x86-64_tls.h	2015-09-08 09:14:37.000000000 +0300
@@ -61,8 +61,8 @@ entry_patch_public(void)
 {
 }
 
-static char
-x86_64_entry_start[];
+extern char
+x86_64_entry_start[] __attribute__((visibility("hidden")));
 
 mapi_func
 entry_get_public(int slot)
