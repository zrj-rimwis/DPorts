--- src/egl/drivers/dri2/platform_wayland.c.orig	2015-10-03 14:30:41.000000000 +0300
+++ src/egl/drivers/dri2/platform_wayland.c
@@ -32,6 +32,8 @@
 #include <string.h>
 #include <limits.h>
 #include <dlfcn.h>
+#include <sys/types.h>
+#include <sys/stat.h>
 #include <errno.h>
 #include <unistd.h>
 #include <fcntl.h>
