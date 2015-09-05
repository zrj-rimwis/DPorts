--- lib/intel_os.c.orig	2015-03-27 16:23:56.000000000 +0200
+++ lib/intel_os.c
@@ -45,6 +45,9 @@
 #include <sys/sysinfo.h>
 #elif defined(HAVE_SWAPCTL) /* Solaris */
 #include <sys/swap.h>
+#elif defined(__DragonFly__)
+#include <sys/types.h>
+#include <sys/sysctl.h>
 #endif
 
 #include "intel_io.h"
@@ -119,6 +122,16 @@ intel_get_avail_ram_mb(void)
         npages = sysconf(_SC_AVPHYS_PAGES);
 
 	retval = (uint64_t) pagesize * npages;
+#elif defined(__DragonFly__)
+	long avail_pages, page_size = 4096;
+	size_t size_apages = sizeof(avail_pages);
+	sysctlbyname("vm.stats.vm.v_free_count", &avail_pages, &size_apages, NULL, 0);
+/* zRJ: one syscall less, yeah bite me */
+	/* sysctlbyname("vm.stats.vm.v_page_size", &page_size, &size_apages, NULL, 0); */
+
+	igt_assert(avail_pages > 0 && page_size >= 1024);
+
+	retval = (uint64_t) page_size * avail_pages;
 #else
 #error "Unknown how to get available RAM for this OS"
 #endif
@@ -184,6 +197,8 @@ intel_get_total_swap_mb(void)
 	free(buf);
 
 	retval = (uint64_t) pagesize * totalpages;
+#elif defined(__DragonFly__)
+	retval = 0; /* why not? */
 #else
 #warning "Unknown how to get swap size for this OS"
 	return 0;
