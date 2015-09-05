--- lib/intel_os.c.orig	2015-09-05 14:22:30.000000000 +0300
+++ lib/igt_kms.c
@@ -37,6 +37,8 @@
 #include <linux/kd.h>
 #elif HAVE_SYS_KD_H
 #include <sys/kd.h>
+#elif defined(__DragonFly__)
+#include <sys/consio.h>
 #endif
 #include <errno.h>
 #include <time.h>
