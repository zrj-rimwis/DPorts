--- lib/drmtest.h.orig	2015-09-05 16:26:59.000000000 +0300
+++ lib/drmtest.h
@@ -34,6 +34,10 @@
 #include <sys/mman.h>
 #include <errno.h>
 
+#ifdef __DragonFly__
+#include <sys/select.h>
+#endif
+
 #include <xf86drm.h>
 
 #include "intel_batchbuffer.h"
