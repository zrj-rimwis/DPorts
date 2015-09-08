--- src/gallium/auxiliary/util/u_cpu_detect.c.orig	2015-09-05 01:09:37.000000000 +0300
+++ src/gallium/auxiliary/util/u_cpu_detect.c	2015-09-08 08:59:38.000000000 +0300
@@ -52,7 +52,7 @@
 #include <machine/cpu.h>
 #endif
 
-#if defined(PIPE_OS_FREEBSD)
+#if defined(PIPE_OS_FREEBSD) || defined(PIPE_OS_DRAGONFLY)
 #include <sys/types.h>
 #include <sys/sysctl.h>
 #endif
