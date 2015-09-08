--- src/mesa/x86/common_x86.c.orig	2015-09-02 20:06:23.000000000 +0300
+++ src/mesa/x86/common_x86.c	2015-09-08 08:58:13.000000000 +0300
@@ -38,7 +38,7 @@
 #if defined(USE_SSE_ASM) && defined(__linux__)
 #include <linux/version.h>
 #endif
-#if defined(USE_SSE_ASM) && defined(__FreeBSD__)
+#if defined(USE_SSE_ASM) && (defined(__FreeBSD__) || defined(__DragonFly__))
 #include <sys/types.h>
 #include <sys/sysctl.h>
 #endif
@@ -128,7 +128,7 @@ static LONG WINAPI ExceptionFilter(LPEXC
  */
 void _mesa_check_os_sse_support( void )
 {
-#if defined(__FreeBSD__)
+#if defined(__FreeBSD__) || defined(__DragonFly__)
    {
       int ret, enabled;
       unsigned int len;
