--- src/mesa/drivers/dri/common/xmlconfig.c.orig	2015-09-02 20:06:23.000000000 +0300
+++ src/mesa/drivers/dri/common/xmlconfig.c	2015-09-08 08:54:23.000000000 +0300
@@ -59,6 +59,9 @@ extern char *program_invocation_name, *p
 #elif defined(__NetBSD__) && defined(__NetBSD_Version__) && (__NetBSD_Version__ >= 106000100)
 #    include <stdlib.h>
 #    define GET_PROGRAM_NAME() getprogname()
+#elif defined(__DragonFly__)
+#    include <stdlib.h>
+#    define GET_PROGRAM_NAME() getprogname()
 #elif defined(__APPLE__)
 #    include <stdlib.h>
 #    define GET_PROGRAM_NAME() getprogname()
