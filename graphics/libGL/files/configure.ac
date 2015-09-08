--- configure.ac.orig	2015-09-06 19:54:50.000000000 +0300
+++ configure.ac	2015-09-08 10:05:40.000000000 +0300
@@ -78,6 +78,7 @@ DRI2PROTO_REQUIRED=2.6
 DRI3PROTO_REQUIRED=1.0
 PRESENTPROTO_REQUIRED=1.0
 LIBUDEV_REQUIRED=151
+LIBDEVQ_REQUIRED=0.0.2
 GLPROTO_REQUIRED=1.4.14
 LIBOMXIL_BELLAGIO_REQUIRED=0.0
 LIBVA_REQUIRED=0.35.0
@@ -97,7 +98,7 @@ AC_PROG_CXX
 AM_PROG_CC_C_O
 AM_PROG_AS
 AX_CHECK_GNU_MAKE
-AC_CHECK_PROGS([PYTHON2], [python2 python])
+AC_CHECK_PROGS([PYTHON2], [python2.7 python2 python])
 AC_PROG_SED
 AC_PROG_MKDIR_P
 
@@ -740,7 +741,7 @@ AC_ARG_ENABLE([dri],
     [enable_dri=yes])
 
 case "$host_os" in
-linux*)
+linux*|freebsd*|dragonfly*)
     dri3_default=yes
     ;;
 *)
@@ -997,6 +998,9 @@ esac
 PKG_CHECK_MODULES([LIBUDEV], [libudev >= $LIBUDEV_REQUIRED],
                   have_libudev=yes, have_libudev=no)
 
+PKG_CHECK_MODULES([LIBDEVQ], [libdevq-1.0 >= $LIBDEVQ_REQUIRED],
+                  have_libdevq=yes, have_libdevq=no)
+
 AC_ARG_ENABLE([sysfs],
     [AS_HELP_STRING([--enable-sysfs],
         [enable /sys PCI identification @<:@default=disabled@:>@])],
@@ -1093,6 +1097,10 @@ if test "$have_libudev" = yes; then
     DEFINES="$DEFINES -DHAVE_LIBUDEV"
     have_pci_id=yes
 fi
+if test "$have_libdevq" = yes; then
+    DEFINES="$DEFINES -DHAVE_LIBDEVQ"
+    have_pci_id=yes
+fi
 
 if test "$have_sysfs" = yes; then
     DEFINES="$DEFINES -DHAVE_SYSFS"
@@ -1215,6 +1223,22 @@ if test "x$enable_dri" = xyes; then
         ;;
     gnu*)
         DEFINES="$DEFINES -DHAVE_ALIAS"
+        if test "x$enable_dri3" = xyes; then
+            DEFINES="$DEFINES -DHAVE_DRI3"
+        fi
+
+        if test "x$have_libdevq" != xyes; then
+            AC_MSG_ERROR([libdevq required for building DRI])
+        fi
+
+        case "$host_cpu" in
+        powerpc* | sparc*)
+            # Build only the drivers for cards that exist on PowerPC/sparc
+            if test "x$with_dri_drivers" = "xyes"; then
+                with_dri_drivers="r200 radeon swrast"
+            fi
+            ;;
+        esac
         ;;
     cygwin*)
         if test "x$with_dri_drivers" = "xyes"; then
@@ -1371,6 +1395,8 @@ fi
 AM_CONDITIONAL(HAVE_GBM, test "x$enable_gbm" = xyes)
 if test "x$need_pci_id$have_libudev" = xyesyes; then
     GBM_PC_REQ_PRIV="libudev >= $LIBUDEV_REQUIRED"
+elif test "x$need_libdevq" = xyes; then
+    GBM_PC_REQ_PRIV="libdevq-1.0 >= $LIBDEVQ_REQUIRED"
 else
     GBM_PC_REQ_PRIV=""
 fi
@@ -1524,9 +1550,19 @@ if test "x$enable_opencl" = xyes; then
         AC_MSG_ERROR([cannot enable OpenCL without Gallium])
     fi
 
+    if test "x$acv_mesa_CLANG" = xno; then
+
+    GCC_VERSION=`$CC -dumpversion`
+    if test $? -eq 0; then
+        GCC_VERSION_MAJOR=`echo $GCC_VERSION | cut -d. -f1`
+        GCC_VERSION_MINOR=`echo $GCC_VERSION | cut -d. -f2`
+    fi
+
     if test $GCC_VERSION_MAJOR -lt 4 -o $GCC_VERSION_MAJOR -eq 4 -a $GCC_VERSION_MINOR -lt 7; then
         AC_MSG_ERROR([gcc >= 4.7 is required to build clover])
     fi
+# end of clang test.
+    fi
 
     if test "x$have_libclc" = xno; then
         AC_MSG_ERROR([pkg-config cannot find libclc.pc which is required to build clover.
@@ -1794,8 +1830,6 @@ if test "x$enable_gallium_llvm" = xyes;
                 CLANG_LIBDIR=${LLVM_LIBDIR}
             fi
             CLANG_RESOURCE_DIR=$CLANG_LIBDIR/clang/${LLVM_VERSION}
-            AS_IF([test ! -f "$CLANG_RESOURCE_DIR/include/stddef.h"],
-                [AC_MSG_ERROR([Could not find clang internal header stddef.h in $CLANG_RESOURCE_DIR Use --with-clang-libdir to specify the correct path to the clang libraries.])])
         fi
     else
         MESA_LLVM=0
