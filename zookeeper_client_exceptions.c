/* $Id$ */

#include "zookeeper_client_exceptions.h"
#if PHP_VERSION_ID >= 70000
#include <Zend/zend_exceptions.h>
#endif

// ---- Core functions ----

void register_zookeeper_client_exception_classes(TSRMLS_D)
{
    zend_class_entry class_entry;
    zend_class_entry **runtime_exception_class_entry = NULL;
#if PHP_VERSION_ID >= 70000
    zend_string *runtime_exception_class_name;
#else

#endif

    INIT_CLASS_ENTRY(class_entry, "ZookeeperClientException", NULL);
#if PHP_VERSION_ID >= 70000
    runtime_exception_class_name = zend_string_init("runtimeexception", strlen("runtimeexception"), 0);
    if ((runtime_exception_class_entry = zend_hash_find_ptr(CG(class_table), runtime_exception_class_name)) != NULL) {
        zookeeper_client_exception_class_entry = zend_register_internal_class_ex(&class_entry, runtime_exception_class_entry);
#else
    if (zend_hash_find(CG(class_table), "runtimeexception", sizeof("RuntimeException"), (void **) &runtime_exception_class_entry) == SUCCESS) {
        zookeeper_client_exception_class_entry = zend_register_internal_class_ex(&class_entry, *runtime_exception_class_entry, NULL TSRMLS_CC);
#endif
    } else {
        zookeeper_client_exception_class_entry = zend_register_internal_class_ex(&class_entry
#if PHP_VERSION_ID < 70000
				, zend_exception_get_default(TSRMLS_C), NULL 
#else
                , zend_ce_exception
#endif
				TSRMLS_CC);
    }

    INIT_CLASS_ENTRY(class_entry, "ZookeeperClientCoreException", NULL);
    zookeeper_client_core_exception_class_entry = zend_register_internal_class_ex(&class_entry, zookeeper_client_exception_class_entry
#if PHP_VERSION_ID < 70000
            , "ZookeeperClientException" 
#endif
            TSRMLS_CC);
}

void throw_zookeeper_client_exception(char *message, int code TSRMLS_DC)
{
    zend_throw_exception(zookeeper_client_exception_class_entry, message, code TSRMLS_CC);
}

void throw_zookeeper_client_core_exception(int code TSRMLS_DC)
{
    char *message;

    if (code == ZOK)
        return;

    message = (char *)zerror(code);
    zend_throw_exception(zookeeper_client_core_exception_class_entry, message, (long)code TSRMLS_CC);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 expandtab fdm=marker
 * vim<600: noet sw=4 ts=4 expandtab
 */
