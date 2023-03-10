#ifndef A_DEBUG
#define A_DEBUG 0
#endif

#ifndef A_RELEASE_ASSERT
#define A_RELEASE_ASSERT 0
#endif

#include <stdarg.h>

typedef signed __int8   i8;
typedef signed __int16  i16;
typedef signed __int32  i32;
typedef signed __int64  i64;

typedef unsigned __int8   u8;
typedef unsigned __int16  u16;
typedef unsigned __int32  u32;
typedef unsigned __int64  u64;

typedef u64 umm;
typedef i64 imm;

typedef float  f32;
typedef double f64;

typedef u8 bool;

#define true (bool)(1)
#define false (bool)(0)

#define U8_MAX   (u8)  0xFF
#define U16_MAX  (u16) 0xFFFF
#define U32_MAX  (u32) 0xFFFFFFFF
#define U64_MAX  (u64) 0xFFFFFFFFFFFFFFFF

#define I8_MIN   (i8)  0x80
#define I16_MIN  (i16) 0x8000
#define I32_MIN  (i32) 0x80000000
#define I64_MIN  (i64) 0x8000000000000000

#define I8_MAX   (i8)  0x7F
#define I16_MAX  (i16) 0x7FFF
#define I32_MAX  (i32) 0x7FFFFFFF
#define I64_MAX  (i64) 0x7FFFFFFFFFFFFFFF

typedef struct String
{
    u8* data;
    u32 size;
} String;

#define STRING(str_lit) (String){ .data = (u8*)(str_lit), .size = sizeof(str_lit) - 1 }

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

#define CONCAT_(a, b) a##b
#define CONCAT(a, b) CONCAT_(a, b)
#define STATIC_ASSERT(EX)                                                 \
	struct CONCAT(STATIC_ASSERT_, CONCAT(__COUNTER__, CONCAT(_, __LINE__))) \
	{                                                                       \
		int static_assert_fails_on_negative_bit_width : (EX) ? 1 : -1;        \
	}

#if A_DEBUG | A_RELEASE_ASSERT
#define ASSERT(EX) ((EX) ? 1 : (*(volatile int*)0 = 0))
#define NOT_IMPLEMENTED ASSERT(!"NOT_IMPLEMENTED")
#define ILLEGAL_CODE_PATH ASSERT(!"ILLEGAL_CODE_PATH")
#else
#define ASSERT(EX)
#define NOT_IMPLEMENTED STATIC_ASSERT(!"NOT_IMPLEMENTED")
#define ILLEGAL_CODE_PATH
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define ROUND_UP(N, align) (((umm)(N) + ((umm)(align) - 1)) & ~((umm)(align) - 1))
#define ROUND_DOWN(N, align) ((umm)(N) & ~((umm)(align) - 1))
#define IS_POW_2(N) ((((umm)(N) - 1) & (umm)(N)) == 0 && (N) > 0)

#define ALIGNOF(T) __alignof(T)
