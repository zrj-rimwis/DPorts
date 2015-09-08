--- src/gallium/winsys/svga/drm/vmw_screen_ioctl.c.orig	2015-09-06 19:54:50.000000000 +0300
+++ src/gallium/winsys/svga/drm/vmw_screen_ioctl.c	2015-09-08 09:17:43.000000000 +0300
@@ -76,6 +76,11 @@ vmw_region_size(struct vmw_region *regio
    return region->size;
 }
 
+#if defined(__DragonFly__) || defined(__FreeBSD__) || \
+    defined(__NetBSD__) || defined(__OpenBSD__)
+#define ERESTART EINTR
+#endif
+
 uint32
 vmw_ioctl_context_create(struct vmw_winsys_screen *vws)
 {
