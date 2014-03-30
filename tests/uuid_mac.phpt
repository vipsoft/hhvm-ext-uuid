--TEST--
uuid_mac() function
--SKIPIF--
<?php 

if(!extension_loaded('uuid')) die('skip ');

 ?>
--FILE--
<?php
var_dump(uuid_mac("b691c99c-7fc5-11d8-9fa8-00065b896488")); // valid MAC
var_dump(uuid_mac("b691c99c-7fc5-11d8-9fa8-01065b896488")); // set multicast bit
var_dump(uuid_mac("b691c99c-7fc5-21d8-9fa8-00065b896488")); // version 2
var_dump(uuid_mac("b691c99c-7fc5-31d8-9fa8-00065b896488")); // version 3
var_dump(uuid_mac("b691c99c-7fc5-41d8-9fa8-00065b896488")); // version 4
var_dump(uuid_mac("b691c99c-7fc5-51d8-9fa8-00065b896488")); // version 5
var_dump(uuid_mac("b691c99c-7fc5-11d8-1fa8-00065b896488")); // NCS variant
var_dump(uuid_mac("b691c99c-7fc5-11d8-dfa8-00065b896488")); // Microsoft variant
var_dump(uuid_mac("b691c99c-7fc5-11d8-ffa8-00065b896488")); // reserved variant

?>
--EXPECT--
string(12) "00065b896488"
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
