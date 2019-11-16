#ifdef __cplusplus
extern "C" {
#endif

/* High level fatal exception handler, gets the stack pointer as argument,
 * the return address of the exception can be extracted and passed to
 * the error_fatal_handler
 */
void Fatal_Handler(unsigned int *stack_ptr)
{
  while(1); 
} 

#ifndef NDEBUG
/* NDEBUG is not defined.  Implement assert functionality rather than
 * using the default implementation */
#ifndef __OPT_SMALL_ASSERT
/* When __OPT_SMALL_ASSERT is defined, the assert macro would expand
 * to directly calling abort and not this __aeabi_assert.  In that case
 * the LINE and FILE information would not be present and be set to
 * 0.  However, the LR is captured by the abort() handler below */
void __aeabi_assert(const char *expr, const char *file, int line) {
}
#endif /* __OPT_SMALL_ASSERT not defined */

void abort() {
}

#endif /*NDEBUG not defined */

#ifdef __cplusplus
}
#endif
