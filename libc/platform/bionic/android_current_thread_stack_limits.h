#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

// Finds the current thread's regular stack limits from bionic thread
// metadata. This is intended for low-level paths such as signal handlers:
// unlike pthread_getattr_np()/pthread_attr_getstack(), it does not use stdio,
// allocation, or other non-async-signal-safe libc machinery.
//
// The implementation is a direct read of __get_thread()->stack_bottom and
// __get_thread()->stack_top, so it is async-signal-safe in the same narrow
// sense as other TLS-register-based bionic thread accessors.
//
// For the main thread, this helper intentionally does not try to reconstruct a
// missing lower bound. __libc_init_main_thread_early() initializes the main
// thread with stack_top = argv and stack_bottom = 0. bionic's internal
// __find_main_stack_limits() can reconstruct the missing lower bound by
// scanning /proc/self/maps, but that helper uses stdio and is therefore not
// async-signal-safe.
//
// As a result, stack_bottom may be 0 for the main thread; callers that need a
// precise lower bound must handle that case separately.
bool android_find_current_thread_stack_limits(uintptr_t* _Nonnull stack_bottom,
                                              uintptr_t* _Nonnull stack_top);

__END_DECLS
