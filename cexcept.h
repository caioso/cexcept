#include <sys/cdefs.h>
#ifdef __cplusplus
#error "cexcept should only be used with the C language"
#else
#include <assert.h>
#include <setjmp.h>
#include <string.h>
#endif // __cplusplus

#ifndef _CEXCEPT_H_
#define _CEXCEPT_H_

#ifndef CEXCEPT_MAX_NESTING
#define MAX_NESTING 10
#else
#define MAX_NESTING CEXCEPT_MAX_NESTING
#endif 

static jmp_buf cexcept_environment_buffer[MAX_NESTING];
static int cexcept_thrown_values[MAX_NESTING] = {0};
static int cexcept_environment_pointer = -1;
static bool cexcept_exception_thrown = false;

bool cexcept_should_run_catch(void) {
    if (cexcept_exception_thrown) {
        cexcept_exception_thrown = false;
        return true;
    }
    return false;
}

bool cexcept_is_thrown(void) {
    if (cexcept_thrown_values[cexcept_environment_pointer] != 0) {
        cexcept_exception_thrown = true;
        return true;
    }
    return false;
}

void initialize_cexcept(void) {
    memset(cexcept_thrown_values, 0, MAX_NESTING);
}

#define throw(x) assert(x != 0 && "0 is a reserved throw code"); \
                 assert(cexcept_environment_pointer >= 0 && "uncaught exception at" ); \
                 longjmp(cexcept_environment_buffer[cexcept_environment_pointer], x);

#define try assert(cexcept_environment_pointer < MAX_NESTING && "maximum try-catch block nested level reached" ); \
            cexcept_environment_pointer++; \
            cexcept_thrown_values[cexcept_environment_pointer] = setjmp(cexcept_environment_buffer[cexcept_environment_pointer]); \
            if (!cexcept_is_thrown())

#define exception cexcept_thrown_values[cexcept_environment_pointer + 1]

#define catch cexcept_environment_pointer--; \
              if (cexcept_should_run_catch())

#endif // _CEXCEPT_H_