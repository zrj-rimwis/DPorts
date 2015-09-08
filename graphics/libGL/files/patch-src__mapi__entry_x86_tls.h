--- src/mapi/entry_x86_tls.h.orig	2015-09-02 20:06:23.000000000 +0300
+++ src/mapi/entry_x86_tls.h	2015-09-08 09:14:05.000000000 +0300
@@ -71,8 +71,8 @@ __asm__(".text");
 extern unsigned long
 x86_current_tls();
 
-static char x86_entry_start[];
-static char x86_entry_end[];
+extern char x86_entry_start[] __attribute__((visibility("hidden")));
+extern char x86_entry_end[] __attribute__((visibility("hidden")));
 
 void
 entry_patch_public(void)
