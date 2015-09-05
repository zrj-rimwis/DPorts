--- tests/pm_rpm.c.orig	2015-09-05 16:33:42.000000000 +0300
+++ tests/pm_rpm.c
@@ -37,8 +37,12 @@
 #include <sys/mman.h>
 #include <sys/types.h>
 #include <sys/stat.h>
+#ifndef __DragonFly__
 #include <linux/i2c.h>
 #include <linux/i2c-dev.h>
+#else
+#include <limits.h>
+#endif
 
 #include <drm.h>
 
@@ -546,6 +550,7 @@ static void assert_drm_infos_equal(struc
 		assert_drm_crtcs_equal(d1->crtcs[i], d2->crtcs[i]);
 }
 
+#ifndef __DragonFly__
 /* We could check the checksum too, but just the header is probably enough. */
 static bool edid_is_valid(const unsigned char *edid)
 {
@@ -649,6 +654,7 @@ static void test_i2c(struct mode_set_dat
 	diff = drm_edids - i2c_edids;
 	igt_assert(diff <= vga_outputs && diff >= 0);
 }
+#endif
 
 static void setup_pc8(void)
 {
@@ -817,6 +823,7 @@ static void drm_resources_equal_subtest(
 	free_drm_info(&post_suspend);
 }
 
+#ifndef __DragonFly__
 static void i2c_subtest_check_environment(void)
 {
 	int i2c_dev_files = 0;
@@ -849,6 +856,7 @@ static void i2c_subtest(void)
 
 	enable_one_screen(&ms_data);
 }
+#endif
 
 static void read_full_file(const char *name)
 {
@@ -1880,8 +1888,10 @@ int main(int argc, char *argv[])
 	/* Misc */
 	igt_subtest("reg-read-ioctl")
 		reg_read_ioctl_subtest();
+#ifndef __DragonFly__
 	igt_subtest("i2c")
 		i2c_subtest();
+#endif
 	igt_subtest("pc8-residency")
 		pc8_residency_subtest();
 	igt_subtest("debugfs-read")
