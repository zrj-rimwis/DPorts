--- tools/intel_gpu_frequency.c.orig	2015-09-05 15:35:19.000000000 +0300
+++ tools/intel_gpu_frequency.c
@@ -114,12 +114,16 @@ initialize_freq_info(struct freq_info *f
 
 static void wait_freq_settle(void)
 {
+#ifdef __DragonFly__
+	usleep(20);
+#else
 	struct timespec ts;
 
 	/* FIXME: Lazy sleep without check. */
 	ts.tv_sec = 0;
 	ts.tv_nsec = 20000;
 	clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
+#endif
 }
 
 static void set_frequency(struct freq_info *freq_info, int val)
