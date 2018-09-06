--TEST--
decode test
--SKIPIF--
<?php if (!extension_loaded("achv2")) print "skip"; ?>
--FILE--
<?php 
var_dump(achv2_decode('06A60070AB00DE04E20B03E40046C6054E00780B0632003148055800780B06CC007D0B055A00780B055600780B'));
?>
--EXPECT--
array(9) {
  [851]=>
  object(stdClass)#1 (4) {
    ["finish"]=>
    int(1)
    ["step"]=>
    int(5)
    ["mark"]=>
    int(901)
    ["start"]=>
    int(0)
  }
  [111]=>
  object(stdClass)#2 (4) {
    ["finish"]=>
    int(1)
    ["step"]=>
    int(5)
    ["mark"]=>
    int(10000)
    ["start"]=>
    int(10)
  }
  [498]=>
  object(stdClass)#3 (4) {
    ["finish"]=>
    int(0)
    ["step"]=>
    int(3)
    ["mark"]=>
    int(566)
    ["start"]=>
    int(20)
  }
  [679]=>
  object(stdClass)#4 (4) {
    ["finish"]=>
    int(1)
    ["step"]=>
    int(5)
    ["mark"]=>
    int(960)
    ["start"]=>
    int(30)
  }
  [793]=>
  object(stdClass)#5 (4) {
    ["finish"]=>
    int(0)
    ["step"]=>
    int(4)
    ["mark"]=>
    int(394)
    ["start"]=>
    int(40)
  }
  [684]=>
  object(stdClass)#6 (4) {
    ["finish"]=>
    int(1)
    ["step"]=>
    int(5)
    ["mark"]=>
    int(960)
    ["start"]=>
    int(50)
  }
  [870]=>
  object(stdClass)#7 (4) {
    ["finish"]=>
    int(1)
    ["step"]=>
    int(5)
    ["mark"]=>
    int(1000)
    ["start"]=>
    int(60)
  }
  [685]=>
  object(stdClass)#8 (4) {
    ["finish"]=>
    int(1)
    ["step"]=>
    int(5)
    ["mark"]=>
    int(960)
    ["start"]=>
    int(70)
  }
  [683]=>
  object(stdClass)#9 (4) {
    ["finish"]=>
    int(1)
    ["step"]=>
    int(5)
    ["mark"]=>
    int(960)
    ["start"]=>
    int(80)
  }
}
