#include "platform/bionic/android_current_thread_stack_limits.h"

#include "pthread_internal.h"

extern "C" bool android_find_current_thread_stack_limits(uintptr_t* stack_bottom,
                                                         uintptr_t* stack_top) {
  pthread_internal_t* thread = __get_thread();
  if (thread == nullptr || thread->stack_top == 0) return false;

  *stack_bottom = thread->stack_bottom;
  *stack_top = thread->stack_top;
  return true;
}
