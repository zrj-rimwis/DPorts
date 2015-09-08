--- src/mesa/main/compiler.h.orig	2015-09-02 20:06:23.000000000 +0300
+++ src/mesa/main/compiler.h	2015-09-08 09:11:48.000000000 +0300
@@ -70,6 +70,9 @@ extern "C" {
 #if defined(__linux__)
 #include <byteswap.h>
 #define CPU_TO_LE32( x )	bswap_32( x )
+#elif defined(__FreeBSD__) || defined(__DragonFly__)
+#include <sys/endian.h>
+#define CPU_TO_LE32( x )	bswap32( x )
 #elif defined(__APPLE__)
 #include <CoreFoundation/CFByteOrder.h>
 #define CPU_TO_LE32( x )	CFSwapInt32HostToLittle( x )
