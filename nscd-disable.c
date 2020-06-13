#define _GNU_SOURCE // RTLD_NEXT
#include <dlfcn.h>

// Callback for glibc 2.15
struct traced_file;
static void do_nothing(size_t dbidx, struct traced_file *finfo) {}

// Stub for the disabler (since there is no header file with it)
void __nss_disable_nscd(void (*hell)(size_t, struct traced_file*));

// Wrapper for __libc_start_main that calls __nss_disable_nscd before calling main()
int __libc_start_main(
    int (*main)(int, char **, char **),
    int argc,
    char **argv,
    int (*init)(int, char **, char **),
    void (*fini)(void),
    void (*rtld_fini)(void),
    void *stack_end) {

	// Find the real __libc_start_main()
	typeof(&__libc_start_main) orig = dlsym(RTLD_NEXT, "__libc_start_main");

	// Disable nscd
	__nss_disable_nscd(do_nothing);

	// Call __libc_start_main with our custom main function
	return orig(main, argc, argv, init, fini, rtld_fini, stack_end);
}
