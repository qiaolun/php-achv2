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

#define FINISH "finish"
#define STEP "step"
#define MARK "mark"
#define START "start"

static PHP_MINFO_FUNCTION(achv2);
 
PHP_FUNCTION(achv2_decode);

ZEND_BEGIN_ARG_INFO_EX(arginfo_achv2_decode, 0, 0, 1)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

static zend_function_entry achv2_functions[] = {
    PHP_FE(achv2_decode, arginfo_achv2_decode)
    PHP_FE_END
};

/* {{{ achv2_module_entry
 */
zend_module_entry achv2_module_entry = {
    STANDARD_MODULE_HEADER,
    "achv2",
    achv2_functions,
    0,
    0,
    0,
    0,
    PHP_MINFO(achv2),
    PHP_ACHV2_VERSION,
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
    size_t raw_size, offset;
    long store, finish, step, mark, id;
    zend_string *key_finish, *key_mark, *key_step, *key_start;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &raw, &raw_size) == FAILURE) {
        return;
    }

    if (raw_size < 10) {
        return;
    }

    memset(buf, 0, 11);

    key_finish = zend_string_init(FINISH, sizeof(FINISH)-1, 0);
    key_mark = zend_string_init(MARK, sizeof(MARK)-1, 0);
    key_step = zend_string_init(STEP, sizeof(STEP)-1, 0);
    key_start = zend_string_init(START, sizeof(START)-1, 0);

    array_init_size(return_value, raw_size / 10 + 10);

    for (offset = 0; offset < raw_size; offset += 10) {
        zval row, z_finish, z_mark, z_step, z_start;

        memcpy(buf, raw + offset, 10);

        store = strtol(buf, NULL, 16);
        finish = store & 0x0000000001;
        step = (store & 0x000000001e) >> 1 ;
        mark = (store & 0x001ffffe0) >> 5 ;
        id = store >> 25;

        if (id < 0 || id > 99999) {
            php_error_docref(NULL, E_WARNING, "invalid id %d", id);
        }

        if (step > 5) {
            php_error_docref(NULL, E_WARNING, "invalid step %d", step);
        }

        array_init_size(&row, 4);

        ZVAL_LONG(&z_finish, finish);
        zend_hash_add(HASH_OF(&row), key_finish, &z_finish);

        ZVAL_LONG(&z_mark, mark);
        zend_hash_add(HASH_OF(&row), key_mark, &z_mark);

        ZVAL_LONG(&z_step, step);
        zend_hash_add(HASH_OF(&row), key_step, &z_step);

        ZVAL_LONG(&z_start, offset);
        zend_hash_add(HASH_OF(&row), key_start, &z_start);

        object_and_properties_init(&row, ZEND_STANDARD_CLASS_DEF_PTR, HASH_OF(&row));

        zend_hash_index_add(HASH_OF(return_value), id, &row);
    }

    zend_string_release(key_finish);
    zend_string_release(key_mark);
    zend_string_release(key_step);
    zend_string_release(key_start);
}
