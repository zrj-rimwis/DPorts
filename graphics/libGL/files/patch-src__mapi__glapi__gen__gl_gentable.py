--- src/mapi/glapi/gen/gl_gentable.py.orig	2015-09-05 01:09:37.000000000 +0300
+++ src/mapi/glapi/gen/gl_gentable.py	2015-09-08 09:12:50.000000000 +0300
@@ -44,7 +44,7 @@ header = """/* GLXEXT is the define used
 #endif
 
 #if (defined(GLXEXT) && defined(HAVE_BACKTRACE)) \\
-	|| (!defined(GLXEXT) && defined(DEBUG) && !defined(__CYGWIN__) && !defined(__MINGW32__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && !defined(__DragonFly__))
+	|| (!defined(GLXEXT) && defined(DEBUG) && !defined(__CYGWIN__) && !defined(__MINGW32__) && !defined(__OpenBSD__) && !defined(__NetBSD__) && !defined(__FreeBSD__) && !defined(__DragonFly__))
 #define USE_BACKTRACE
 #endif
 
