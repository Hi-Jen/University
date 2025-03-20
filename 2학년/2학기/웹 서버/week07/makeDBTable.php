<?php
$conn = mysqli_connect('localhost', 'root', 'tv591100');
if (!$conn) die('Could not connect: ' . mysqli_error($conn));
if (!mysqli_select_db($conn, 'week07')) die('Can\'t use database: ' . mysqli_error($conn));

$sql = "CREATE TABLE data (
    uid VARCHAR(20) NOT NULL,
    kor INT NOT NULL,
    eng INT NOT NULL,
    math INT NOT NULL,
    sci INT NOT NULL,
    hist INT NOT NULL,
    PRIMARY KEY (uid)
) DEFAULT CHARSET=utf8;";

if (!mysqli_query($conn, $sql)) {
    echo 'Error creating table: ' . mysqli_error($conn) . "\n";
} else {
    echo 'Table data is created' . "\n";
}

mysqli_close($conn);
?>
