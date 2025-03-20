<?php
$conn = mysqli_connect('localhost', 'root', 'tv591100');
if (!$conn) die('Could not connect: ' . mysqli_error($conn));
if (!mysqli_select_db($conn, 'week07')) die('Can\'t use database: ' . mysqli_error($conn));

$sql = "select * from data";
$result = mysqli_query($conn,$sql);
while($row = mysqli_fetch_array($result)) {
    echo $row['uid']. " ";
    echo $row['kor']. " ";
    echo $row['eng']. " ";
    echo $row['math']. " ";
    echo $row['sci']. " ";
    echo $row['hist'] . " <br/>";
}

mysqli_close($conn);
?>

