/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_achv2.h"

/* If you declare any globals in php_achv2.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(achv2)
*/

/* True global resources - no need for thread safety here */
static int le_achv2;

/* {{{ achv2_functions[]
 *
 * Every user visible function must have an entry in achv2_functions[].
 */
const zend_function_entry achv2_functions[] = {
	PHP_FE(achv2_decode,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in achv2_functions[] */
};
/* }}} */

/* {{{ achv2_module_entry
 */
zend_module_entry achv2_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"achv2",
	achv2_functions,
	PHP_MINIT(achv2),
	PHP_MSHUTDOWN(achv2),
	PHP_RINIT(achv2),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(achv2),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(achv2),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_ACHV2_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ACHV2
ZEND_GET_MODULE(achv2)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("achv2.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_achv2_globals, achv2_globals)
    STD_PHP_INI_ENTRY("achv2.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_achv2_globals, achv2_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_achv2_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_achv2_init_globals(zend_achv2_globals *achv2_globals)
{
	achv2_globals->global_value = 0;
	achv2_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(achv2)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(achv2)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(achv2)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(achv2)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(achv2)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "achv2 support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

PHP_FUNCTION(achv2_decode) {
    const char *raw;
    int size;
	int offset;
	char buf[64];
	

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &raw, &size) == FAILURE) return; 
       
	array_init(return_value);

	if (size < 10) {
		return;
	}

	for (offset = 0; offset < size; offset += 10) {	

		memcpy(buf, raw + offset, 10);
		buf[11] = 0;

		long store = strtol(buf, NULL, 16);
        long finish = store & 0x0000000001;
        long step = (store & 0x000000001e) >> 1 ; 
        long mark = (store & 0x001ffffe0) >> 5 ; 
        long id = store >> 25; 

		zval *data;
		MAKE_STD_ZVAL(data);
		object_init(data);

		add_property_long(data, "finish", finish);
		add_property_long(data, "mark", mark);
		add_property_long(data, "step", step);
		add_property_long(data, "start", offset);

		add_index_zval(return_value, id, data);
	}

}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
