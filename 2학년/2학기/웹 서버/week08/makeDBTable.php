<?php
$conn = mysqli_connect('localhost', 'root', 'admin#2024');

$sql = "DROP DATABASE IF EXISTS DB20213032";
if (!mysqli_query($conn, $sql)) {
    echo 'Error dropping database: ' . mysqli_error($conn) . "\n";
} else {
    echo 'Database DB20213032 is dropped if it existed.' . "\n";
}

$sql = "CREATE DATABASE DB20213032";
if (!mysqli_query($conn, $sql)) {
    die('Error creating database: ' . mysqli_error($conn) . "\n");
} else {
    echo 'Database DB20213032 is created.' . "\n";
}

if (!mysqli_select_db($conn, 'DB20213032')) {
    die('Can\'t use DB20213032: ' . mysqli_error($conn));
}

$sql = "DROP TABLE IF EXISTS poll";
if (!mysqli_query($conn, $sql)) {
    echo 'Error dropping table: ' . mysqli_error($conn) . "\n";
} else {
    echo 'Table poll is dropped if it existed.' . "\n";
}

$sql = "CREATE TABLE poll (";
$sql .= " sname VARCHAR(256) NOT NULL,";
$sql .= " sid VARCHAR(256) NOT NULL,";
$sql .= " sdept VARCHAR(256) NOT NULL,";
$sql .= " q1 INT NOT NULL,";
$sql .= " q2 INT NOT NULL,";
$sql .= " q3 INT NOT NULL,";
$sql .= " q4 VARCHAR(256) NOT NULL,";
$sql .= " q4a VARCHAR(256) NOT NULL,";
$sql .= " PRIMARY KEY (sid)) DEFAULT CHARSET=utf8;";

if (!mysqli_query($conn, $sql)) {
    echo 'Error creating table: ' . mysqli_error($conn) . "\n";
} else {
    echo 'Table poll is created.' . "\n";
}

mysqli_close($conn);
?>