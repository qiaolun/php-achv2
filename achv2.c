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


ZEND_BEGIN_ARG_INFO_EX(arginfo_achv2_encode, 0, 0, 1)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

const zend_function_entry achv2_functions[] = {
    PHP_FE(achv2_decode, arginfo_achv2_encode)
    PHP_FE_END
};

/* {{{ achv2_module_entry
 */
zend_module_entry achv2_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "achv2",
    achv2_functions,
    NULL,
    NULL,
    NULL,
    NULL,
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

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(achv2)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "achv2 support", "enabled");
    php_info_print_table_end();
}
/* }}} */

PHP_FUNCTION(achv2_decode) {
    const char *raw;
    char buf[11];
    int raw_size, offset;
    long store, finish, step, mark, id;
    zval *data;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &raw, &raw_size) == FAILURE) {
        return;
    }

    if (raw_size < 10) {
        return;
    }

    array_init_size(return_value, 8191);

    for (offset = 0; offset < raw_size; offset += 10) {

        memcpy(buf, raw + offset, 10);

        store = strtol(buf, NULL, 16);
        finish = store & 0x0000000001;
        step = (store & 0x000000001e) >> 1 ;
        mark = (store & 0x001ffffe0) >> 5 ;
        id = store >> 25;

        MAKE_STD_ZVAL(data);
        array_init(data);

        add_assoc_long_ex(data, "finish", 7, finish);
        add_assoc_long_ex(data, "mark", 5, mark);
        add_assoc_long_ex(data, "step", 5, step);
        add_assoc_long_ex(data, "start", 6, offset);

        object_and_properties_init(data, ZEND_STANDARD_CLASS_DEF_PTR, Z_ARRVAL_P(data));

        add_index_zval(return_value, id, data);
    }

}
