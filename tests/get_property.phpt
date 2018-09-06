--TEST--
decode test
--SKIPIF--
<?php if (!extension_loaded("achv2")) print "skip"; ?>
--FILE--
<?php 
$d = achv2_decode('06A60070AB00DE04E20B03E40046C6054E00780B0632003148055800780B06CC007D0B055A00780B055600780B');
echo $d['851']->mark;
?>
--EXPECT--
901
