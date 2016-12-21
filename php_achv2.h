#ifndef PHP_ACHV2_H
#define PHP_ACHV2_H

extern zend_module_entry achv2_module_entry;
#define phpext_achv2_ptr &achv2_module_entry

#define PHP_ACHV2_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_ACHV2_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_ACHV2_API __attribute__ ((visibility("default")))
#else
#	define PHP_ACHV2_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINFO_FUNCTION(achv2);

PHP_FUNCTION(achv2_decode);

#endif
