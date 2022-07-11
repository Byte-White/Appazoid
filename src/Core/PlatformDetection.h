// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
#define AZ_PLATFORM_WINDOWS //is supported
#ifdef _WIN64
	/* Windows x64  */
#define AZ_PLATFORM_WINDOWS64 //is supported
#else
	/* Windows x86 */
#define AZ_PLATFORM_WINDOWS32 //is supported
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!" //not supported
#elif TARGET_OS_IPHONE == 1
#define AZ_PLATFORM_IOS
#error "IOS is not supported!" //not supported
#elif TARGET_OS_MAC == 1
#define AZ_PLATFORM_MACOS //is supported
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
#define AZ_PLATFORM_ANDROID
#error "Android is not supported!" //not supported
#elif defined(__linux__)
#define AZ_PLATFORM_LINUX //is supported

#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection
