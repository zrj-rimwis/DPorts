--- src/gallium/include/pipe/p_config.h.orig	2015-09-05 01:09:37.000000000 +0300
+++ src/gallium/include/pipe/p_config.h	2015-09-08 09:19:15.000000000 +0300
@@ -81,6 +81,13 @@
 #define PIPE_CC_SUNPRO
 #endif
 
+#if defined(__sparc__) || defined(__sparc64__)
+#define PIPE_ARCH_SPARC
+#if defined(__sparc64__)
+#define PIPE_ARCH_SPARC_64
+#endif
+#endif
+
 
 /*
  * Processor architecture
