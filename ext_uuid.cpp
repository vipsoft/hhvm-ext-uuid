/*
   UUID extension for HHVM.

   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2005 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Hartmut Holzgraefe, Anthon Pang                             |
   +----------------------------------------------------------------------+
*/

#include "hphp/runtime/base/base-includes.h"
#include <cinttypes>
#include <uuid/uuid.h>

#define UUID_TYPE_DEFAULT 0
#define UUID_TYPE_NULL -1
#define UUID_TYPE_INVALID -42

namespace HPHP {

const StaticString s_UUID_VARIANT_NCS("UUID_VARIANT_NCS");
const int64_t k_UUID_VARIANT_NCS = UUID_VARIANT_NCS;

const StaticString s_UUID_VARIANT_DCE("UUID_VARIANT_DCE");
const int64_t k_UUID_VARIANT_DCE = UUID_VARIANT_DCE;

const StaticString s_UUID_VARIANT_MICROSOFT("UUID_VARIANT_MICROSOFT");
const int64_t k_UUID_VARIANT_MICROSOFT = UUID_VARIANT_MICROSOFT;

const StaticString s_UUID_VARIANT_OTHER("UUID_VARIANT_OTHER");
const int64_t k_UUID_VARIANT_OTHER = UUID_VARIANT_OTHER;

const StaticString s_UUID_TYPE_DEFAULT("UUID_TYPE_DEFAULT");
const int64_t k_UUID_TYPE_DEFAULT = UUID_TYPE_DEFAULT;

const StaticString s_UUID_TYPE_TIME("UUID_TYPE_TIME");
const int64_t k_UUID_TYPE_TIME = UUID_TYPE_DCE_TIME;

const StaticString s_UUID_TYPE_DCE("UUID_TYPE_DCE");
const int64_t k_UUID_TYPE_DCE = UUID_TYPE_DCE_RANDOM;

const StaticString s_UUID_TYPE_NAME("UUID_TYPE_NAME");
const int64_t k_UUID_TYPE_NAME = UUID_TYPE_DCE_TIME;

const StaticString s_UUID_TYPE_RANDOM("UUID_TYPE_RANDOM");
const int64_t k_UUID_TYPE_RANDOM = UUID_TYPE_DCE_RANDOM;

const StaticString s_UUID_TYPE_NULL("UUID_TYPE_NULL");
const int64_t k_UUID_TYPE_NULL = UUID_TYPE_NULL;

const StaticString s_UUID_TYPE_INVALID("UUID_TYPE_INVALID");
const int64_t k_UUID_TYPE_INVALID = UUID_TYPE_INVALID;

const int UUID_BUF_LEN = 37;

#define CHECK_UUID(uuid_param, u_param) \
    if (uuid_parse(uuid_param.c_str(), u_param)) { \
        return Variant(false); \
    }

static Variant HHVM_FUNCTION(uuid_compare, const String& uuid1, const String& uuid2) {
    uuid_t u1, u2;

    CHECK_UUID(uuid1, u1)
    CHECK_UUID(uuid2, u2)

    return Variant(uuid_compare(u1, u2));
}

static String HHVM_FUNCTION(uuid_create, int64_t uuid_type /* = NULL */) {
    uuid_t u;
    char uuid_str[UUID_BUF_LEN];

    switch (uuid_type) {
        case UUID_TYPE_DCE_TIME:
            uuid_generate_time(u);
            break;
        case UUID_TYPE_DCE_RANDOM:
            uuid_generate_random(u);
            break;
        case UUID_TYPE_DEFAULT:
            uuid_generate(u);
            break;
        default:
            raise_warning(
                "Unknown/invalid UUID type '%ld' requested, using default type instead",
                uuid_type
            );
            uuid_generate(u);
    }

    uuid_unparse(u, uuid_str);

    return String(uuid_str);
}

static bool HHVM_FUNCTION(uuid_is_null, const String& uuid) {
    uuid_t u;

    if (uuid_parse(uuid.c_str(), u)) {
        return false;
    }

    return (bool) uuid_is_null(u);
}

static bool HHVM_FUNCTION(uuid_is_valid, const String& uuid) {
    uuid_t u;

    return (bool) (0 == uuid_parse(uuid.c_str(), u));
}

static Variant HHVM_FUNCTION(uuid_mac, const String& uuid) {
    uuid_t u;
    char uuid_str[UUID_BUF_LEN];

    CHECK_UUID(uuid, u)

    if (uuid_variant(u) != UUID_VARIANT_DCE ||
        uuid_type(u) != UUID_TYPE_DCE_TIME ||
        (u[10] & 0x01) // fake MAC address if the multicast bit is set
    ) {
        return Variant(false);
    }

    uuid_unparse(u, uuid_str);

    return Variant(String((char *) (uuid_str + 24)));
}

static Variant HHVM_FUNCTION(uuid_parse, const String& uuid) {
    uuid_t u;

    CHECK_UUID(uuid, u)

    return Variant(String((char *) &u, sizeof(uuid_t), CopyString));
}

static Variant HHVM_FUNCTION(uuid_time, const String& uuid) {
    uuid_t u;

    CHECK_UUID(uuid, u)

    if (uuid_variant(u) != UUID_VARIANT_DCE ||
        uuid_type(u) != UUID_TYPE_DCE_TIME
    ) {
        return Variant(false);
    }

    return Variant(uuid_time(u, NULL));
}

static Variant HHVM_FUNCTION(uuid_type, const String& uuid) {
    uuid_t u;

    CHECK_UUID(uuid, u)

    if (uuid_is_null(u)) {
        return Variant(UUID_TYPE_NULL);
    }

    return Variant(uuid_type(u));
}

static Variant HHVM_FUNCTION(uuid_unparse, const String& u) {
    char uuid_str[UUID_BUF_LEN];

    if (u.length() != sizeof(uuid_t)) {
        return Variant(false);
    }

    uuid_unparse((unsigned char *) u.c_str(), uuid_str);

    return Variant(String(uuid_str, 36, CopyString));
}

static Variant HHVM_FUNCTION(uuid_variant, const String& uuid) {
    uuid_t u;

    CHECK_UUID(uuid, u)

    if (uuid_is_null(u)) {
        return Variant(UUID_TYPE_NULL);
    }

    return Variant(uuid_variant(u));
}

////////////////////////////////////////////////////////////////////////////////

class uuidExtension: public Extension {
public:
  uuidExtension(): Extension("uuid", "1.0.3") {}
  virtual void moduleInit() {
    Native::registerConstant<KindOfInt64>(s_UUID_VARIANT_NCS.get(), k_UUID_VARIANT_NCS);
    Native::registerConstant<KindOfInt64>(s_UUID_VARIANT_DCE.get(), k_UUID_VARIANT_DCE);
    Native::registerConstant<KindOfInt64>(s_UUID_VARIANT_MICROSOFT.get(), k_UUID_VARIANT_MICROSOFT);
    Native::registerConstant<KindOfInt64>(s_UUID_VARIANT_OTHER.get(), k_UUID_VARIANT_OTHER);
    Native::registerConstant<KindOfInt64>(s_UUID_TYPE_DEFAULT.get(), k_UUID_TYPE_DEFAULT);
    Native::registerConstant<KindOfInt64>(s_UUID_TYPE_TIME.get(), k_UUID_TYPE_TIME);
    Native::registerConstant<KindOfInt64>(s_UUID_TYPE_DCE.get(), k_UUID_TYPE_DCE);
    Native::registerConstant<KindOfInt64>(s_UUID_TYPE_NAME.get(), k_UUID_TYPE_NAME);
    Native::registerConstant<KindOfInt64>(s_UUID_TYPE_RANDOM.get(), k_UUID_TYPE_RANDOM);
    Native::registerConstant<KindOfInt64>(s_UUID_TYPE_NULL.get(), k_UUID_TYPE_NULL);
    Native::registerConstant<KindOfInt64>(s_UUID_TYPE_INVALID.get(), k_UUID_TYPE_INVALID);
    HHVM_FE(uuid_compare);
    HHVM_FE(uuid_create);
    HHVM_FE(uuid_is_null);
    HHVM_FE(uuid_is_valid);
    HHVM_FE(uuid_mac);
    HHVM_FE(uuid_parse);
    HHVM_FE(uuid_time);
    HHVM_FE(uuid_type);
    HHVM_FE(uuid_unparse);
    HHVM_FE(uuid_variant);

    loadSystemlib();
  }
} s_uuid_extension;

HHVM_GET_MODULE(uuid);

}
