--- src/mesa/x86/assyntax.h.orig	2015-08-07 20:36:03.000000000 +0300
+++ src/mesa/x86/assyntax.h	2015-09-08 08:55:13.000000000 +0300
@@ -978,7 +978,8 @@
 #if defined(Lynx) || (defined(SYSV) || defined(SVR4)) \
  || (defined(__linux__) || defined(__OS2ELF__)) && defined(__ELF__) \
  || (defined(__FreeBSD__) && __FreeBSD__ >= 3) \
- || (defined(__NetBSD__) && defined(__ELF__))
+ || (defined(__NetBSD__) && defined(__ELF__)) \
+ || (defined(__DragonFly__))
 #define GLNAME(a)	a
 #else
 #define GLNAME(a)	CONCAT(_, a)
