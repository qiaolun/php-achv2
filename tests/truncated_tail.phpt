--TEST--
Skip incomplete trailing records while preserving complete records
--SKIPIF--
<?php if (!extension_loaded("achv2")) print "skip"; ?>
--FILE--
<?php
$records = '06A60070AB00DE04E20B';
$expected = array(
    851 => array('finish' => 1, 'mark' => 901, 'step' => 5, 'start' => 0),
    111 => array('finish' => 1, 'mark' => 10000, 'step' => 5, 'start' => 10),
);

for ($length = 0; $length < 10; $length++) {
    $decoded = achv2_decode($records . substr('03E40046C6', 0, $length));
    $actual = array_map('get_object_vars', $decoded);
    echo 'tail ', $length, ': ', $actual === $expected ? 'ok' : 'FAIL', "\n";
}

var_dump(achv2_decode(''));
var_dump(achv2_decode('0'));
var_dump(achv2_decode('06A60070A'));
?>
--EXPECT--
tail 0: ok
tail 1: ok
tail 2: ok
tail 3: ok
tail 4: ok
tail 5: ok
tail 6: ok
tail 7: ok
tail 8: ok
tail 9: ok
NULL
NULL
NULL
