--- lib/igt_core.c.orig	2015-09-05 14:49:21.000000000 +0300
+++ lib/igt_core.c
@@ -1465,6 +1465,8 @@ static void fatal_sig_handler(int sig)
 		pid_t tid = syscall(SYS_gettid);
 
 		syscall(SYS_tgkill, pid, tid, sig);
+#elif defined (__DragonFly__)
+		kill(getpid(), sig);
 #else
 		pthread_t tid = pthread_self();
 		union sigval value = { .sival_ptr = NULL };
