<?hh

/**
 * uuid_compare() - compare whether two UUIDs are the same
 *
 * @param string $uuid1 - first UUID
 * @param string $uuid2 - second UUID
 *
 * @return mixed - Returns an integer less than, equal to, or greater than zero
 *                 if uuid1 is lexicographically less than, equal to, or
 *                 greater than uuid2.
 *                 Returns false if either uuid1 or uuid2 are invalid UUIDs.
 *
 */
<<__Native>> function uuid_compare (string $uuid1, string $uuid2): mixed;

/**
 * uuid_create() - creates a new universally unique identifier (UUID)
 *
 * @param int $uuid_type - UUID_TYPE_DEFAULT, UUID_TYPE_RANDOM, UUID_TYPE_TIME
 *
 * @return string - A 36 byte string representation of the UUID
 */
<<__Native>> function uuid_create (int $uuid_type = NULL): string;

/**
 * uuid_is_null() - compare the value of the UUID to NULL UUID
 *
 * @param string $uuid - a UUID
 *
 * @return bool - Returns true if uuid is equal to the NULL UUID,
 *                00000000-0000-0000-0000-000000000000.
 *                Otherwise it returns false.
 */
<<__Native>> function uuid_is_null (string $uuid): bool;

/**
 * uuid_is_valid() - compare the UUID to the expected format
 *
 * @param string $uuid - a UUID
 *
 * @return bool - Returns true if uuid can be converted to its binary
 *                representation.
 *                Otherwise it returns false.
 */
<<__Native>> function uuid_is_valid (string $uuid): bool;

/**
 * uuid_mac() - extract MAC address from UUID
 *
 * @param string $uuid - a UUID
 *
 * @return mixed - Returns the last 12 characters of the UUID if uuid
 *                 contains a MAC address.
 *                 Otherwise it returns false.
 */
<<__Native>> function uuid_mac (string $uuid): mixed;

/**
 * uuid_parse() - convert UUID string representation to binary
 *
 * @param string $uuid - a UUID
 *
 * @return mixed - Returns a 16 byte binary representation of the UUID.
 *                 Otherwise it returns false.
 */
<<__Native>> function uuid_parse (string $uuid): mixed;

/**
 * uuid_time() - extract the time at which the UUID was created
 *
 * @param string $uuid - a UUID
 *
 * @return mixed - Returns the UUID creation time if uuid contains
 *                 an encoded timestamp.
 *                 Otherwise it returns false.
 */
<<__Native>> function uuid_time (string $uuid): mixed;

/**
 * uuid_type() - extract the UUID type
 *
 * @param string $uuid - a UUID
 *
 * @return mixed - Returns one of UUID_TYPE_RANDOM, UUID_TYPE_TIME, or
 *                 UUID_TYPE_OTHER if uuid is a valid UUID.
 *                 Otherwise it returns false.
 */
<<__Native>> function uuid_type (string $uuid): mixed;

/**
 * uuid_unparse() - convert UUID binary representation to human readable string
 *
 * @param string $u - a binary UUID
 *
 * @return mixed - Returns a 36 byte string representation of the UUID.
 *                 Otherwise it returns false.
 */
<<__Native>> function uuid_unparse (string $u): mixed;

/**
 * uuid_variant() - extract the UUID variant
 *
 * @param string $uuid - a UUID
 *
 * @return mixed - Returns one of UUID_VARIANT_NCS, UUID_VARIANT_DCE,
 *                 UUID_VARIANT_MICROSOFT, or UUID_VARIANT_OTHER if uuid is a
 *                 valid UUID.
 *                 Otherwise it returns false.
 */
<<__Native>> function uuid_variant (string $uuid): mixed;
