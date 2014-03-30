## UUID (uuid) Extension for HHVM

This is a port of the PECL uuid extension for HipHop Virtual Machine.

### Prerequisites

This extension requires the `<uuid/uuid.h>` header file and `libuuid` library installed.

On Ubuntu 12.04, you need to install the "uuid-dev" and "libuuid1" packakges.

### Building & Installation

Requires HHVM 3.0 or later.

~~~
$ export HPHP_HOME=/path/to/hhvm
$ cd /path/to/extension
$ ./build.sh
~~~

This will produce a `uuid.so` file, the dynamically-loadable extension.

To enable the extension, you need to have the following section in your HHVM
config file:

~~~
DynamicExtensionPath = /path/to/hhvm/extensions
DynamicExtensions {
        * = uuid.so
}
~~~

Where `/path/to/hhvm/extensions` is a folder containing all HHVM extensions,
and `uuid.so` is in it. This will cause the extension to be loaded when the
virtual machine starts up.

### Testing

To run the test suite:

~~~
$ cd /path/to/extension
$ ./test.sh run-tests.php
~~~
